#ifndef PANEL_H
#define PANEL_H


#include <Arduino.h>
#include "Motor.h"

// Useful constants
const char ALL[] = "*";
const char TOP_LINE[] = "ADGJMPSV";
const char MIDDLE_LINE[] = "BEHKNQTW";
const char BOTTOM_LINE[] = "CFILORUX";

const char TOP_RIGHT[] = "ADGJ";
const char MIDDLE_RIGHT[] = "BEHK";
const char BOTTOM_RIGHT[] = "CFIL";

const char TOP_LEFT[] = "MPSV";
const char MIDDLE_LEFT[] = "NQTW";
const char BOTTOM_LEFT[] = "ORUX";

const char COLUMN1[] = "VWX";
const char COLUMN2[] = "STU";
const char COLUMN3[] = "PQR";
const char COLUMN4[] = "MNO";
const char COLUMN5[] = "JKL";
const char COLUMN6[] = "GHI";
const char COLUMN7[] = "DEF";
const char COLUMN8[] = "ABC";

const char DIGIT1[7] = "STUVWX";
const char DIGIT2[7] = "MNOPQR";
const char DIGIT3[7] = "GHIJKL";
const char DIGIT4[7] = "ABCDEF";

const char DIGITS[4][7]  = { "STUVWX", "MNOPQR", "GHIJKL", "ABCDEF" };
const char COLUMNS[8][4] = { "VWX","STU","PQR","MNO","JKL","GHI","DEF","ABC" };
const char ROWS[3][9]    = { "ADGJMPSV","BEHKNQTW","CFILORUX" };

#define MOTOR_COUNT 48

// Class enum for the rotation direction for the Goto command
enum class Direction { Clockwise = 1, Anticlockwise = 2, Shortest = 3, Alternate = 4};

class Panel
{
private: 

  bool sleeping = false;
  
  int get_motor_number(const char motor);
  
  void send_command(const char function, const char* motors);
  void send_command(const char function, const int param1, const char* motors);
  void send_command(const char function, const int param1, const int param2, const char* motors);
  
  void send_int(const int num);
  void send_char(const char ch);

  Motor* motor_array[MOTOR_COUNT];

  
  
public:

  Panel();  // constructor
  ~Panel(); // destructor
  
  void power_down();
  void wake_up();
  void go_to(const int pos1, const int pos2, char* motors, Direction dir);
  void go_to(const int pos1, const int pos2, char motor, Direction dir);            
  void go_to(const int pos1, const int pos2, Direction dir);            
  
  void absolute(const unsigned int pos1, const unsigned int pos2, const char* motors);
  void absolute(const unsigned int pos1, const unsigned int pos2, const char motor);
  void absolute(const unsigned int pos1, const unsigned int pos2);
  
  void clockwise(const unsigned int pos1, const unsigned int pos2, const char* motors);
  void clockwise(const unsigned int pos1, const unsigned int pos2);
  
  void anticlockwise(const unsigned int pos1, const unsigned int pos2, const char* motors);
  void anticlockwise(const unsigned int pos1, const unsigned int pos2);
  
  void relative(const int pos1, const int pos2, const char* motors);
  void relative(const int pos1, const int pos2, const char motor);                        // overload
  void relative(const int pos1, const int pos2);  
  
  void speeed(const byte rpm, const char* motors);
  void speeed(const byte rpm);
  
  void freeze();
  void unfreeze();
    
  void acceleration_on();
  void acceleration_off();
  
  void led_on(const char* motors);
  void led_off(const char* motors);
  void led_flash(const unsigned char count, const char* motors);
  
  void set_digit (const unsigned char num, const unsigned char digit_no, Direction dir);

  unsigned long get_end_millis();
  void wait_for_completion();
  bool busy();
  
};


#endif
