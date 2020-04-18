/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F15355
        Driver Version    :  2.00
*/


#include "mcc_generated_files/mcc.h"

#pragma warning disable 520


/* =================================================================== */
/* =================================================================== */
/* Type Declarations                                                   */
/* =================================================================== */
/* =================================================================== */

#define QUEUE_SIZE 16
#define POWER_DOWN_TIME 30000  // in 10ms steps, i.e. 5 mins. max=65532

typedef enum
{
    IDLE,       // No characters received
    COMMAND,    // Received a valid address, waiting for the command
    PARAM1,     // Received the command, waiting for optional parameter 1
    PARAM2,     // Received parameter 1, waiting for optional parameter 2
    SKIP        // Ignore the rest of this line
} rs232State_t;


// RS232 input are in the following format:
//
// <address><command>[<param1>[,<param2>]]<cr>
//
// 1. Address selects the board and motor, and is a character between 'A' and 'X',
//    or '*' to select all
//
// 2. Command is one of the following:
//      A = Goto absolute position 0 - 180, i.e.  *A0,0
//      R = Goto relative position -180 to +180, i.e. AR45,-45
//      S = Speed 0-99 (0=slow, 99=fast), i.e. *S50
//      L = LED 0=Off,1=On,2=Flash
//      P = Power Down, i.e. turn off current to the motors until the next command
//      H = Halt immediately (TODO)
//      F = Freeze Queue (1=freeze, 0=unfreeze)
//      X = Acceleration (1=On, 0=Off)
// 
// 3. Param1 is optional, -32768 to +32767 and defaults to zero
// 
// 4. Param2 is optional, -32768 to +32767 and defaults to zero


typedef struct 
{
    char    cmd;
    int16_t param1;
    int16_t param2;
} command_t;

/* =================================================================== */
/* =================================================================== */
/* Global Variables                                                   */
/* =================================================================== */
/* =================================================================== */
const int16_t _sines[] = {
      0,  // step 0
     78,  // step 1  
    153,  // step 2
    222,  // step 3
    283,  // step 4
    333,  // step 5
    370,  // step 6
    392,  // step 7
    400,  // step 8
    392,  // step 9
    370,  // step 10
    333,  // step 11
    283,  // step 12
    222,  // step 13
    153,  // step 14
     78,  // step 15
      0,  // step 16
    -78,  // step 17
   -153,  // step 18
   -222,  // step 19
   -283,  // step 20
   -333,  // step 21
   -370,  // step 22
   -392,  // step 23
   -400,  // step 24
   -392,  // step 25
   -370,  // step 26
   -333,  // step 27
   -283,  // step 28
   -222,  // step 29
   -153,  // step 30
   -78   // step 31
};  


const int16_t _cosines[] = {
    400,   // step 0
    392,   // step 1
    370,   // step 2
    333,   // step 3
    283,   // step 4
    222,   // step 5
    153,   // step 6
     78,   // step 7
      0,   // step 8
    -78,   // step 9
   -153,   // step 10
   -222,   // step 11
   -283,   // step 12
   -333,   // step 13
   -370,   // step 14
   -392,   // step 15
   -400,   // step 16
   -392,   // step 17
   -370,   // step 18
   -333,   // step 19
   -283,   // step 20
   -222,   // step 21
   -153,   // step 22
    -78,   // step 23
      0,   // step 24
     78,   // step 25
    153,   // step 26
    222,   // step 27
    283,   // step 28
    333,   // step 29
    370,   // step 30
    392    // step 31
};


const uint8_t _speeds[] =
{
    255,  // 1 rpm
    255,  // 2 rpm
    255,  // 3 rpm
    255,  // 4 rpm
    255,  // 5 rpm           
    216,  // 6 rpm
    185,  // 7 rpm
    162,  // 8 rpm
    144,  // 9 rpm
    129,  // 10 rpm
    117,  // 11 rpm
    108,  // 12 rpm
    99,   // 13 rpm
    92,   // 14 rpm
    86,   // 15 rpm
    80,   // 16 rpm
    76,   // 17 rpm
    71,   // 18 rpm
    68,   // 19 rpm
    64,   // 20 rpm
    61,   // 21 rpm
    58,   // 22 rpm
    56,   // 23 rpm
    53,   // 24 rpm
    51,   // 25 rpm
    49,   // 26 rpm
    47,   // 27 rpm
    46,   // 28 rpm
    44,   // 29 rpm
    42,   // 30 rpm
    41,   // 31 rpm
    40,   // 32 rpm
    38,   // 33 rpm
    37,   // 34 rpm
    36,   // 35 rpm
    35,   // 36 rpm
    34,   // 37 rpm
    33,   // 38 rpm
    32,   // 39 rpm
    32,   // 40 rpm
    31,   // 41 rpm
    30,   // 42 rpm
    29,   // 43 rpm
    29,   // 44 rpm
    28,   // 45 rpm
    27,   // 46 rpm
    27,   // 47 rpm
    26,   // 48 rpm
    26,   // 49 rpm
    25,   // 50 rpm
    25,   // 51 rpm
    24,   // 52 rpm
    24,   // 53 rpm
    23,   // 54 rpm
    23,   // 55 rpm
    22,   // 56 rpm
    22,   // 57 rpm
    21,   // 58 rpm
    21,   // 59 rpm
    21    // 60 rpm
};

/* Used by microstepping interrupt */
volatile int16_t _stepcount_1 = 0;     // 0 = stopped, >0 = clockwise, <0 = anticlockwise
volatile int16_t _stepcount_2 = 0;     // 0 = stopped, >0 = clockwise, <0 = anticlockwise
volatile uint8_t _microstep_1 = 0;     // 0 - 31
volatile uint8_t _microstep_2 = 0;     // 0 - 31
volatile uint8_t _position_1 = 90;     // current position of pointer 1, 0-179
volatile uint8_t _position_2 = 90;     // current position of pointer 2, 0-179

/* Used for acceleration / deceleration */
bool     _accelerate = true;            // Enable / disable acceleration
uint16_t _stepstaken_1 = 0;             // No of full steps so far
uint16_t _stepstaken_2 = 0;
uint8_t _slowdown_1 = 0;                // Amount to slow down by. 0=None, 1=half speed, 2=third speed
uint8_t _slowdown_2 = 0;
uint8_t _slowcount_1 = 0;              // Slow down Counter 
uint8_t _slowcount_2 = 0;

volatile bool _freeze_queue = false;  // If True, the current command may finish, but no more ones will start processing
volatile int16_t powerdown_timer = POWER_DOWN_TIME;

// The processor's address, from 'A' for digit 1 motor 1, to 'X' for digit 4 motor 6
char _my_address;     

// State machine for serial input
volatile rs232State_t _rs232_state = IDLE;

// temporary copy of command data, used by the state machine
char _cmd = '\0';
int16_t _param1 = 0;
int16_t _param2 = 0;
bool _param1_negative = false;
bool _param2_negative = false;

bool _power_down = false;
volatile uint16_t _power_down_timer = POWER_DOWN_TIME;

// Cyclic buffer to hold a list of commands waiting to be executed
volatile command_t _queue[QUEUE_SIZE];
volatile uint8_t _queue_front = 0;
volatile uint8_t _queue_back = 0;
volatile uint8_t _queue_length = 0;

// LED flasher and 10 millisecond (jiffy) clock
volatile uint8_t _led_mode = 0;     //  0 = off, 255 = always on, 1-254 = number of flashes to do
volatile uint8_t _led_timer = 0;    // 10 millisecond steps




/* =================================================================== */
/* =================================================================== */
/* Forward Function Declarations                                       */
/* =================================================================== */
/* =================================================================== */
void seek1(uint16_t pos1);
void seek2(uint16_t pos2);
void wait(void);


/* =================================================================== */
/* =================================================================== */
/* Interrupt Handler                                                   */
/* =================================================================== */
/* =================================================================== */


void Timer0_int_handler(void)
{
    int16_t sin;
    int16_t cos;
    
    //-------------------
    // HOURS FINGER
    //-------------------
    
    // slows things down 2x or 3x during acceleration and deceleration
    if (_slowcount_1 < _slowdown_1)
    {        
        _slowcount_1++;
    }
    else
    {
        _slowcount_1 = 0;

        if (_stepcount_1 == 0)        
        {
            // Nothing to do. Put the motor into low power (holding) mode.
            PWM3_LoadDutyValue(0);
            PWM4_LoadDutyValue(100);
        }
        else
        {
            if (_stepcount_1 > 0)
            {        
                // Move clockwise
                if (_microstep_1 >= 31)
                {
                    _microstep_1 = 0;
                    _stepcount_1--;                    
                    _position_1 = (_position_1 == 179) ? 0 : _position_1 + 1;

                    _stepstaken_1++;
                    
                    if (_accelerate) 
                    {
                        if ((_stepstaken_1 <= 3) || (_stepcount_1 <= 3))
                        {
                            _slowdown_1 = 3;
                        }
                        else if ((_stepstaken_1 <= 6) || (_stepcount_1 <= 6))
                        {
                            _slowdown_1 = 2;
                        }
                        else if ((_stepstaken_1 <= 9) || (_stepcount_1 <= 9))
                        {
                            _slowdown_1 = 1;
                        }
                        else
                        {
                            _slowdown_1 = 0;
                        }
                    }
                    else
                    {
                        _slowdown_1 = 0;
                    }
                }
                else    
                {
                    _microstep_1++;
                }
            }
            else
            {
                // move anticlockwise
                if (_microstep_1 == 0)
                {
                    _microstep_1 = 31;
                }
                else if (_microstep_1 == 1)
                {
                    _microstep_1 = 0;
                    _stepcount_1++;                    
                    _position_1 = (_position_1 == 0) ? 179 : _position_1 - 1;

                    _stepstaken_1++;
                    
                    if (_accelerate)
                    {
                        if ((_stepstaken_1 <= 3) || (_stepcount_1 >= -3))
                        {
                            _slowdown_1 = 3;
                        }
                        else if ((_stepstaken_1 <= 6) || (_stepcount_1 >= -6))
                        {
                            _slowdown_1 = 2;
                        }
                        else if ((_stepstaken_1 <= 9) || (_stepcount_1 >= -9))
                        {
                            _slowdown_1 = 1;
                        }
                        else
                        {
                            _slowdown_1 = 0;
                        }
                    }
                    else
                    {
                        _slowdown_1 = 0;
                    }
                }
                else
                {
                    _microstep_1--;
                }    
            }

            sin = _sines[_microstep_1];        
            cos = _cosines[_microstep_1];

            if (sin >= 0)
            {
               PWM3_LoadDutyValue(sin);
               IO_MOTOR1B_SetLow();
            }
            else
            {
               PWM3_LoadDutyValue(400 + sin);
               IO_MOTOR1B_SetHigh();
            }

            if (cos >= 0)
            {
               PWM4_LoadDutyValue(cos);
               IO_MOTOR2B_SetLow();
            }
            else
            {
               PWM4_LoadDutyValue(400 + cos);
               IO_MOTOR2B_SetHigh();
            }            
        }
    } // end if (_slowcount_1 < _slowdown_1)

    
    //-------------------
    // MINUTES FINGER
    //-------------------
    // slows things down 2x or 3x during acceleration and deceleration
    if (_slowcount_2 < _slowdown_2)
    {        
        _slowcount_2++;
    }
    else
    {
        _slowcount_2 = 0;

        if (_stepcount_2 == 0)        
        {
            // Nothing to do. Put the motor into low power (holding) mode.
            PWM5_LoadDutyValue(0);
            PWM6_LoadDutyValue(100);
        }
        else
        {
            if (_stepcount_2 > 0)
            {        
                // Move clockwise one step
                if (_microstep_2 >= 31)
                {
                    _microstep_2 = 0;
                    _stepcount_2--;                    
                    _position_2 = (_position_2 == 179) ? 0 : _position_2 + 1;

                    _stepstaken_2++;
                    
                    if (_accelerate) 
                    {
                        if ((_stepstaken_2 <= 3) || (_stepcount_2 <= 3))
                        {
                            _slowdown_2 = 3;
                        }
                        else if ((_stepstaken_2 <= 6) || (_stepcount_2 <= 6))
                        {
                            _slowdown_2 = 2;
                        }
                        else if ((_stepstaken_2 <= 9) || (_stepcount_2 <= 9))
                        {
                            _slowdown_2 = 1;
                        }
                        else
                        {
                            _slowdown_2 = 0;
                        }
                    }
                    else
                    {
                        _slowdown_2 = 0;
                    }
                }
                else    
                {
                    _microstep_2++;
                }
            }
            else
            {
                if (_microstep_2 == 0)
                {
                    _microstep_2 = 31;
                }
                else if (_microstep_2 == 1)
                {
                    _microstep_2 = 0;
                    _stepcount_2++;
                    _position_2 = (_position_2 == 0) ? 179 : _position_2 - 1;
                    
                    _stepstaken_2++;
                    
                    if (_accelerate)
                    {
                        if ((_stepstaken_2 <= 3) || (_stepcount_2 >= -3))
                        {
                            _slowdown_2 = 3;
                        }
                        if ((_stepstaken_2 <= 6) || (_stepcount_2 >= -6))
                        {
                            _slowdown_2 = 2;
                        }
                        else if ((_stepstaken_2 <= 9) || (_stepcount_2 >= -9))
                        {
                            _slowdown_2 = 1;
                        }
                        else
                        {
                            _slowdown_2 = 0;
                        }
                    }
                    else
                    {
                        _slowdown_2 = 0;
                    }
                }
                else
                {
                    _microstep_2--;
                }    
            }

            sin = _sines[_microstep_2];        
            cos = _cosines[_microstep_2];

            if (sin >= 0)
            {
               PWM5_LoadDutyValue(sin);
               IO_MOTOR3B_SetLow();
            }
            else
            {
               PWM5_LoadDutyValue(400 + sin);
               IO_MOTOR3B_SetHigh();
            }

            if (cos >= 0)
            {
               PWM6_LoadDutyValue(cos);
               IO_MOTOR4B_SetLow();
            }
            else
            {
               PWM6_LoadDutyValue(400 + cos);
               IO_MOTOR4B_SetHigh();
            }
        }
    } // end if (_slowcount_2 < _slowdown_2)

}

/* =================================================================== */
/* =================================================================== */
/* 10 millisecond timer used to flash the LED and to power down if no  */
/* serial port data received in 5 minutes                              */
/* =================================================================== */
/* =================================================================== */


void Timer1_int_handler(void)
{
    _led_timer++;
    
    if (_led_timer >= 50)   // 500 milliseconds
    {
        //  _led_mode 0 = off, 255 = always on, 1-254 = number of flashes to do
        if (_led_mode != 255)
        {
            IO_LED_SetLow();
        }
        
        if ((_led_mode < 254) && (_led_mode > 0))
        {
            _led_mode--;
        }
        
        _led_timer = 0;
    }
    else if (_led_timer == 25)  // 150 milliseconds
    {
        if (_led_mode > 0)
        {
            IO_LED_SetHigh();
        }
    }
    
    // Power down if no activity for a few minutes
    if (_power_down_timer == 0)
    {
        if (!_power_down)
        {
            // Add the Power Down command to the command queue
            volatile command_t* cmdPtr = &_queue[_queue_back];
            cmdPtr->cmd = 'P';
            _queue_length++;
            _queue_back++;
            if (_queue_back >= QUEUE_SIZE)
                _queue_back = 0;                    
        }
    }
    else
    {
        _power_down_timer--;
    }
    
}
    
/* =================================================================== */
/* =================================================================== */
/* Flash LED                                                           */
/* =================================================================== */
/* =================================================================== */
// Set the LED on, off or blink it a specified number of times.
//
//  count = 0 : LED OFF
//  count = 255 : LED ON
//  count = 254 : Flash forever
//  count = n (where n is between 1 and 253) : flash n times

void flash_led(uint8_t count)
{
    INTERRUPT_GlobalInterruptDisable();   
    _led_mode = count;
    _led_timer = 24;
    INTERRUPT_GlobalInterruptEnable();   
}


/* =================================================================== */
/* =================================================================== */
/* Power Management                                                    */
/* =================================================================== */
/* =================================================================== */


/* Turn off power to all motors and put the processor into doze mode */
void powerDown()
{
    TMR0_Reload(_speeds[30]);    
    seek1(90);
    seek2(90);
    wait();

    IO_MOTOR1B_TRIS = 1;
    IO_MOTOR2B_TRIS = 1;
    IO_MOTOR3B_TRIS = 1;
    IO_MOTOR4B_TRIS = 1;
    
    /* Todo : Put the processor to sleep */
    TMR0_StopTimer();
    TMR1_StopTimer();
    TMR2_StopTimer();
    
    _power_down = true;  
    
    CPUDOZEbits.DOZEN = 1;    // Doze enable - runs the CPU at reduced speed but maintains the peripherals
    CPUDOZEbits.ROI = 1;      // Full Speed in interrupt handling routines
    CPUDOZEbits.DOE = 1;      // Returns to slow speed at end of interrupt
    CPUDOZEbits.DOZE = 0b100; // CPU speed ratio = 1/32
}


/* Gets everything working again after a powerDown*/
void powerUp()
{    
    CPUDOZEbits.DOZEN = 0;    // Doze enable = False - runs the CPU at full speed
    TMR0_StartTimer();
    TMR1_StartTimer();
    TMR2_StartTimer();
    
    IO_MOTOR1B_TRIS = 0;
    IO_MOTOR2B_TRIS = 0;
    IO_MOTOR3B_TRIS = 0;
    IO_MOTOR4B_TRIS = 0;
    
    _power_down = false;    
}


/* =================================================================== */
/* =================================================================== */
/* Check USART                                                         */
/* =================================================================== */
/* =================================================================== */


/* Checks for any incoming characters in the USART buffer. 
   If they are for us, then they are parsed to get the command and 
   0,1 or 2 optional parameters. At <CR> the new command is added to 
  the end of the command queue list.
 */
void check_usart()
{   
    char rxChar;
    eusart1_status_t rxStatus;
        
    // Get the next character if there is one
    while (EUSART1_is_rx_ready()) 
    {           
        if (_power_down)
        {
            powerUp();
        }                           
        
        // Reset the power down timer
        INTERRUPT_GlobalInterruptDisable();   
        _power_down_timer = POWER_DOWN_TIME;
        INTERRUPT_GlobalInterruptEnable();   

        rxChar = (char)EUSART1_Read();
        rxStatus = EUSART1_get_last_status();

        // Convert to upper case
        if ((rxChar >= 'a') && (rxChar <='z')) {
            rxChar = rxChar - 'a' + 'A';
        }
        
        if(rxStatus.ferr) 
        {
            // Serial framing error. 
            // flash_led(2);
            _rs232_state = SKIP;
        }       
        else if ((rxChar == '\r') || (rxChar == '\n')) 
        {
            // End of line. Start processing the current command (if any)
            if ((_rs232_state == PARAM1) || (_rs232_state == PARAM2)) 
            { 
                if ((_cmd == 'F') || (_cmd == 'f')) 
                {
                    // Freeze or unfreeze the command queue
                    if (_param1 == 0)
                        _freeze_queue = false;
                    else
                        _freeze_queue = true;
                }                
                else
                {    
                    // push the command and any parameters onto the back of the command queue   
                    if (_queue_length < QUEUE_SIZE-1)
                    {
                        volatile command_t* cmdPtr = &_queue[_queue_back];
                        cmdPtr->cmd = _cmd;
                        cmdPtr->param1 = _param1_negative ? -_param1 : _param1;
                        cmdPtr->param2 = _param2_negative ? -_param2 : _param2;
                        _queue_length++;
                        _queue_back++;
                        if (_queue_back >= QUEUE_SIZE)
                            _queue_back = 0;                    
                    }
                }
            }

            _cmd = '\0';
            _param1 = 0;
            _param2 = 0;       
            _param1_negative = false;
            _param2_negative = false;
            _rs232_state = IDLE;
        }
        else if (_rs232_state == IDLE) 
        {
            // Check if the next command is for us
            if ((rxChar == '*') || (rxChar == _my_address)) 
            {
                // Yes it is, get ready for it
                _rs232_state = COMMAND;           
            }
            else
            {
                _rs232_state = SKIP;
            }
        } 
        else if (_rs232_state == COMMAND) 
        {
            if (rxChar == 'H')
            {
                // Halt - reset everything immediately ??? TODO 
                _rs232_state = SKIP;
            }
            else
            {
                // Remember the command until the <CR> and get ready to 
                // receive the first parameter (if any)
                _cmd = rxChar;
                _rs232_state = PARAM1;
            }
        }
        else if (_rs232_state == PARAM1)
        {
            // Received part of the first parameter. 
            if ((rxChar >= '0') && (rxChar <= '9'))
            {
                _param1 = (_param1 * 10) + rxChar - '0';
            }
            else if  (rxChar == '-') 
            {
                _param1_negative = true;
            }
            else if (rxChar == ',') 
            {
                // comma terminator - wait for the second parameter
                _rs232_state = PARAM2;
            }
            else
            {
                // Unexpected character
                // flash_led(1);
                _rs232_state = SKIP;            
            }
        } 
        else if (_rs232_state == PARAM2)
        {
            // Received part of the second parameter. 
            if ((rxChar >= '0') && (rxChar <= '9'))
            {
                _param2 = (_param2 * 10) + rxChar - '0';
            }
            else if (rxChar == '-') 
            {
                _param2_negative = true;
            }
            else
            {
                // Unexpected character
                // flash_led(1);
                _rs232_state = SKIP;            
            }
        }
        
    }   
}    


//============================================================================
//============================================================================
// Helper functions
//============================================================================
//============================================================================


void moveRelative1(int16_t steps)
{    
    INTERRUPT_GlobalInterruptDisable();
    
    _stepcount_1 = steps;
    _stepstaken_1 = 0;
    _slowcount_1 = 0;
           
    INTERRUPT_GlobalInterruptEnable();
}


void moveRelative2(int16_t steps)
{    
    INTERRUPT_GlobalInterruptDisable();
    
    _stepcount_2 = steps;
    _stepstaken_2 = 0;
    _slowcount_2 = 0;
    
    INTERRUPT_GlobalInterruptEnable();
}


/* Move motor 1 by the shortest route to absolute position (0 - 180) */
void seek1(uint16_t pos1)
{
    int16_t offset1 = pos1 - _position_1;
    
    if (offset1 >= 90)
        offset1 -= 180;
    else if (offset1 <= -90)
        offset1 += 180;
    
    if (offset1 != 0) 
    {
        INTERRUPT_GlobalInterruptDisable();   
        
        _stepcount_1 = offset1;
        _stepstaken_1 = 0;
        _slowcount_1 = 0;
        
        INTERRUPT_GlobalInterruptEnable();
    }       
}


/* Move motor 2 by the shortest route to absolute position (0 - 180) */
void seek2(uint16_t pos2)
{
    int16_t offset2 = pos2 - _position_2;
    
    if (offset2 >= 90)
        offset2 -= 180;
    else if (offset2 <= -90)
        offset2 += 180;

    if (offset2 != 0) 
    {
        INTERRUPT_GlobalInterruptDisable();   
        
        _stepcount_2 = offset2;       
        _stepstaken_2 = 0;
        _slowcount_2 = 0;

        INTERRUPT_GlobalInterruptEnable();
    }
            
}



/* Move motor 1 clockwise to absolute position (0 - 180) */
void seekClockwise1(uint16_t pos1)
{
    int16_t offset1 = pos1 - _position_1;
    
    if (offset1 < 0)
        offset1 += 180;
    
    if (offset1 != 0) 
    {
        INTERRUPT_GlobalInterruptDisable();   
        
        _stepcount_1 = offset1;
        _stepstaken_1 = 0;
        _slowcount_1 = 0;
        
        INTERRUPT_GlobalInterruptEnable();
    }       
}


/* Move motor 2 clockwise to absolute position (0 - 180) */
void seekClockwise2(uint16_t pos2)
{
    int16_t offset2 = pos2 - _position_2;
    
    if (offset2 < 0)
        offset2 += 180;
    
    if (offset2 != 0) 
    {
        INTERRUPT_GlobalInterruptDisable();   
        
        _stepcount_2 = offset2;
        _stepstaken_2 = 0;
        _slowcount_2 = 0;
        
        INTERRUPT_GlobalInterruptEnable();
    }       
}




/* Move motor 1 counter clockwise to absolute position (0 - 180) */
void seekAntiClockwise1(uint16_t pos1)
{
    int16_t offset1 = pos1 - _position_1;
    
    if (offset1 > 0)
        offset1 -= 180;
    
    if (offset1 != 0) 
    {
        INTERRUPT_GlobalInterruptDisable();   
        
        _stepcount_1 = offset1;
        _stepstaken_1 = 0;
        _slowcount_1 = 0;
        
        INTERRUPT_GlobalInterruptEnable();
    }       
}


/* Move motor 2 counter clockwise to absolute position (0 - 180) */
void seekAntiClockwise2(uint16_t pos2)
{
    int16_t offset2 = pos2 - _position_2;
    
    if (offset2 > 0)
        offset2 -= 180;
    
    if (offset2 != 0) 
    {
        INTERRUPT_GlobalInterruptDisable();   
        
        _stepcount_2 = offset2;
        _stepstaken_2 = 0;
        _slowcount_2 = 0;
        
        INTERRUPT_GlobalInterruptEnable();
    }       
}




/* Wait until both motors have stopped moving */
void wait()
{
    int16_t sc1;
    int16_t sc2;
    uint8_t ms1;
    uint8_t ms2;
    
    
    do
    {
        __delay_ms(5);
        check_usart();
        
        INTERRUPT_GlobalInterruptDisable();   
        sc1 = _stepcount_1;
        sc2 = _stepcount_2;
        ms1 = _microstep_1;
        ms2 = _microstep_2;
        INTERRUPT_GlobalInterruptEnable();  
        
    } while ((sc1!=0) || (sc2!=0) || (ms1!=0) || (ms2!=0));
    
}


// Wait for the led to stop flashing
void wait_for_flashing_to_stop()
{
    while ((_led_mode > 0) && (_led_mode < 254))
    {
        __delay_ms(50);
        check_usart();
    }
}


/* =================================================================== */
/* =================================================================== */
/* MAIN CODE                                                           */
/* =================================================================== */
/* =================================================================== */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // Set up the timer0 (microstepping) interrupt handler
    TMR0_SetInterruptHandler(&Timer0_int_handler);
    
    // Set up the timer1 (10ms timer) interrupt handler    
    TMR1_SetInterruptHandler(&Timer1_int_handler);


    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
    
    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    // Read the board select and chip select input pins to determine our address    
    // Board 0 addresses are "A" to "F",
    // Board 1 addresses are "G" to "L"
    // Board 2 addresses are "M" to "R"
    // Board 3 addresses are "S" to "X"    
    // 
    // Note that bit 0 of IO_CHIPSEL and IO_DIGITSEL is the MOST significant
    
    
    _my_address = 'A';
    if (IO_CHIPSEL0_GetValue()) _my_address += (char)4;    
    if (IO_CHIPSEL1_GetValue()) _my_address += (char)2;
    if (IO_CHIPSEL2_GetValue()) _my_address += (char)1;
    
    if (IO_DIGITSEL0_GetValue()) _my_address += (char)12; 
    if (IO_DIGITSEL1_GetValue()) _my_address += (char)6;
    
    
    // give the user time to move the fingers to the bottom (6 O'clock) position
    __delay_ms(2000);

    // Flash the LED to show the address and to prove we've booted up
    flash_led(1 + _my_address - 'A');
    wait_for_flashing_to_stop();
    
    // Move both motors to their starting position (fully up)
    seek1(0);
    seek2(0);
    wait();
    
    
    // Start of main loop
    while(1)
    {        
        check_usart();
       
        if ((_queue_length > 0) && (!_freeze_queue))
        {
            //volatile command_t* cmdPtr = &_queue[_queue_front];

            //char cmd = cmdPtr->cmd;
            //int16_t param1 = cmdPtr->param1;
            //int16_t param2 = cmdPtr->param2;
            
            volatile char cmd = _queue[_queue_front].cmd;
            volatile int16_t param1 = _queue[_queue_front].param1;
            volatile int16_t param2 = _queue[_queue_front].param2;

            _queue_length--;
            _queue_front++;
            if (_queue_front >= QUEUE_SIZE) 
            {
                _queue_front = 0;                    
            }

            switch (cmd)
            {
                case 'A': // Absolute position by shortest route. Param1&2 = 0 - 360, i.e.  *A0,0
                    if (param1 < 0) param1 = 0;
                    if (param1 > 360) param1 = 360;
                    if (param2 < 0) param2 = 0;
                    if (param2 > 360) param2 = 360;

                    seek1(param1/2);
                    seek2(param2/2);
                    
                    wait();

                    break;

                    
                case 'C': // Clockwise to absolute position. Param1&2 = 0 - 360, i.e.  *C270,90
                    if (param1 < 0) param1 = 0;
                    if (param1 > 360) param1 = 360;
                    if (param2 < 0) param2 = 0;
                    if (param2 > 360) param2 = 360;

                    seekClockwise1(param1/2);
                    seekClockwise2(param2/2);
                    
                    wait();

                    break;

                    
                case 'D': // Anti clockwise to absolute position. Param1&2 = 0 - 360, i.e.  *C270,90
                    if (param1 < 0) param1 = 0;
                    if (param1 > 360) param1 = 360;
                    if (param2 < 0) param2 = 0;
                    if (param2 > 360) param2 = 360;

                    seekAntiClockwise1(param1/2);
                    seekAntiClockwise2(param2/2);
                    
                    wait();

                    break;

                    
                case 'H': // Halt
                    // Should never get here, it its processed immediately by read_char()
                    break;
                                    

                // L = LED. Param1 0=Off , 1=On , 2=flash continuously, 3=Flash <param2> times
                case 'L': 
                    
                    if (param1 == 0)
                        // off
                        flash_led(0);
                    
                    else if (param1 == 1)
                        // permanently on
                        flash_led(255);
                    
                    else if (param1 == 2)
                        // permanently flashing
                        flash_led(245);
                    
                    else if (param1 == 3)
                    {
                        // flash <param2> times
                        if (param2<1) param2 = 1;
                        if (param2>253) param2 = 253;                                
                        flash_led(param2);
                        wait_for_flashing_to_stop();
                    }
                    
                    break;
                    

                case 'P': // Power Down, i.e. move the fingers to the bottom and 
                          // turn off current to the motors until the next command
                    
                    powerDown();
                    break;

                    
                case 'R': // Relative position. i.e. AR45,-45
                    if (param1 < -9999) param1 = -9999;
                    if (param1 > 9999) param1 = 9999;
                    if (param2 < -9999) param2 = -9999;
                    if (param2 > 9999) param2 = 9999;

                    moveRelative1(param1/2);
                    moveRelative2(param2/2);
                    
                    wait();
                    
                    break;

                case 'S': // Speed param1 (1-60) RPM 
                    if (param1 < 1) param1 = 1;
                    if (param1 > 60) param1 = 60;
                    
                    TMR0_Reload(_speeds[param1-1]);
                    
                    break;
                    
                case 'X': // Acceleration enable/disable
                    
                    if (param1 == 0)
                        _accelerate = false;
                    else
                        _accelerate = true;
                    
                    break;

            }

        }
        

    }
     
}
