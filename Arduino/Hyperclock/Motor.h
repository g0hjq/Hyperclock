#ifndef MOTOR_H
#define MOTOR_H


#include <Arduino.h>

class Motor
{
  
private: 

  byte motor_number;
  int current_position;
  byte rpm;
  bool acceleration;
  unsigned long end_millis;
  int degrees_to_move;

  void set_end_time();

  void absolute(int param);
  void clockwise(int param);
  void anticlockwise(int param);
  void relative(int param);
  void speeed(int param);
  void accelerate(int param);

   
public:

  
  // Constructor
  Motor(byte num);

  void reset();
  
  void process_command(char cmd, int param);

  bool busy();
  
  unsigned long get_end_millis();
  
};

#endif
