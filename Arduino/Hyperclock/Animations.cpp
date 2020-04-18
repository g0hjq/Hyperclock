#include <LiquidCrystal.h>
#include "Panel.h"
#include "Animations.h"

extern LiquidCrystal lcd;
extern Panel p;
extern void wait(unsigned int milliseconds);
extern void wait();

byte i;
byte j;

void animation_1()
{
    p.acceleration_on();
    
    p.speeed(20);
    p.absolute(90,270);
    wait();
    p.speeed(60);

    for (byte i=0; i<8; i++)
    {
        const char* motor_p = COLUMNS[i];
        p.go_to(90, 90, *motor_p, Direction::Clockwise);
        p.go_to(90, 90, *(motor_p+1), Direction::Clockwise);
        p.go_to(90, 90, *(motor_p+2), Direction::Clockwise);
        wait();
    }

    for (signed char x=7; x>=0; x--)
    {
        const char* motor_p = COLUMNS[x];

        p.go_to(270, 90, *motor_p, Direction::Anticlockwise);
        p.go_to(270, 90, *(motor_p+1), Direction::Anticlockwise);
        p.go_to(270, 90, *(motor_p+2), Direction::Anticlockwise);
        wait();
    }
}


void animation_2()
{
    p.acceleration_on();

    p.absolute(0,0);
    p.speeed(8, COLUMN1);
    p.speeed(8, COLUMN8);
    
    p.speeed(10, COLUMN2);
    p.speeed(10, COLUMN7);
    
    p.speeed(12, COLUMN3);
    p.speeed(12, COLUMN6);
    
    p.speeed(14, COLUMN4);
    p.speeed(14, COLUMN5);
    wait();

    p.relative(360*4, -360*4);
    wait();    
}


void animation_3()
{
    p.speeed(15);

    const int degs = 360*4;    
    const int degsminus = -degs; 

    for (i=0; i<4; i++)
    {
        p.relative(degs, degs, DIGITS[i][0]);
        p.relative(degsminus, degsminus, DIGITS[i][1]);
        p.relative(degs, degs, DIGITS[i][2]);
        p.relative(degsminus, degsminus, DIGITS[i][3]);
        p.relative(degs, degs, DIGITS[i][4]);
        p.relative(degsminus, degsminus, DIGITS[i][5]);
    }
    wait();
}


void animation_4()
{
    p.speeed(20);
    p.acceleration_on();

    for (i=0; i<4; i++)
    {
        p.go_to(0,270, DIGITS[i][0], Direction::Shortest);
        p.go_to(180,270, DIGITS[i][1], Direction::Shortest);
        p.go_to(0,270, DIGITS[i][2], Direction::Shortest);
        p.go_to(0,90, DIGITS[i][3], Direction::Shortest);
        p.go_to(180,90, DIGITS[i][4], Direction::Shortest);
        p.go_to(0,90, DIGITS[i][5], Direction::Shortest);
    }
    wait();

    for (i=0; i<5; i++)
    {
        for (j=0; j<4; j++)
        {
            p.relative(180,-180, DIGITS[j][3]);
            delay(150);
            p.relative(-180,180, DIGITS[j][4]);
            delay(150);
            p.relative(180,-180, DIGITS[j][5]);
            delay(150);
            p.relative(-180,180, DIGITS[j][0]);
            delay(150);
            p.relative(180,-180, DIGITS[j][1]);
            delay(150);
            p.relative(-180,180, DIGITS[j][2]);
            delay(150);
        }
        wait(500);
    }
}


void animation_5()
{
    p.speeed(20);
    p.acceleration_on();

    p.absolute(90, 270, TOP_LINE);
    wait();
    p.absolute(90, 270, MIDDLE_LINE);
    wait();
    p.absolute(90, 270, BOTTOM_LINE);
    wait(2000);

    p.relative(1440, -1440);
    wait(1000);

    p.relative(720, 720);
    wait(1000);
    p.relative(-720, -720);    
}



void animation_6()
{
    p.speeed(15);
    p.acceleration_on();

    // move all fingers to top
    p.absolute(0,0);
    wait(1000);

    // move to horizontal, one row at a time
    p.relative(-90,90, TOP_LINE);
    wait(); 
    
    p.relative(-90,90, MIDDLE_LINE);
    wait(); 
    
    p.relative(-90,90, BOTTOM_LINE);
    wait(1000);

    // rotate all 2 revolutions in oposite direction
    p.relative(-720, 720);
    wait(1000);
}

 
void animation_7()
{
    p.acceleration_on();
    p.speeed(10);
    
    p.absolute(0,0);
    wait(1500);
    
    p.absolute(90,270);
    wait(500);
    
    p.speeed(16, COLUMN8);
    p.speeed(17, COLUMN7);
    p.speeed(18, COLUMN6);
    p.speeed(19, COLUMN5);
    p.speeed(20, COLUMN4);
    p.speeed(21, COLUMN3);
    p.speeed(22, COLUMN2);
    p.speeed(23, COLUMN1);

    p.relative(1080, 1080);
    wait(500);
    
    p.relative(-1080, -1080);
    wait(2000);
      
    p.speeed(12, COLUMN8);
    p.speeed(12, COLUMN1);
    
    p.speeed(16, COLUMN7);
    p.speeed(16, COLUMN2);
    
    p.speeed(20, COLUMN6);
    p.speeed(20, COLUMN3);
    
    p.speeed(24, COLUMN5);
    p.speeed(24, COLUMN4);

    p.relative(1080, 1080, COLUMN1);
    p.relative(1080, 1080, COLUMN2);
    p.relative(1080, 1080, COLUMN3);
    p.relative(1080, 1080, COLUMN4);
    p.relative(-1080, -1080, COLUMN5);
    p.relative(-1080, -1080, COLUMN6);
    p.relative(-1080, -1080, COLUMN7);
    p.relative(-1080, -1080, COLUMN8);
    wait(500);
    
    p.relative(-1080, -1080, COLUMN1);
    p.relative(-1080, -1080, COLUMN2);
    p.relative(-1080, -1080, COLUMN3);
    p.relative(-1080, -1080, COLUMN4);
    p.relative(1080, 1080, COLUMN5);
    p.relative(1080, 1080, COLUMN6);
    p.relative(1080, 1080, COLUMN7);
    p.relative(1080, 1080, COLUMN8);
    wait();
}

    


void animation_8()
{   
    p.speeed(30);
    p.acceleration_off();

    p.absolute(90,270);
    wait(1000);
    
    p.speeed(60);
    p.acceleration_on();

    p.absolute(270, 270, "A");
    p.absolute(90, 90, "V");
    wait();
    
    p.absolute(270, 270, "D");
    p.absolute(90, 90, "S");
    wait();
    
    p.absolute(270, 270, "G");
    p.absolute(90, 90, "P");
    wait();
    
    p.absolute(270, 270, "J");
    p.absolute(90, 90, "M");
    wait();
    
    p.absolute(270, 270, "B");
    p.absolute(90, 90, "W");
    wait();
    
    p.absolute(270, 270, "E");
    p.absolute(90, 90, "T");
    wait();
    
    p.absolute(270, 270, "H");
    p.absolute(90, 90, "Q");
    wait();
    
    p.absolute(270, 270, "K");
    p.absolute(90, 90, "N");
    wait();
    
    p.absolute(270, 270, "C");
    p.absolute(90, 90, "X");
    wait();
    
    p.absolute(270, 270, "F");
    p.absolute(90, 90, "U");
    wait();
    
    p.absolute(270, 270, "I");
    p.absolute(90, 90, "R");
    wait();
    
    p.absolute(270, 270, "L");
    p.absolute(90, 90, "O");
    wait();

    // Now undo it
    p.absolute(90, 270, "A");
    p.absolute(90, 270, "V");
    wait();
    
    p.absolute(90, 270, "D");
    p.absolute(90, 270, "S");
    wait();
    
    p.absolute(90, 270, "G");
    p.absolute(90, 270, "P");
    wait();
    
    p.absolute(90, 270, "J");
    p.absolute(90, 270, "M");
    wait();
    
    p.absolute(90, 270, "B");
    p.absolute(90, 270, "W");
    wait();
    
    p.absolute(90, 270, "E");
    p.absolute(90, 270, "T");
    wait();
    
    p.absolute(90, 270, "H");
    p.absolute(90, 270, "Q");
    wait();
    
    p.absolute(90, 270, "K");
    p.absolute(90, 270, "N");
    wait();
    
    p.absolute(90, 270, "C");
    p.absolute(90, 270, "X");
    wait();
    
    p.absolute(90, 270, "F");
    p.absolute(90, 270, "U");
    wait();
    
    p.absolute(90, 270, "I");
    p.absolute(90, 270, "R");
    wait();
    
    p.absolute(90, 270, "L");
    p.absolute(90, 270, "O");
    wait();
    
}






void animation_9()
{
    p.speeed(40);
    p.acceleration_on();

    p.absolute(0,0);

    for (i=0; i<4; i++)
    {
        p.relative(90,0);
        wait();
        p.relative(0,90);  
        wait();
    }

    for (i=0; i<4; i++)
    {
        p.relative(-90,0);
        wait();
        p.relative(0,-90);  
        wait();
    }

}




void animation_10()
{
    p.speeed(30);
    p.acceleration_on();
    
    p.absolute(90,90,COLUMN1);
    p.absolute(270,270,COLUMN8);
    wait(700);
    
    p.absolute(90,90,COLUMN2);
    p.absolute(270,270,COLUMN7);
    wait(700);
    
    p.absolute(90,90,COLUMN3);
    p.absolute(270,270,COLUMN6);
    wait(700);
    
    p.absolute(90,90,COLUMN4);
    p.absolute(270,270,COLUMN5);

    wait(2000);
        
    p.speeed(5, COLUMN1);
    p.speeed(5, COLUMN8);    
    p.speeed(6, COLUMN2);
    p.speeed(6, COLUMN7);    
    p.speeed(7, COLUMN3);
    p.speeed(7, COLUMN6);    
    p.speeed(8, COLUMN4);
    p.speeed(8, COLUMN5);
    
    p.absolute(45, 45, TOP_LEFT);
    p.absolute(45, 135, MIDDLE_LEFT);
    p.absolute(135, 135, BOTTOM_LEFT);
    p.absolute(315, 315, TOP_RIGHT);
    p.absolute(315, 225, MIDDLE_RIGHT);
    p.absolute(225, 225, BOTTOM_RIGHT);
    wait(3000);
    
    p.absolute(  0,   0, TOP_LINE);
    p.absolute(  0, 180, MIDDLE_LINE);
    p.absolute(180, 180, BOTTOM_LINE);
    wait(3000);

    p.absolute(315, 45);
    wait(3000);
    p.absolute(225, 135);
    wait(3000);
    p.relative(180, 180);    
    wait();
}


void animation_11()
{
    p.speeed(10);
    p.acceleration_on();

    p.absolute(90,90, DIGIT1);
    p.absolute(90,90, DIGIT2);
    p.absolute(270,270, DIGIT3);
    p.absolute(270,270, DIGIT4);
    wait(2000);

    p.speeed(12,"KN");
    p.speeed(11,"JHLMQO");
    p.speeed(10,"GEIPTR");
    p.speeed(9,"DBFSWU");
    p.speeed(8,"ACVX");
    
    p.relative(-1440,-1440,"ABCDEFGHIJKL");
    p.relative(1440,1440,"MNOPQRSTUVWX");    
    wait();
}


void animation_12()
{
    p.speeed(10);
    p.acceleration_on();

    p.go_to(225,225, Direction::Clockwise);
    wait(2000);

    p.speeed(14,"X");
    p.speeed(13,"WU");
    p.speeed(12,"VTR");
    p.speeed(11,"SQO");
    p.speeed(10,"PNL");
    p.speeed(9,"MKI");
    p.speeed(8,"JHF");
    p.speeed(7,"GEC");
    p.speeed(6,"DB");
    p.speeed(5,"A");
    
    p.relative(-1440,1440);
    
    wait();
}



void animation_13()
{
    p.speeed(15);
    p.acceleration_off();

    p.relative(45,45);
    p.clockwise(225,45);
    wait(1000);

    for (i=0; i<2; i++)
    {
        // 1L
        p.relative(45, 0, COLUMN1);
        wait();
    
        // 1R 2R
        p.relative(0, 45, COLUMN1);
        p.relative(0, 45, COLUMN2);
        wait();
    
        // 1L 2L 3L
        p.relative(45, 0, COLUMN1);
        p.relative(45, 0, COLUMN2);
        p.relative(45, 0, COLUMN3);
        wait();
    
        // 2R 3R 4R
        p.relative(0, 45, COLUMN2);
        p.relative(0, 45, COLUMN3);
        p.relative(0, 45, COLUMN4);
        wait();
    
        // 3L 4L 5L
        p.relative(45, 0, COLUMN3);
        p.relative(45, 0, COLUMN4);
        p.relative(45, 0, COLUMN5);
        wait();
    
        // 4R 5R 6R
        p.relative(0, 45, COLUMN4);
        p.relative(0, 45, COLUMN5);
        p.relative(0, 45, COLUMN6);
        wait();
    
        // 5L 6L 7L
        p.relative(45, 0, COLUMN5);
        p.relative(45, 0, COLUMN6);
        p.relative(45, 0, COLUMN7);
        wait();
    
        // 6R 7R 8R
        p.relative(0, 45, COLUMN6);
        p.relative(0, 45, COLUMN7);
        p.relative(0, 45, COLUMN8);
        wait();
    
        // 7L 8L
        p.relative(45, 0, COLUMN7);
        p.relative(45, 0, COLUMN8);
        wait();
    
        // 8R
        p.relative(0, 45, COLUMN8);
        wait();

    }

    p.relative(360,360);
    p.clockwise(180, 0);
    wait();
}


// execute one of the animation functions by number
void execute_animation(byte number)
{
    lcd.clear();
    lcd.print(F("Animation "));
    lcd.print(number);
    
    switch (number)
    {
        case 1:
            animation_1();
            break;
            
        case 2:
            animation_2();
            break;
            
        case 3:
            animation_3();
            break;
            
        case 4:
            animation_4();
            break;
            
        case 5:
            animation_5();
            break;
            
        case 6:
            animation_6();
            break;
            
        case 7:
            animation_7();
            break;
            
        case 8:
            animation_8();
            break;
            
        case 9:
            animation_9();
            break;
            
        case 10:
            animation_10();
            break;
            
        case 11:
            animation_11();
            break;
            
        case 12:
            animation_12();
            break;
            
        case 13:
            animation_13();
            break;
           
    }
    wait();

    lcd.clear();
}



void do_random_animations(byte count)
{
    for (int i = 0; i<count; i++)
    {
        execute_animation(random(0, NUMBER_OF_ANIMATIONS));
        wait();
    }
  
}
