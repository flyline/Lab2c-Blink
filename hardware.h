/* ************************************************************************** */
/** Descriptive File Name
  @ Author
    Richard Wall
 
  @ Date
    April 30, 2016

  @ Revised
     December 12, 2016

  @Company
    Digilent Inc.      

   @File Name
    hardware.h

  @Summary
    Definition of constants and macro routines for the Basys MX3A processor board 

  @Description
    The #define statements and macro C code provide high level access to the 
    Basys MX3A trainer boards switches, push buttons, and LEDs.
    
 */
/* ************************************************************************** */
/* Conditional inclusion prevents multiple definition errors */
#ifndef _HARDWARE_H_   
    #define	_HARDWARE_H_

    #ifndef _SUPPRESS_PLIB_WARNING	/* Suppress plib obsolesce warnings */
        #define _SUPPRESS_PLIB_WARNING
    #endif

    #ifndef _DISABLE_OPENADC10_CONFIGPORT_WARNING
        #define  _DISABLE_OPENADC10_CONFIGPORT_WARNING
    #endif

/* Comment out the following define statement when programmer is NOT used to 
 * allow using BTNL and BTNU as user inputs. */
    #define DEBUG_MODE  /* Inputs from push buttons BTNL and BRNU are not useable */

/* This included file provides access to the peripheral library functions and
   must be installed after the XC32 compiler. See
http://ww1.microchip.com/downloads/en/DeviceDoc/32bitPeripheralLibraryGuide.pdf and
http://www.microchip.com/SWLibraryWeb/product.aspx?product=PIC32%20Peripheral%20Library */

   #include <plib.h>
   
/* The following definitions are for IO assigned on the Digilent Basys MX3A
   processor board. */

/* The ANSELx register has a default value of 0xFFFF; therefore, all pins that
 * share analog functions are analog (not digital) by default. All pins are 
 * initially set be digital followed be setting A_POT for the ANALOG INPUT 
 * CONTROL and A_MIC for the microphone input back to being analog input pins.*/
    #define ALL_DIGITAL_IO() (ANSELA=0,ANSELB=0,ANSELC=0,ANSELD=0,ANSELE=0,ANSELF=0,ANSELG = 0)
    #define SET_MIC_ANALOG()  ANSELBbits.ANSB4 = 1
    #define SET_POT_ANALOG()  ANSELBbits.ANSB2 = 1

/* Macros to configure PIC pins as inputs to sense switch settings */

/* The following macro instructions set switches as inputs. */
    #define Set_SW0_in()    TRISFbits.TRISF3 = 1 
    #define Set_SW1_in()    TRISFbits.TRISF5 = 1 
    #define Set_SW2_in()    TRISFbits.TRISF4 = 1 
    #define Set_SW3_in()    TRISDbits.TRISD15 = 1
    #define Set_SW4_in()    TRISDbits.TRISD14 = 1
    #define Set_SW5_in()    TRISBbits.TRISB11 = 1 
    #define Set_SW6_in()    TRISBbits.TRISB10 = 1
    #define Set_SW7_in()    TRISBbits.TRISB9  = 1

/* The following macro instruction seta the processor pins for all 8 switch inputs */
    #define Set_All_Switches_Input();  { Set_SW0_in(); Set_SW1_in(); Set_SW2_in();\
                                   Set_SW3_in(); Set_SW4_in(); Set_SW5_in();\
                                   Set_SW6_in(); Set_SW7_in(); }

/* The following macro instructions provide for reading the position of the 8 switches. */
    #define SW0()           PORTFbits.RF3
    #define SW1()           PORTFbits.RF5
    #define SW2()           PORTFbits.RF4
    #define SW3()           PORTDbits.RD15
    #define SW4()           PORTDbits.RD14
    #define SW5()           PORTBbits.RB11
    #define SW6()           PORTBbits.RB10
    #define SW7()           PORTBbits.RB9

/* See http://umassamherstm5.org/tech-tutorials/pic32-tutorials/pic32mx220-tutorials/internal-pull-updown-resistors */
/* Macro instructions to set the push buttons as inputs */
    #ifndef DEBUG_MODE
/* Include BTNL and BTNU only if NOT in debug mode */
        #define Set_BTNL_in()  (TRISBbits.TRISB0 = 1, CNPDBbits.CNPDB0 = 1)
        #define Set_BTNU_in()  (TRISBbits.TRISB1 = 1, CNPDBbits.CNPDB1 = 1) 
    #endif
    #define Set_BTNR_in()   TRISBbits.TRISB8 = 1
    #define Set_BTNR_out()  TRISBbits.TRISB8 = 0    // use for Servo J1
    #define Set_BTND_in()   TRISAbits.TRISA15 = 1
    #define Set_BTND_out()  TRISAbits.TRISA15 = 0   // use for Servo J2
    #define Set_BTNC_in()   TRISFbits.TRISF0 = 1

/* Single macro instruction to configure all 5 push buttons */	
    #ifndef DEBUG_MODE
/* Allow use of BTNL and BTNU */
        #define Set_All_PBs_Input()  ( Set_BTNL_in(),Set_BTNR_in(),Set_BTNU_in(),Set_BTND_in(),Set_BTNC_in() )    
    #else
/* Allow use of BTNL and BTNU */
        #define Set_All_PBs_Input()  ( Set_BTNR_in(),Set_BTND_in(),Set_BTNC_in() )
    #endif

/* Macro instructions to read the button position values. 1 = button pressed */ 
    #ifndef DEBUG_MODE
/* Include BTNL and BTNU only if NOT in debug mode */
        #define BNTL()      PORTBbits.RB0  
        #define BNTU()      PORTBbits.RB1  
    #endif
    #define BNTR()          PORTBbits.RB8  
    #define BNTD()          PORTAbits.RA15 
    #define BNTC()          PORTFbits.RF0 

/* Macros to define the PIC pin values for the board LEDs */
    #define LED0_bit        0x01
    #define LED1_bit        0x02
    #define LED2_bit        0x04
    #define LED3_bit        0x08
    #define LED4_bit        0x10
    #define LED5_bit        0x20
    #define LED6_bit        0x40
    #define LED7_bit        0x80
    #define All_LED_bits    0xFF	/* Set all LEDs off  */

/* Macros to configure PIC pins as outputs for board LEDs */
    #define Set_LED0_out()  TRISAbits.TRISA0 = 0
    #define Set_LED1_out()  TRISAbits.TRISA1 = 0
    #define Set_LED2_out()  TRISAbits.TRISA2 = 0
    #define Set_LED3_out()  TRISAbits.TRISA3 = 0
    #define Set_LED4_out()  TRISAbits.TRISA4 = 0
    #define Set_LED5_out()  TRISAbits.TRISA5 = 0
    #define Set_LED6_out()  TRISAbits.TRISA6 = 0
    #define Set_LED7_out()  TRISAbits.TRISA7 = 0
	
/* Macro instruction to configure all 8 LED pins for outputs */
    #define Set_All_LEDs_Output()  TRISACLR = All_LED_bits

/* Macros to set board each LED on (1) or off (0) */
    #define setLED0(a);  {if(a) LATASET = LED0_bit; else LATACLR = LED0_bit;}
    #define setLED1(a);  {if(a) LATASET = LED1_bit; else LATACLR = LED1_bit;}
    #define setLED2(a);  {if(a) LATASET = LED2_bit; else LATACLR = LED2_bit;}
    #define setLED3(a);  {if(a) LATASET = LED3_bit; else LATACLR = LED3_bit;}
    #define setLED4(a);  {if(a) LATASET = LED4_bit; else LATACLR = LED4_bit;}
    #define setLED5(a);  {if(a) LATASET = LED5_bit; else LATACLR = LED5_bit;}
    #define setLED6(a);  {if(a) LATASET = LED6_bit; else LATACLR = LED6_bit;}
    #define setLED7(a);  {if(a) LATASET = LED7_bit; else LATACLR = LED7_bit;}
    #define Set_All_LEDs_On()   LATASET = All_LED_bits  // Set all LEDs on
    #define Set_All_LEDs_Off()  LATACLR = All_LED_bits  // Set all LEDs off

/* Macros to invert the output to the board LEDs */
    #define invLED0()   LATAINV = LED0_bit    
    #define invLED1()   LATAINV = LED1_bit
    #define invLED2()   LATAINV = LED2_bit
    #define invLED3()   LATAINV = LED3_bit
    #define invLED4()   LATAINV = LED4_bit
    #define invLED5()   LATAINV = LED5_bit
    #define invLED6()   LATAINV = LED6_bit
    #define invLED7()   LATAINV = LED7_bit

/* Configure RGB LED outputs */
	#define Set_LED8_R_Out()	TRISDbits.TRISD2 = 0		
	#define Set_LED8_G_Out()	TRISDbits.TRISD12 = 0		
	#define Set_LED8_B_Out()	TRISDbits.TRISD3 = 0		
    #define Set_RGB_Output()    ( Set_LED8_R_Out(), Set_LED8_G_Out(), Set_LED8_B_Out() )

    #define Set_LED8_R(a)       LATDbits.LATD2 = a
    #define Set_LED8_G(a)       LATDbits.LATD12 = a
    #define Set_LED8_B(a)       LATDbits.LATD3 = a

    #define Set_LED8_RGB(a)     (LATDbits.LATD2 = a, LATDbits.LATD12 = a, LATDbits.LATD3 = a)             

/* Based upon setting in config_bits.h These directly influence timed
 * events using the Tick module.  They also are used for UART I2C, and SPI
 * baud rate generation. */

    #define XTAL                 (8000000UL)     /* 8 MHz Xtal on Basys MX3A */
    #define GetSystemClock()     (80000000UL)    /* Instruction frequency */
    #define SYSTEM_FREQ          (GetSystemClock())
    #define GetCoreClock()       (GetSystemClock()/2) /* Core clock frequency */
    #define GetPeripheralClock() (GetSystemClock()/8) /* PCLK set for 10 MHz */

/* Used in core timer software delay */
    #define CORE_MS_TICK_RATE	 (unsigned int) (GetCoreClock()/1000UL)

#endif	/* End of _HARDWARE_H_ */

/* Declare Hardware setup for global access */
void Hardware_Setup(void);

unsigned int switch2Binary(void);
/* End of hardware.h */


