/* ************************************************************************** */
/** Descriptive File Name:     main.c for Lab 2a

  @ Author
    Richard Wall
 
  @ Date
    September 20, 2016

  @ Verified
    February 28, 2017
 
  @Company
    Digilent Inc.

  @File Name
    main.c

  @Summary
    Timer based delays.

  @Description
    Delay routines that blink LEDs at different rates based on polled timer 
    based delays and preemptive based timer based delays.
  @Remarks
    Uses XC32 peripheral library. See 
 http://ww1.microchip.com/downloads/en/DeviceDoc/32bitPeripheralLibraryGuide.pdf
 http://www.microchip.com/SWLibraryWeb/product.aspx?product=PIC32%20Peripheral%20Library
  
    Note: hardware.c and hardware.h is not required for this solution
 
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/*********************************************************************
 * The purpose of this example code is to demonstrate the use of 
 * peripheral library macros and functions supporting the PIC32MX general 
 * purpose Type A Timer 1.
 *
 * Platform:     Basys MX3
 *
 * Features demonstrated:
 *      - Timer configuration
 *      - Timer Interrupt flag polling
 *      - Timer Interrupt flag resetting
 *
 * Description:
 *         - This example polls the Timer 1 interrupt flag and toggles LED0 and 
 *
 * Oscillator Configuration Bit Settings: config_bits.h
 * Basys MX3 hardware initialization is provided by Hardware_Setup.c 
 * Notes:
 *        - Peripheral Clock: PBCLK = 80E6 / 8 = 10E6 
 *        - Timer1 clock = T1CLK = PBCLK/T1_PRESCALE = 10E6/8 = 1.25MHz
 *        - To generate a 1 ms delay, PR1 = (T1CLK / 1000)-1 = (1250-1) = 1249
*
 ********************************************************************/
#include "config_bits.h"

// Application constant
#define GetPeripheralClock()    10000000
#define T1_PRESCALE             8
#define TOGGLES_PER_SEC         1000
#define T1_TICK          (GetPeripheralClock() / T1_PRESCALE / TOGGLES_PER_SEC)

// Function prototype
void Timer1_delay(int );   

int main(void)
{
// Set instrumentation output pins
    TRISAbits.TRISA0 = 0;      // Set LED0 IO pin for output
    TRISEbits.TRISE0 = 0;      // Use LCD DB0 for timing instrumentation

// Initialize Timer 1 for 1 ms period
    T1CONbits.TCKPS = 0x01;    // Timer 1 pre scale = 8
    T1CONbits.TCS = 0;         // Timer 1 source = PBCLK
    T1CONbits.TGATE = 0;       // Turn gated Timer 1 off
    PR1 = T1_TICK - 1;         // Set T1 period for 1 ms
    T1CONbits.ON = 1;          // Turn Timer 1 on.
    
    while(1)
    {
        Timer1_delay(100);      // Delay 100 ms		
/* Toggle outputs once every 100 millisecond */        
        LATAINV = 0x01;        // Toggle LED on RA0 
        LATEINV = 0x01;        // Toggle RE0 for timing output
    }

    return (EXIT_FAILURE);  // System has failed is this line is reached
}

/* START FUNCTION DESCRIPTION ********************************************
 * Timer1_delay
 * SYNTAX:         void Timer1_delay(int delay);
 * KEYWORDS:       millisecond, hardware delay, Timer A, multirate timer
 * DESCRIPTION:    Delays the number of milliseconds specified by the passed
 *                 argument, delay. 
 * Parameter 1:    int - number of ms to delay
 * RETURN:         None
 * NOTES:          The Timer 1 interrupt flag is polled but the Timer 1 
 *                 interrupt is not enabled. Hence this is a blocking function
 *                 that can be preempted.
 * END DESCRIPTION *******************************************************/
void Timer1_delay(int delay)
{
    while(delay--)                  // Continue for the delay period
    {
        while(!IFS0bits.T1IF);      // Wait for interrupt flag to be set
        IFS0bits.T1IF = 0;          // Clear the interrupt flag
    }
}
/* End of File main.c  */
