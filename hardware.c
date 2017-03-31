/* ************************************************************************** */
/** Descriptive File Name
  @ Author
    Richard Wall
 
  @ Date
    April 30, 2016

  @ Revised
    December 10, 2016
 
  @ Verified
    February 28, 2017

  @Company
    Digilent       

   @File Name
    hardware.c

  @Summary
    Configure Basys MX3 IO 

  @Description
    The #define statements and macro C code provide high level access to the 
    "Trainer" boards switches, push buttons, and LEDs as well as analog inputs.
    
 */
/* ************************************************************************** */

/* This included file provides access to the peripheral library functions and
   must be installed after the XC32 compiler. See
http://ww1.microchip.com/downloads/en/DeviceDoc/32bitPeripheralLibraryGuide.pdf
http://www.microchip.com/SWLibraryWeb/product.aspx?product=PIC32%20Peripheral%20Library
 */
#include "hardware.h"
#include "switches.h"
#include <plib.h>

// *****************************************************************************
/**
    @Function
        void hardware(void);

    @Summary
        Initializes PIC32 pins commonly used for IO on the Basys MX3 Trainer 
        processor board.

    @Description
        Initializes PIC32 digital IO pins to provide functionality for the 
        switches, push buttons, and LEDs

    @Parameters
        None

    @Returns
        None
    */
     
void Hardware_Setup(void)
{
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Statement configure cache, wait states and peripheral bus clock
 * Configure the device for maximum performance but does not change the PBDIV
 * Given the options, this function will change the flash wait states, RAM
 * wait state and enable prefetch cache but will not change the PBDIV.
 * The PBDIV value is already set via the pragma FPBDIV option above..
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
// Allow RA0, RA1, RA4 and RA5 to be used as digital IO
    SYSTEMConfig(GetSystemClock(), SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
    DDPCONbits.JTAGEN = 0;  // Statement is required to use Pin RA0 as IO
   
    ALL_DIGITAL_IO();       	/* Sets all LED, switches and push buttons for digital IO*/
    SET_MIC_ANALOG();       	/* Sets microphone input for analog */
    SET_POT_ANALOG();       	/* Sets ANALOG INPUT CONTROL for analog input */
    
    Set_All_LEDs_Output();		/* Sets Basys MX3 LED0 through LED7 as output */
    Set_All_LEDs_Off();			/* Sets Basys MX3 LED0 through LED7 off */
    Set_All_Switches_Input();	/* Sets Basys MX3 SW0 through SW7 as input */
    Set_All_PBs_Input();		/* Sets Basys MX3 push buttons as input */
	Set_RGB_Output();			/* Sets Basys MX3 RGB LED as output */
	Set_LED8_RGB(0);            /* Sets Basys MX3 RGB LED off */
	
} /* End of Basys MX3A hardware configuration */
/** 
  @Function
    unsigned int Switch2Binary( void ) 

  @Summary
    Generates an unsigned integer value from the switch settings using binary
    weighting. The Basys MX3 slide switches are initialized as inputs to a
    disparate port assignments.  This function collects all the switch 
    settings into a single variable.

  @Remarks
    None
 */
unsigned int switch2Binary(void) 
{
int value;
    
    value =  ((int) SW0()) << 0;
    value += ((int) SW1()) << 1;
    value += ((int) SW2()) << 2;
    value += ((int) SW3()) << 3;
    value += ((int) SW4()) << 4;
    value += ((int) SW5()) << 5;
    value += ((int) SW6()) << 6;
    value += ((int) SW7()) << 7;
    return value;
}

/* End of hardware.c */
