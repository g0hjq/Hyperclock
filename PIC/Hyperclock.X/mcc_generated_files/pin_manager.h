/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F15355
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above
        MPLAB 	          :  MPLAB X 5.20	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_CHIPSEL0 aliases
#define IO_CHIPSEL0_TRIS                 TRISAbits.TRISA0
#define IO_CHIPSEL0_LAT                  LATAbits.LATA0
#define IO_CHIPSEL0_PORT                 PORTAbits.RA0
#define IO_CHIPSEL0_WPU                  WPUAbits.WPUA0
#define IO_CHIPSEL0_OD                   ODCONAbits.ODCA0
#define IO_CHIPSEL0_ANS                  ANSELAbits.ANSA0
#define IO_CHIPSEL0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define IO_CHIPSEL0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define IO_CHIPSEL0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define IO_CHIPSEL0_GetValue()           PORTAbits.RA0
#define IO_CHIPSEL0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define IO_CHIPSEL0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define IO_CHIPSEL0_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define IO_CHIPSEL0_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define IO_CHIPSEL0_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define IO_CHIPSEL0_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define IO_CHIPSEL0_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define IO_CHIPSEL0_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set IO_CHIPSEL1 aliases
#define IO_CHIPSEL1_TRIS                 TRISAbits.TRISA1
#define IO_CHIPSEL1_LAT                  LATAbits.LATA1
#define IO_CHIPSEL1_PORT                 PORTAbits.RA1
#define IO_CHIPSEL1_WPU                  WPUAbits.WPUA1
#define IO_CHIPSEL1_OD                   ODCONAbits.ODCA1
#define IO_CHIPSEL1_ANS                  ANSELAbits.ANSA1
#define IO_CHIPSEL1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define IO_CHIPSEL1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define IO_CHIPSEL1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define IO_CHIPSEL1_GetValue()           PORTAbits.RA1
#define IO_CHIPSEL1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define IO_CHIPSEL1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define IO_CHIPSEL1_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define IO_CHIPSEL1_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define IO_CHIPSEL1_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define IO_CHIPSEL1_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define IO_CHIPSEL1_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define IO_CHIPSEL1_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set IO_CHIPSEL2 aliases
#define IO_CHIPSEL2_TRIS                 TRISAbits.TRISA2
#define IO_CHIPSEL2_LAT                  LATAbits.LATA2
#define IO_CHIPSEL2_PORT                 PORTAbits.RA2
#define IO_CHIPSEL2_WPU                  WPUAbits.WPUA2
#define IO_CHIPSEL2_OD                   ODCONAbits.ODCA2
#define IO_CHIPSEL2_ANS                  ANSELAbits.ANSA2
#define IO_CHIPSEL2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define IO_CHIPSEL2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define IO_CHIPSEL2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define IO_CHIPSEL2_GetValue()           PORTAbits.RA2
#define IO_CHIPSEL2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define IO_CHIPSEL2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define IO_CHIPSEL2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define IO_CHIPSEL2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define IO_CHIPSEL2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define IO_CHIPSEL2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define IO_CHIPSEL2_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define IO_CHIPSEL2_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set IO_DIGITSEL1 aliases
#define IO_DIGITSEL1_TRIS                 TRISAbits.TRISA3
#define IO_DIGITSEL1_LAT                  LATAbits.LATA3
#define IO_DIGITSEL1_PORT                 PORTAbits.RA3
#define IO_DIGITSEL1_WPU                  WPUAbits.WPUA3
#define IO_DIGITSEL1_OD                   ODCONAbits.ODCA3
#define IO_DIGITSEL1_ANS                  ANSELAbits.ANSA3
#define IO_DIGITSEL1_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define IO_DIGITSEL1_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define IO_DIGITSEL1_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define IO_DIGITSEL1_GetValue()           PORTAbits.RA3
#define IO_DIGITSEL1_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define IO_DIGITSEL1_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define IO_DIGITSEL1_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define IO_DIGITSEL1_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define IO_DIGITSEL1_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define IO_DIGITSEL1_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define IO_DIGITSEL1_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define IO_DIGITSEL1_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set IO_DIGITSEL0 aliases
#define IO_DIGITSEL0_TRIS                 TRISAbits.TRISA4
#define IO_DIGITSEL0_LAT                  LATAbits.LATA4
#define IO_DIGITSEL0_PORT                 PORTAbits.RA4
#define IO_DIGITSEL0_WPU                  WPUAbits.WPUA4
#define IO_DIGITSEL0_OD                   ODCONAbits.ODCA4
#define IO_DIGITSEL0_ANS                  ANSELAbits.ANSA4
#define IO_DIGITSEL0_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define IO_DIGITSEL0_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define IO_DIGITSEL0_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define IO_DIGITSEL0_GetValue()           PORTAbits.RA4
#define IO_DIGITSEL0_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define IO_DIGITSEL0_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define IO_DIGITSEL0_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define IO_DIGITSEL0_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define IO_DIGITSEL0_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define IO_DIGITSEL0_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define IO_DIGITSEL0_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define IO_DIGITSEL0_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set IO_LED aliases
#define IO_LED_TRIS                 TRISAbits.TRISA5
#define IO_LED_LAT                  LATAbits.LATA5
#define IO_LED_PORT                 PORTAbits.RA5
#define IO_LED_WPU                  WPUAbits.WPUA5
#define IO_LED_OD                   ODCONAbits.ODCA5
#define IO_LED_ANS                  ANSELAbits.ANSA5
#define IO_LED_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define IO_LED_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define IO_LED_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define IO_LED_GetValue()           PORTAbits.RA5
#define IO_LED_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define IO_LED_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define IO_LED_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define IO_LED_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define IO_LED_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define IO_LED_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define IO_LED_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define IO_LED_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set IO_RB0 aliases
#define IO_RB0_TRIS                 TRISBbits.TRISB0
#define IO_RB0_LAT                  LATBbits.LATB0
#define IO_RB0_PORT                 PORTBbits.RB0
#define IO_RB0_WPU                  WPUBbits.WPUB0
#define IO_RB0_OD                   ODCONBbits.ODCB0
#define IO_RB0_ANS                  ANSELBbits.ANSB0
#define IO_RB0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define IO_RB0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define IO_RB0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define IO_RB0_GetValue()           PORTBbits.RB0
#define IO_RB0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define IO_RB0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define IO_RB0_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define IO_RB0_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define IO_RB0_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define IO_RB0_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define IO_RB0_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define IO_RB0_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set IO_RB1 aliases
#define IO_RB1_TRIS                 TRISBbits.TRISB1
#define IO_RB1_LAT                  LATBbits.LATB1
#define IO_RB1_PORT                 PORTBbits.RB1
#define IO_RB1_WPU                  WPUBbits.WPUB1
#define IO_RB1_OD                   ODCONBbits.ODCB1
#define IO_RB1_ANS                  ANSELBbits.ANSB1
#define IO_RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define IO_RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define IO_RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define IO_RB1_GetValue()           PORTBbits.RB1
#define IO_RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define IO_RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define IO_RB1_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define IO_RB1_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define IO_RB1_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define IO_RB1_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define IO_RB1_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define IO_RB1_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set IO_MOTOR2B aliases
#define IO_MOTOR2B_TRIS                 TRISBbits.TRISB2
#define IO_MOTOR2B_LAT                  LATBbits.LATB2
#define IO_MOTOR2B_PORT                 PORTBbits.RB2
#define IO_MOTOR2B_WPU                  WPUBbits.WPUB2
#define IO_MOTOR2B_OD                   ODCONBbits.ODCB2
#define IO_MOTOR2B_ANS                  ANSELBbits.ANSB2
#define IO_MOTOR2B_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define IO_MOTOR2B_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define IO_MOTOR2B_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define IO_MOTOR2B_GetValue()           PORTBbits.RB2
#define IO_MOTOR2B_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define IO_MOTOR2B_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define IO_MOTOR2B_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define IO_MOTOR2B_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define IO_MOTOR2B_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define IO_MOTOR2B_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define IO_MOTOR2B_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define IO_MOTOR2B_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set IO_MOTOR2A aliases
#define IO_MOTOR2A_TRIS                 TRISBbits.TRISB3
#define IO_MOTOR2A_LAT                  LATBbits.LATB3
#define IO_MOTOR2A_PORT                 PORTBbits.RB3
#define IO_MOTOR2A_WPU                  WPUBbits.WPUB3
#define IO_MOTOR2A_OD                   ODCONBbits.ODCB3
#define IO_MOTOR2A_ANS                  ANSELBbits.ANSB3
#define IO_MOTOR2A_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define IO_MOTOR2A_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define IO_MOTOR2A_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define IO_MOTOR2A_GetValue()           PORTBbits.RB3
#define IO_MOTOR2A_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define IO_MOTOR2A_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define IO_MOTOR2A_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define IO_MOTOR2A_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define IO_MOTOR2A_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define IO_MOTOR2A_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define IO_MOTOR2A_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define IO_MOTOR2A_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set IO_MOTOR1B aliases
#define IO_MOTOR1B_TRIS                 TRISBbits.TRISB4
#define IO_MOTOR1B_LAT                  LATBbits.LATB4
#define IO_MOTOR1B_PORT                 PORTBbits.RB4
#define IO_MOTOR1B_WPU                  WPUBbits.WPUB4
#define IO_MOTOR1B_OD                   ODCONBbits.ODCB4
#define IO_MOTOR1B_ANS                  ANSELBbits.ANSB4
#define IO_MOTOR1B_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define IO_MOTOR1B_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define IO_MOTOR1B_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define IO_MOTOR1B_GetValue()           PORTBbits.RB4
#define IO_MOTOR1B_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define IO_MOTOR1B_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define IO_MOTOR1B_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define IO_MOTOR1B_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define IO_MOTOR1B_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define IO_MOTOR1B_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define IO_MOTOR1B_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define IO_MOTOR1B_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set ICSPCLK aliases
#define ICSPCLK_TRIS                 TRISBbits.TRISB6
#define ICSPCLK_LAT                  LATBbits.LATB6
#define ICSPCLK_PORT                 PORTBbits.RB6
#define ICSPCLK_WPU                  WPUBbits.WPUB6
#define ICSPCLK_OD                   ODCONBbits.ODCB6
#define ICSPCLK_ANS                  ANSELBbits.ANSB6
#define ICSPCLK_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define ICSPCLK_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define ICSPCLK_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define ICSPCLK_GetValue()           PORTBbits.RB6
#define ICSPCLK_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define ICSPCLK_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define ICSPCLK_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define ICSPCLK_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define ICSPCLK_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define ICSPCLK_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define ICSPCLK_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define ICSPCLK_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set ICSPDAT aliases
#define ICSPDAT_TRIS                 TRISBbits.TRISB7
#define ICSPDAT_LAT                  LATBbits.LATB7
#define ICSPDAT_PORT                 PORTBbits.RB7
#define ICSPDAT_WPU                  WPUBbits.WPUB7
#define ICSPDAT_OD                   ODCONBbits.ODCB7
#define ICSPDAT_ANS                  ANSELBbits.ANSB7
#define ICSPDAT_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define ICSPDAT_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define ICSPDAT_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define ICSPDAT_GetValue()           PORTBbits.RB7
#define ICSPDAT_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define ICSPDAT_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define ICSPDAT_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define ICSPDAT_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define ICSPDAT_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define ICSPDAT_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define ICSPDAT_SetAnalogMode()      do { ANSELBbits.ANSB7 = 1; } while(0)
#define ICSPDAT_SetDigitalMode()     do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set IO_RC0 aliases
#define IO_RC0_TRIS                 TRISCbits.TRISC0
#define IO_RC0_LAT                  LATCbits.LATC0
#define IO_RC0_PORT                 PORTCbits.RC0
#define IO_RC0_WPU                  WPUCbits.WPUC0
#define IO_RC0_OD                   ODCONCbits.ODCC0
#define IO_RC0_ANS                  ANSELCbits.ANSC0
#define IO_RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define IO_RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define IO_RC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define IO_RC0_GetValue()           PORTCbits.RC0
#define IO_RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define IO_RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define IO_RC0_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define IO_RC0_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define IO_RC0_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define IO_RC0_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define IO_RC0_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define IO_RC0_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set RC1 procedures
#define RC1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define RC1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define RC1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define RC1_GetValue()              PORTCbits.RC1
#define RC1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define RC1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define RC1_SetPullup()             do { WPUCbits.WPUC1 = 1; } while(0)
#define RC1_ResetPullup()           do { WPUCbits.WPUC1 = 0; } while(0)
#define RC1_SetAnalogMode()         do { ANSELCbits.ANSC1 = 1; } while(0)
#define RC1_SetDigitalMode()        do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set IO_BUFF_OUT aliases
#define IO_BUFF_OUT_TRIS                 TRISCbits.TRISC2
#define IO_BUFF_OUT_LAT                  LATCbits.LATC2
#define IO_BUFF_OUT_PORT                 PORTCbits.RC2
#define IO_BUFF_OUT_WPU                  WPUCbits.WPUC2
#define IO_BUFF_OUT_OD                   ODCONCbits.ODCC2
#define IO_BUFF_OUT_ANS                  ANSELCbits.ANSC2
#define IO_BUFF_OUT_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define IO_BUFF_OUT_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define IO_BUFF_OUT_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define IO_BUFF_OUT_GetValue()           PORTCbits.RC2
#define IO_BUFF_OUT_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define IO_BUFF_OUT_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define IO_BUFF_OUT_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define IO_BUFF_OUT_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define IO_BUFF_OUT_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define IO_BUFF_OUT_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define IO_BUFF_OUT_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define IO_BUFF_OUT_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set IO_BUFF_IN aliases
#define IO_BUFF_IN_TRIS                 TRISCbits.TRISC3
#define IO_BUFF_IN_LAT                  LATCbits.LATC3
#define IO_BUFF_IN_PORT                 PORTCbits.RC3
#define IO_BUFF_IN_WPU                  WPUCbits.WPUC3
#define IO_BUFF_IN_OD                   ODCONCbits.ODCC3
#define IO_BUFF_IN_ANS                  ANSELCbits.ANSC3
#define IO_BUFF_IN_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define IO_BUFF_IN_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define IO_BUFF_IN_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define IO_BUFF_IN_GetValue()           PORTCbits.RC3
#define IO_BUFF_IN_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define IO_BUFF_IN_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define IO_BUFF_IN_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define IO_BUFF_IN_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define IO_BUFF_IN_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define IO_BUFF_IN_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define IO_BUFF_IN_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define IO_BUFF_IN_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set IO_MOTOR4B aliases
#define IO_MOTOR4B_TRIS                 TRISCbits.TRISC4
#define IO_MOTOR4B_LAT                  LATCbits.LATC4
#define IO_MOTOR4B_PORT                 PORTCbits.RC4
#define IO_MOTOR4B_WPU                  WPUCbits.WPUC4
#define IO_MOTOR4B_OD                   ODCONCbits.ODCC4
#define IO_MOTOR4B_ANS                  ANSELCbits.ANSC4
#define IO_MOTOR4B_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define IO_MOTOR4B_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define IO_MOTOR4B_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define IO_MOTOR4B_GetValue()           PORTCbits.RC4
#define IO_MOTOR4B_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define IO_MOTOR4B_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define IO_MOTOR4B_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define IO_MOTOR4B_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define IO_MOTOR4B_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define IO_MOTOR4B_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define IO_MOTOR4B_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define IO_MOTOR4B_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set IO_MOTOR4A aliases
#define IO_MOTOR4A_TRIS                 TRISCbits.TRISC5
#define IO_MOTOR4A_LAT                  LATCbits.LATC5
#define IO_MOTOR4A_PORT                 PORTCbits.RC5
#define IO_MOTOR4A_WPU                  WPUCbits.WPUC5
#define IO_MOTOR4A_OD                   ODCONCbits.ODCC5
#define IO_MOTOR4A_ANS                  ANSELCbits.ANSC5
#define IO_MOTOR4A_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define IO_MOTOR4A_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define IO_MOTOR4A_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define IO_MOTOR4A_GetValue()           PORTCbits.RC5
#define IO_MOTOR4A_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define IO_MOTOR4A_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define IO_MOTOR4A_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define IO_MOTOR4A_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define IO_MOTOR4A_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define IO_MOTOR4A_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define IO_MOTOR4A_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define IO_MOTOR4A_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set IO_MOTOR3B aliases
#define IO_MOTOR3B_TRIS                 TRISCbits.TRISC6
#define IO_MOTOR3B_LAT                  LATCbits.LATC6
#define IO_MOTOR3B_PORT                 PORTCbits.RC6
#define IO_MOTOR3B_WPU                  WPUCbits.WPUC6
#define IO_MOTOR3B_OD                   ODCONCbits.ODCC6
#define IO_MOTOR3B_ANS                  ANSELCbits.ANSC6
#define IO_MOTOR3B_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define IO_MOTOR3B_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define IO_MOTOR3B_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define IO_MOTOR3B_GetValue()           PORTCbits.RC6
#define IO_MOTOR3B_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define IO_MOTOR3B_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define IO_MOTOR3B_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define IO_MOTOR3B_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define IO_MOTOR3B_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define IO_MOTOR3B_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define IO_MOTOR3B_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define IO_MOTOR3B_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()             do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()           do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/