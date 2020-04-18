#include "Panel.h"
#include "MemoryFree.h"

extern int free_memory;

// Constructor
Panel::Panel()
{
    Serial.begin(19200,SERIAL_8N1);
    wake_up();

    for (byte i=0; i<MOTOR_COUNT; i++)
    {
       motor_array[i] = new Motor(i);  
    }
}


// Destructor
Panel::~Panel()
{
    power_down();
}

void Panel::send_char(const char ch)
{
    if (!sleeping)
        Serial.print(ch);         
}


void Panel::send_int(const int num)
{
    char ch;
    int n = num;
    bool active = false;  

    if (n < 0)
    {
        ch = '-';
        send_char(ch);
        n = -n;
    }

    if (n >= 10000)
    {  
        ch = '0' + (n / 10000);
        send_char(ch);
        n = n % 10000;
        active = true;
    }

    if ((n >= 1000) || active)
    {  
        ch = '0' + (n / 1000);
        send_char(ch);
        n = n % 1000;
        active = true;
    }

    if ((n >= 100) || active)
    {  
        ch = '0' + (n / 100);
        send_char(ch);
        n = n % 100;
        active = true;
    }

    if ((n >= 10) || active)
    {  
        ch = '0' + (n / 10);
        send_char(ch);
        n = n % 10;
    }
  
    ch = '0' + n;
    send_char(ch);

    int fm = freeMemory(); free_memory = min(free_memory, fm); 
}



void Panel::send_command(const char function, const char* motors)
{
    if (*motors == '*')
    {
        // Send the command to all motors
        send_char('*');
        send_char(function);
        send_char('\n');
        
        for (int i=0; i<MOTOR_COUNT; i+=2)
        {
            motor_array[i]->process_command(function, 0);
            motor_array[i+1]->process_command(function, 0);        
        } 
    }
    else
    {
        // send the command to one or a group of motors    
        const char* ptr = motors;  
        while (*ptr)
        {
            char motor = *ptr;
        
            send_char(motor);
            send_char(function);
            send_char('\n');
    
            byte motor_num = get_motor_number(motor);
            motor_array[motor_num]->process_command(function, 0);
            motor_array[motor_num+1]->process_command(function, 0);
        
            ptr++;        
        }
    }

    int fm = freeMemory(); free_memory = min(free_memory, fm); 

}


void Panel::send_command(const char function, const int param1, const char* motors)
{
    if (*motors == '*')
    {
        // Send the command to all motors
        send_char('*');
        send_char(function);
        send_int(param1);
        send_char('\n');
        
        for (int i=0; i<MOTOR_COUNT; i+=2)
        {
            motor_array[i]->process_command(function, param1);
            motor_array[i+1]->process_command(function, param1);        
        } 
    }
    else
    {
        // send the command to one or a group of motors    
        const char* ptr = motors;  
        while (*ptr)
        {
            char motor = *ptr;
        
            send_char(motor);
            send_char(function);
            send_int(param1);
            send_char('\n');
    
            byte motor_num = get_motor_number(motor);
            motor_array[motor_num]->process_command(function, param1);
            motor_array[motor_num+1]->process_command(function, param1);
        
            ptr++;        
        }
    }
}

void Panel::send_command(const char function, const int param1, const int param2, const char* motors)
{
    if (*motors == '*')
    {
        // Send the command to all motors
        send_char('*');
        send_char(function);
        send_int(param1);
        send_char(',');
        send_int(param2);
        send_char('\n');
        
        for (int i=0; i<MOTOR_COUNT; i+=2)
        {
            motor_array[i]->process_command(function, param1);
            motor_array[i+1]->process_command(function, param2);        
        } 
    }
    else
    {
        // send the command to one or a group of motors    
        const char* ptr = motors;  
        while (*ptr)
        {
            char motor = *ptr;
        
            send_char(motor);
            send_char(function);
            send_int(param1);
            send_char(',');
            send_int(param2);
            send_char('\n');
    
            byte motor_num = get_motor_number(motor);
            motor_array[motor_num]->process_command(function, param1);
            motor_array[motor_num+1]->process_command(function, param2);
        
            ptr++;        
        }
    }
}

int Panel::get_motor_number(const char motor)
{
  return (motor - 'A') << 1;
}

void Panel::power_down()
{
  send_command('P', ALL);
  sleeping = true;  
}

void Panel::wake_up()
{
  sleeping = false;  

  Serial.print(F("\n\n"));
  Serial.print(F("*F0\n"));  // Unfreeze
  Serial.print(F("*X1\n"));  // acceleration on
  Serial.print("*S30\n"); // speed = 30 rpm  
}

void Panel::absolute(const unsigned int pos1, const unsigned int pos2, const char* motors)
{  
  send_command('A', pos1, pos2, motors);
}

void Panel::absolute(const unsigned int pos1, const unsigned int pos2, const char motor)
{
    char motors[2];
    motors[0] = motor;
    motors[1] = '\0';  
    send_command('A', pos1, pos2, motors);
}

void Panel::absolute(const unsigned int pos1, const unsigned int pos2)
{  
  send_command('A', pos1, pos2, ALL);
}


void Panel::clockwise(const unsigned int pos1, const unsigned int pos2, const char* motors)
{
  send_command('C', pos1, pos2, motors);
}

void Panel::clockwise(const unsigned int pos1, const unsigned int pos2)
{
  send_command('C', pos1, pos2, ALL);
}

void Panel::anticlockwise(const unsigned int pos1, const unsigned int pos2, const char* motors)
{
  send_command('D', pos1, pos2, motors);
}

void Panel::anticlockwise(const unsigned int pos1, const unsigned int pos2)
{
  send_command('D', pos1, pos2, ALL);
}

void Panel::relative(const int pos1, const int pos2, const char* motors)
{
  send_command('R', pos1, pos2, motors);
}

void Panel::relative(const int pos1, const int pos2, const char motor)
{
    char motors[2];
    motors[0] = motor;
    motors[1] = '\0';  
    send_command('R', pos1, pos2, motors);
}

void Panel::relative(const int pos1, const int pos2)
{
  send_command('R', pos1, pos2, ALL);
}

void Panel::speeed(const byte rpm, const char* motors)
{
  send_command('S', rpm, motors);
}

void Panel::speeed(const byte rpm)
{
  send_command('S', rpm, ALL);
}

void Panel::go_to(const int pos1, const int pos2, char* motors, Direction dir)
{
   switch (dir) 
   {
      case Direction::Clockwise:
          send_command('C', pos1, pos2, motors);        
          break;
          
      case Direction::Anticlockwise:
          send_command('D', pos1, pos2, motors);        
          break;
          
      case Direction::Shortest:
          send_command('A', pos1, pos2, motors);
          break;   
          
      case Direction::Alternate:
          char buff[2];
          char* ptr = motors;
          char ch;     
               
          while (ch = *ptr, ch)
          {           
              Serial.print("#");
              Serial.println(ch);
              
              buff[0] = ch;
              buff[1] = '\0';  
              
              switch (ch)
              {
                  case 'A':
                  case 'B':
                  case 'C':
                  case 'G':
                  case 'H':
                  case 'I':
                  case 'M':
                  case 'N':
                  case 'P':
                  case 'S':
                  case 'T':
                  case 'U':
                      send_command('C', pos1, pos2, buff);          
                      break;
                  default:
                      send_command('D', pos1, pos2, buff);          
                       break;                
              }

              ptr++;
          }
   }
}



void Panel::go_to(const int pos1, const int pos2, char motor, Direction dir)
{
    char motors[2];
    motors[0] = motor;
    motors[1] = '\0';
    go_to(pos1, pos2, motors, dir);
}


  void Panel::go_to(const int pos1, const int pos2, Direction dir)
{
   switch (dir) 
   {
      case Direction::Clockwise:
          send_command('C', pos1, pos2, ALL);        
          break;
          
      case Direction::Anticlockwise:
          send_command('D', pos1, pos2, ALL);        
          break;
          
      case Direction::Shortest:
          send_command('A', pos1, pos2, ALL);
          break;          

      case Direction::Alternate:
          send_command('C', pos1, pos2, "ABCGHIMNOSTU");
          send_command('D', pos1, pos2, "DEFJKLPQRVWX");
          break;             
   }
}

void Panel::set_digit (const unsigned char num, const unsigned char digit_no, Direction dir)
{
    const char* motor_p = DIGITS[digit_no];
  
    switch (num)
    {
        case 1:
            go_to( 180, 225, *motor_p, dir);
            go_to(   0, 180, *(motor_p+1), dir);
            go_to(   0,   0, *(motor_p+2), dir);
            go_to( 225, 225, *(motor_p+3), dir);
            go_to( 225, 225, *(motor_p+4), dir);
            go_to( 225, 225, *(motor_p+5), dir);
            break;

        case 2:
            go_to( 180, 270, *motor_p, dir);
            go_to(   0, 270, *(motor_p+1), dir);
            go_to( 270, 270, *(motor_p+2), dir);
            go_to(  90,  90, *(motor_p+3), dir);
            go_to( 180,  90, *(motor_p+4), dir);
            go_to(   0,  90, *(motor_p+5), dir);
            break;

        case 3:
            go_to( 270, 225, *motor_p, dir);
            go_to( 180, 270, *(motor_p+1), dir);
            go_to(   0, 270, *(motor_p+2), dir);
            go_to(  90,  90, *(motor_p+3), dir);
            go_to(  45,  90, *(motor_p+4), dir);
            go_to(  90,  90, *(motor_p+5), dir);
            break;

        case 4:
            go_to( 180, 180, *motor_p, dir);
            go_to(   0, 180, *(motor_p+1), dir);
            go_to(   0,   0, *(motor_p+2), dir);
            go_to( 180, 180, *(motor_p+3), dir);
            go_to(   0,  90, *(motor_p+4), dir);
            go_to( 225, 225, *(motor_p+5), dir);
            break;

        case 5:
            go_to( 270, 270, *motor_p, dir);
            go_to( 180, 270, *(motor_p+1), dir);
            go_to(   0, 270, *(motor_p+2), dir);
            go_to( 180,  90, *(motor_p+3), dir);
            go_to(   0,  90, *(motor_p+4), dir);
            go_to(  90,  90, *(motor_p+5), dir);
            break;

        case 6:
            go_to( 270, 270, *motor_p, dir);
            go_to( 180, 270, *(motor_p+1), dir);
            go_to(   0, 270, *(motor_p+2), dir);
            go_to(  90, 180, *(motor_p+3), dir);
            go_to(   0, 180, *(motor_p+4), dir);
            go_to(   0,  90, *(motor_p+5), dir);
            break;

        case 7:
            go_to( 180, 270, *motor_p, dir);
            go_to(   0, 180, *(motor_p+1), dir);
            go_to(   0,   0, *(motor_p+2), dir);
            go_to(  90,  90, *(motor_p+3), dir);
            go_to( 225, 225, *(motor_p+4), dir);
            go_to( 225, 225, *(motor_p+5), dir);
            break;

        case 8:
            go_to( 180, 270, *motor_p, dir);
            go_to( 180, 270, *(motor_p+1), dir);
            go_to(   0, 270, *(motor_p+2), dir);
            go_to( 180,  90, *(motor_p+3), dir);
            go_to( 180,  90, *(motor_p+4), dir);
            go_to(   0,  90, *(motor_p+5), dir);
            break;

        case 9:
            go_to( 180, 270, *motor_p, dir);
            go_to(   0, 180, *(motor_p+1), dir);
            go_to(   0, 270, *(motor_p+2), dir);
            go_to(  90, 180, *(motor_p+3), dir);
            go_to(   0,  90, *(motor_p+4), dir);
            go_to(  90,  90, *(motor_p+5), dir);
            break;

        case 0:
            go_to( 270, 180, *motor_p, dir);
            go_to(   0, 180, *(motor_p+1), dir);
            go_to(   0, 270, *(motor_p+2), dir);
            go_to(  90, 180, *(motor_p+3), dir);
            go_to( 180,   0, *(motor_p+4), dir);
            go_to(   0,  90, *(motor_p+5), dir);
            break;

    }
    
}
      


void Panel::freeze()
{
  send_command('F', 1, ALL);
}


void Panel::unfreeze()
{
  send_command('F', 0, ALL);
}

void Panel::acceleration_on()
{
  send_command('X', 1, ALL);
}

void Panel::acceleration_off()
{
  send_command('X', 0, ALL);
}

void Panel::led_on(const char* motors)
{
  send_command('L', 1, motors);
}

void Panel::led_off(const char* motors)
{
  send_command('L', 0, motors);
}

void Panel::led_flash(const unsigned char count, const char* motors)
{
  send_command('L', 3, count, motors);                                                            
}


unsigned long Panel::get_end_millis()
{
    unsigned long end_millis = 0;

    for (int i=0; i<MOTOR_COUNT; i++)
    {
        unsigned long end_time = motor_array[i]->get_end_millis();
        
        if (end_time > end_millis)
            end_millis = end_time;       
    }

    return end_millis;
}


void Panel::wait_for_completion()
{
    unsigned long end_millis = get_end_millis();

    do 
    {
    } 
    while (millis() <= end_millis);    
}

bool Panel::busy()
{
    bool is_busy = false;

    for (int i=0; i<MOTOR_COUNT; i++)
    {
        if (motor_array[i]->busy())
        {
            is_busy = true;
        }
    }

    return is_busy;
}
