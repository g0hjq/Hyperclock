#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Motor.h"
#include "MemoryFree.h"

extern int free_memory;

// Constructor
Motor::Motor(byte num)
{
  motor_number = num;
  reset();
}



void Motor::set_end_time()
{
    int fm = freeMemory(); free_memory = min(free_memory, fm); 

    degrees_to_move = abs(degrees_to_move);

    // adjust the degrees to move to compensate for the time taken by acceleration + deceleration (if enabled)
    // (It's only an approximation for now)
    if (acceleration)
    {
        if (degrees_to_move < 35)
            degrees_to_move *= 2;
        else
            degrees_to_move += 70;
    }

    // time taken to complete the move
    unsigned long milliseconds = ((166667L / (long)rpm) * (long)degrees_to_move) / 1000L;

    // Update the expected finish time
    unsigned long now = millis();
    if (end_millis > now)
        end_millis = end_millis + milliseconds;
    else
        end_millis = now + milliseconds;

   // Serial.print("# ");
   // Serial.print(motor_number);
   // Serial.print(": degrees="); Serial.print(degrees_to_move);
   // Serial.print(" rpm="); Serial.print(rpm);
   // Serial.print(" accel="); Serial.print(acceleration);
   // Serial.print(" millis="); Serial.print(milliseconds);
   // Serial.print(" now="); Serial.print(now);
   // Serial.print(" end="); Serial.print(end_millis);
}


void Motor::reset()
{
   rpm=30;
   current_position=180;
   degrees_to_move=0;
   acceleration=true;
   end_millis = 0;
}


void Motor::absolute(int param)
{
  if (param < 0) param = 0;
  if (param > 360) param = 360;

  degrees_to_move = param - current_position;

  if (degrees_to_move >= 180)
      degrees_to_move -= 360;
  else if (degrees_to_move <= -180)
      degrees_to_move += 360;
      
  set_end_time();
  
  current_position = param;
  //Serial.print(" pos=");
  //Serial.println(current_position);      
}


void Motor::clockwise(int param)
{
  if (param < 0) param = 0;
  if (param > 360) param = 360;

  degrees_to_move = param - current_position;
  
  if (degrees_to_move < 0)
      degrees_to_move += 360;

  set_end_time();
  
  current_position = param;    
  //Serial.print(" pos=");
  //Serial.println(current_position);      
}


void Motor::anticlockwise(int param)
{
  if (param < 0) param = 0;
  if (param > 360) param = 360;

  degrees_to_move = current_position - param;
  if (degrees_to_move < 0)
      degrees_to_move += 360;

  set_end_time();

  current_position = param;
  //Serial.print("# pos=");
  //Serial.println(current_position);      
}


void Motor::relative(int param)
{
    if (param < -9999) param = -9999;
    if (param > 9999) param = 9999;

    degrees_to_move = abs(param);
    set_end_time();

    current_position += param;
    
    while (current_position >= 360)
      current_position -= 360;

    while (current_position < 0)
      current_position += 360;
      
    //Serial.print("# pos=");
    //Serial.println(current_position);      
}


void Motor::speeed(int param)
{
    if (param < 5) param = 5;
    if (param > 60) param = 60;

    rpm = param;
}


void Motor::accelerate(int param)
{
    if (param == 0)
        acceleration = false;
    else
        acceleration = true;    
}


  
void Motor::process_command(char cmd, int param)
{
    switch (cmd)
    {
        case 'A':
            // Absolute
            absolute(param);
            break;

        case 'C':
            // Clockwise
            clockwise(param);
            break;

        case 'D':
            // Anticlockwise
            anticlockwise(param);
            break;

        case 'P':
            // Power down
            reset();
            break;

        case 'R':
            // Relative
            relative(param);
            break;

        case 'S':
            // speed
            speeed(param);
            break;

        case 'X':
            // acceleration
            accelerate(param);
            break;            
  }
}

  
bool Motor::busy()
{
  unsigned long now = millis();
  return (now <= end_millis);
}


unsigned long Motor::get_end_millis()
{
  return end_millis;
}
