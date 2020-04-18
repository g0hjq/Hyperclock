#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <limits.h>

#include "Panel.h"
#include "Wire.h"
#include "uRTCLib.h"
#include "Animations.h"
#include "MemoryFree.h"

// Forward References to functions in this file
extern void wait(unsigned int milliseconds);
extern void wait();

// Class enum for the lcd and buttons state machine
enum class State {Run=1, SetHour=2, SetMinute=3, ZeroSecond=4, SetAnimation=5, SetChime=6, Animate=7, Sleep=8};

// Class enum for the animation level
enum class AnimationLevel {Off=1, Low=2, Medium=3, High=4};

// Class Enum for the "chime" level
enum class ChimeLevel {None=1, Hourly=2, Quarterly=3, FiveMinute=4};

// Class Enum for push button state
enum class Button {None=1, Up=2, Down=3, Left=4, Right=5, Select=6, Timeout=7};

// initialize the library with the numbers of the interface pins
#define LCD_EN 9
#define LCD_RS 8
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_BACKLIGHT 10
#define LED_PIN 13
#define BUTTONS A0

// EEPROM addresses for saving the CHIME and ANIMATION settings. 
// In a different page to try and reduce wear
#define EEPROM_ADDR_CHIME 1
#define EEPROM_ADDR_ANIMATION 256

// brightness of the LCD backlight (0-255)
#define BACKLIGHT_LEVEL 30

// Initialise LCD object
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
  
// Initialise uRTCLib rtc object
uRTCLib rtc(0x68, URTCLIB_MODEL_DS3231);

// Initialise the Clock Motors Panel
Panel p;

// Used to detect a change in the button state
unsigned int previous_adc = 1023;

// state machine state
State           state = State::Run;  

// How much animation to do when changing the minute. Stored in EEPROM
AnimationLevel  animation_level;

// When to do extra animation (hourly, quarterly or none). Stored in EEPROM
ChimeLevel      chime_level;         // Loaded from EEPROM

bool            skip_chimes = true;  // Skips the chimes at startup and when setting the time

byte hr;
byte mi;
byte se;


int free_memory = 32767;

//=====================================================================================//
// Helper Functions                                                                     //
//=====================================================================================//


// pause execution until all motors have stopped
void wait()
{
    do
    {     
        delay(100);
    } while (p.busy());
}


// pause execution until all motors have stopped. Then wait another x milliseconds
void wait(unsigned int milliseconds)
{
    do
    {    
        delay(100);
    } while (p.busy());

    unsigned long end_time = millis() + milliseconds;

    while (end_time > millis())
    {     
        delay(100);
    }
}


// Writes a 2-digit decimal number to the LCD, with leading zeros
void print2(byte n)
{
    lcd.write(n/10 + '0');
    lcd.write(n%10 + '0');
}


void update_time()
{
    Direction dir = Direction::Clockwise;
    
    rtc.refresh();
    hr = rtc.hour();
    mi = rtc.minute();
    p.set_digit(hr/10, 0, dir);
    p.set_digit(hr%10, 1, dir);
    p.set_digit(mi/10, 2, dir);
    p.set_digit(rtc.minute()%10, 3, dir);   
}


// Checks the buttons and returns Button (None, Up, Down, Left, Right or Select)
Button check_buttons()
{ 
    static unsigned long timeout_end = LONG_MAX;

    // check for any button presses
    unsigned int val = analogRead(BUTTONS);

    if (val < 868)
    {
        // reset the timeout if any button pressed
        timeout_end = millis() + 120000;  // 2 minutes

        // don't do the chime for at least one minute
        skip_chimes = true;
    }
    else
    {
        // return Timeout if no button pressed for 30 seconds
        if (millis() > timeout_end)
        {
            timeout_end = LONG_MAX;
            return Button::Timeout;
        }
    }
   
    
    // Only raise events if there's been a change in the button state
    // Approx button ADC values are: None=1023 Select=744 Up=144 Down=343 Left=513 Right=0   
    int diff = val - previous_adc;
    
    if (abs(diff) > 45)  // only return a value if new key pressed
    {     
        previous_adc = val;
        
        if (val < 72)
        {
            return Button::Right;
        }
        else if (val < 243)
        {
            return Button::Up;
        }
        else if (val < 428)
        {
            return Button::Down;
        }
        else if (val < 613)
        {
            return Button::Left;
        }
        else if (val < 868)
        {
            return Button::Select;
        }        
    }    

    return Button::None;
}


  

//=====================================================================================//
// State machine functions
//=====================================================================================//

byte previous_minute = 255;
byte previous_second = 255;
    
void do_run()
{  
    // Used to detect when the minute has changed

    Direction dir = Direction::Clockwise;

    lcd.clear();
    lcd.print(F("RUNNING"));

    do 
    {
        rtc.refresh();
        byte second = rtc.second();

        if (second !=  previous_second)
        {
            previous_second = second;
            
            // Display the time on the LCD
            hr = rtc.hour();
            mi = rtc.minute();
            
            lcd.clear();
            lcd.print(F("RUN"));
            lcd.setCursor(8,0);
            print2(hr);
            lcd.print(":");
            print2(mi);
            lcd.print(":");
            print2(second);

            int fm = freeMemory(); free_memory = min(free_memory, fm); 
            lcd.setCursor(4,1);
            lcd.print(free_memory);
        

            if (mi != previous_minute)
            {
                previous_minute = mi;

                // do animations on the full hour, quarter hour or every 5 minutes
                if (!skip_chimes)
                {
                    if ((mi == 0) && 
                        (chime_level != ChimeLevel::None))
                    {
                        // hourly chime  
                        do_random_animations(1);
                    }
                    else if ( ((mi == 15) || (mi == 30) || (mi == 45)) && 
                              ((chime_level == ChimeLevel::Quarterly) || (chime_level == ChimeLevel::FiveMinute)) )
                    {
                        // smaller 1/4 hour chime
                        do_random_animations(1);
                    }
                    else if (((mi % 5) == 0) && 
                              (chime_level == ChimeLevel::FiveMinute))
                    {
                        // 5 minute chime
                        do_random_animations(1);                
                    }
                    wait();
                }
                skip_chimes = false;
                
                // if it's nearly the next minute, wait - there's no point in showing the time yet
                rtc.refresh();
                se = rtc.second();
                while (se > 45)
                {
                    lcd.clear();
                    lcd.print(F("Wait ... "));
                    lcd.print(60 - se);
                    
                    delay(1000);
                    rtc.refresh();
                    se = rtc.second();                    
                }
                
                // display the time on the panel
                switch (animation_level)
                {
                    case AnimationLevel::Off:
                        p.speeed(50);
                        p.acceleration_on();
                        dir = Direction::Shortest;
                        break;
                      
                    case AnimationLevel::Low:
                        p.speeed(10);
                        p.acceleration_on();
                        dir = Direction::Clockwise;
                        break;
                    break;
                      
                    case AnimationLevel::Medium:
                        dir = Direction::Alternate;
                        p.speeed(12);
                        p.acceleration_off();
                        p.go_to(0, 0, dir);
                        break;
                    break;
                      
                    case AnimationLevel::High:  
                        dir = Direction::Alternate;
                        p.acceleration_off();                      
                        //p.speeed(20);
                        //p.go_to(0, 0, dir);
                        //wait();
                        
                        p.speeed(7,DIGIT1);
                        p.speeed(8,DIGIT2);
                        p.speeed(9,DIGIT3);
                        p.speeed(10,DIGIT4);
                        p.relative(360,360, "ABCGHIMNOSTU");
                        p.relative(-360,-360, "DEFJKLPQRVWX");
                        break;
                    break;                      
                }

                // Display the time
                rtc.refresh();
                hr = rtc.hour();
                mi = rtc.minute();
                p.set_digit(hr/10, 0, dir);
                p.set_digit(hr%10, 1, dir);
                p.set_digit(mi/10, 2, dir);
                p.set_digit(mi%10, 3, dir);                
            }          
        }
        
        // Check the buttons
        Button btn = check_buttons();
        switch (btn)
        {
            case Button::Select:
                state = State::Sleep;
                break;
                
            case Button::Left:
                state = State::Animate;
                break;
                
            case Button::Right:
                state = State::SetHour;
                break;
                
            default:
                break;
        }
        delay(100);
    } while (state == State::Run);
}


void do_set_hour()
{
    lcd.clear();
    lcd.print(F("SET HOUR:"));

    rtc.refresh();
    hr = rtc.hour();
          
    do 
    {        
        lcd.setCursor(14, 0);
        print2(hr);
    
        Button btn = check_buttons();

        switch (btn)
        {
            case Button::Select:

            case Button::Left:
                state = State::Run;
                break;

            case Button::Right:
                state = State::SetMinute;
                break;

            case Button::Up:
                // Increment hour
                hr = (hr >= 23) ? 1 : hr + 1;
                break;

            case Button::Down:
                // Decrement hour
                hr = (hr <= 1) ? 23 : hr - 1;
                break;

            case Button::Timeout:
                state = State::Run;
                break;

            default:
                break;
        }

        delay(100);

    } while (state == State::SetHour);

    // Update the RTC chip
    rtc.refresh();
    if (rtc.hour() != hr)
    {
        rtc.set(rtc.second(), rtc.minute(), hr, 0, 0, 0, 0);
    }
}


void do_set_minute()
{
    lcd.clear();
    lcd.print(F("SET MINUTE:"));

    rtc.refresh();
    mi = rtc.minute();
          
    do 
    {
        lcd.setCursor(14, 0);
        print2(mi);
    
        Button btn = check_buttons();
        switch (btn)
        {
            case Button::Select:
                state = State::Run;
                break;
                
            case Button::Left:
                state = State::SetHour;
                break;
                
            case Button::Right:
                state = State::ZeroSecond;
                break;
                
            case Button::Up:
                // Increment minute
                mi = (mi >= 59) ? 0 : mi+1; 
                break;

            case Button::Down:
                // Decrement minute
                mi = (mi <= 1) ? 59 : mi-1;                    
                break;

            case Button::Timeout:
                state = State::Run;
                break;

            default:
                break;
        }

        delay(100);

    } while (state == State::SetMinute);  

    // Update the RTC chip
    rtc.refresh();
    if (rtc.minute() != mi)
    {
        rtc.set(rtc.second(), mi, rtc.hour(), 0, 0, 0, 0);
    }
}


void do_zero_second()
{
    lcd.clear();
    lcd.print(F("SET SECOND:"));

    do 
    {
        rtc.refresh();
        byte second = rtc.second();
          
        lcd.setCursor(14, 0);
        print2(second);
    
        Button btn = check_buttons();
        switch (btn)
        {
            case Button::Select:
                state = State::Run;
                break;
                
            case Button::Left:
                state = State::SetMinute;
                break;
                
            case Button::Right:
                state = State::SetAnimation;
                break;
                
            case Button::Up:
            case Button::Down:   
                {         
                    // Zero the second, rounding to the next minute
                    hr = rtc.hour();
                    mi = rtc.minute();
                    if (rtc.second() >= 30)
                    {
                        if (mi >= 59)
                        {
                            mi = 0;
                            hr = (hr >= 12) ? 1 : hr + 1;
                        }
                        else
                        {
                            mi++;
                        }
                    }
                        
                    rtc.set(0, mi, hr, 0, 0, 0, 0);
                }
                break;
            
            case Button::Timeout:
                state = State::Run;
                break;

           default:
                break;
        }
        
        delay(100);
    } while (state == State::ZeroSecond);  
   
}

void do_set_animation()
{
    lcd.clear();
    lcd.print(F("ANIMATION:"));

    AnimationLevel old_al = animation_level;
    
    do 
    {
        lcd.setCursor(12, 0);        
        switch (animation_level)
        {
            case AnimationLevel::Off:
                lcd.print(F("None"));
                break;
            case AnimationLevel::Low:
                lcd.print(F("Low "));
                break;
            case AnimationLevel::Medium:
                lcd.print(F("Med "));
                break;
            case AnimationLevel::High:
                lcd.print(F("High"));
                break;
            default:
                 break;
        }
      
        Button btn = check_buttons();
        switch (btn)
        {
            case Button::Select:
                state = State::Run;
                break;
                
            case Button::Left:
                state = State::ZeroSecond;
                break;
                
            case Button::Right:
                state = State::SetChime;
                break;
                
            case Button::Up:
                // Increment Animation Level
                if (animation_level == AnimationLevel::High)
                    animation_level = AnimationLevel::Off;  
                else
                    animation_level = (AnimationLevel)((byte)animation_level + 1);

                break;
                
            case Button::Down:
                // Decrement Animation Level
                if (animation_level == AnimationLevel::Off)
                    animation_level = AnimationLevel::High;  
                else
                    animation_level = (AnimationLevel)((byte)animation_level - 1);
                
                break;

            case Button::Timeout:
                state = State::Run;
                break;

            default:
                break;
        }
        delay(100);
    } while (state == State::SetAnimation);  

    // Update the EEPROM
    if (animation_level != old_al)
    {
        EEPROM.write(EEPROM_ADDR_ANIMATION, (byte)animation_level);   
    }
}

void do_set_chime()
{
    lcd.clear();
    lcd.print(F("CHIMES:"));

    ChimeLevel old_cl = chime_level;
    
    do 
    {
        lcd.setCursor(10, 0);        

        switch (chime_level)
        {
            case ChimeLevel::None:
                 lcd.print(F("None  "));
                 break;
            case ChimeLevel::Hourly:
                 lcd.print(F("Hourly"));
                 break;
            case ChimeLevel::Quarterly:
                 lcd.print(F("15 min"));
                 break;
            case ChimeLevel::FiveMinute:
                 lcd.print(F("5 min "));
                 break;
        }
      
        Button btn = check_buttons();
        switch (btn)
        {
            case Button::Select:
                state = State::Run;
                break;
                
            case Button::Left:
                state = State::SetAnimation;
                break;
                
            case Button::Right:
                state = State::Animate;
                break;
                
            case Button::Up:
                // Increment Chime Level
                if (chime_level == ChimeLevel::FiveMinute)
                    chime_level = ChimeLevel::None;  
                else
                    chime_level = (ChimeLevel)((int)chime_level + 1);

                break;                
                
            case Button::Down:
                // Decrement Chime Level
                if (chime_level == ChimeLevel::None)
                    chime_level = ChimeLevel::FiveMinute;  
                else
                    chime_level = (ChimeLevel)((int)chime_level - 1);

                break;

            case Button::Timeout:
                state = State::Run;
                break;

            default:
                break;
        }
        delay(100);
    } while (state == State::SetChime);  

    if (chime_level != old_cl)
    {
        EEPROM.write(EEPROM_ADDR_CHIME, (byte)chime_level);
    }
}


void do_animate()
{
    byte animation_number = 1;

    do 
    {
        lcd.clear();
        lcd.print(F("Animate    "));
        print2(animation_number);

        Button btn = check_buttons();
        switch (btn)
        {
            case Button::Select:
                execute_animation(animation_number);
                break;
                
            case Button::Left:
                state = State::SetChime;
                break;
                
            case Button::Right:
                state = State::Run;
                break;
                
            case Button::Up:
                // Increment Animation number
                if (animation_number >= NUMBER_OF_ANIMATIONS)
                    animation_number = 1;  
                else
                    animation_number++;

                break;                
                
            case Button::Down:
                // Decrement Animation number
                if (animation_number <= 1)
                    animation_number = NUMBER_OF_ANIMATIONS;  
                else
                    animation_number--;

                break;

            case Button::Timeout:
                state = State::Run;
                break;

            default:
                break;
        }
        
        delay(150);
    } while (state == State::Animate);  
}


void do_sleep()
{
    // Used for fading of the LED backlight in sleep mode
    byte fade_step = 0;

    lcd.clear();
    lcd.print(F("Sleeping ZZzzz.."));

    p.power_down();
    
    do 
    {
        // Fade the LCD backlight in and out if in sleep mode
        fade_step = (fade_step >= 40) ? 0 : fade_step+1;
        byte b = (fade_step < 20) ? fade_step : 40-fade_step;        
        
        analogWrite(LCD_BACKLIGHT, b);
       
        Button btn = check_buttons();
        if ((btn != Button::None) && (btn != Button::Timeout))
        {
            analogWrite(LCD_BACKLIGHT, BACKLIGHT_LEVEL);
            lcd.clear();
            lcd.print(F("WAKEY WAKEY!"));

            p.wake_up();
            p.clockwise(180, 0);
            p.anticlockwise(0, 0);
            wait();
            state = State::Run;
        }
        delay(150);
    } while (state == State::Sleep);  
}


//=====================================================================================//
// SETUP - Called once at initialisation
//=====================================================================================//
void setup() 
{
    Serial.begin(19200,SERIAL_8N1);

    // set up the LCD
    lcd.begin(16, 2);
    pinMode(LCD_BACKLIGHT, OUTPUT);
    analogWrite(LCD_BACKLIGHT, BACKLIGHT_LEVEL);

    // set up the Analogue (buttons) input
    pinMode(BUTTONS, INPUT);
  
    // Set up the DS3231 RTC chip
    Wire.begin();
    rtc.refresh();

    // Initialise the random number generator
    long seed = (rtc.hour() * 3600) + (rtc.minute() * 60) + rtc.second();
    randomSeed(seed);
      
    // Initiaslise the RTC chip if necessary
    if (rtc.lostPower()) 
    {      
        Serial.println(F("# Initialising RTC"));
        rtc.set(0,0,12,5,13,3,20);  // Default time to 12:00:00 Fri 13/03/2020
        rtc.lostPowerClear();
        rtc.refresh();
    }   

    // Read the animation and chime settings from the micro's EEPROM
    byte x = EEPROM.read(EEPROM_ADDR_CHIME);
    chime_level = (ChimeLevel)constrain(x,1,3); 

    x = EEPROM.read(EEPROM_ADDR_ANIMATION);
    animation_level = (AnimationLevel)constrain(x,1,4);
    
    // Print a message to the LCD.
    lcd.clear();
    lcd.print(F("HYPERCLOCK V0.02"));
    lcd.setCursor(0,1);
    lcd.print(F("Gary Bleads 2020"));
    delay(10000);
    lcd.clear();
}


//=====================================================================================//
// LOOP - Called continuously after initialisation
//=====================================================================================//
void loop() 
{

    switch (state)
    {
        case State::Run:
            do_run();
            break;
            
        case State::SetHour:
            do_set_hour();
            break;
            
        case State::SetMinute:
            do_set_minute();       
            break;
            
        case State::ZeroSecond:
            do_zero_second();
            break;
            
        case State::SetAnimation:
            do_set_animation();
            break;
            
        case State::SetChime:
            do_set_chime();
            break;
            
        case State::Animate:       
            do_animate();
            break;

        case State::Sleep:       
            do_sleep();
            break;
    }
  
}
