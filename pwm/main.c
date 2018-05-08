/* User LED is on PA0 */
/* This example generates a PWM waveform using TC0 in 16 bit mode.
 * The PWM frequency is set to 1kHz and the duty cycle ramps from 0 to 100% (and straight back to zero again)
 * 
 * It does not use timer interrupts.
 */
#include <stdint.h>
#include "../samd20e16.h"
#include "serial.h"
/*
 How to program: run openocd first
 Next, run arm-none-eabi-gdb in another window and execute these commands (adjust directory to suit)
 target remote :3333
 monitor at91samd chip-erase
 monitor reset halt
 monitor load_image /home/frank/Documents/programming/samd/Baremetal/samd20_examples/pwm/main.elf 0
 monitor reset 
*/
void delay(uint32_t dly)
{
    while(dly--);
}
void initTimer()
{
    // Configure timer counter 0 to interrupt periodically
    // Will use 48MHz base clock from clock module 0     
    GCLK_CLKCTRL = 0x13 + BIT14; // route the 48MHz clock output from generic clock generator 0 to TC0
    while(  (GCLK_STATUS & BIT7)); // wait for sync to complete
    PM_APBCMASK |= BIT8; // Turn on the timer register clock
    TC0_CTRLA |= BIT6+BIT5+BIT1; // MPWM, enable the timer in 16 bit mode

    TC0_CC0_16 = 48000; // 1ms period (48MHz divided by 48000)
    TC0_CC1_16 = 0; // Duty = 0 to start with 
    
    // configure the counter i/o pins
    // Pin 12 = TC0 WO[1], PA9, Function E
    PAPMUX4 = 0x40; //  Enable function E
    PAPPINCFG9 |= BIT0; // enable alternative function on PA9
}

void setDuty(uint32_t Duty)
{
    uint32_t Period = TC0_CC0_16;
    TC0_CC1_16 = (Period * Duty)/100;
}
int main()
{ 
    int i=0;
    PADIRSET = BIT0; // make Port A bit 0 an output
    // Startup delay to allow escape from a potentially bricked chip: ONLY DELETE WHEN SURE OF PROPER CLOCK OPERATION
    for (i=0;i<10;i++)
    {
        PAOUTTGL = BIT0; // Toggle Port A bit 0
        delay(1000000);   // Wait  
    }    
    initUART(); // get SERCOM0 going
    initTimer(); // get the timer going
    enable_interrupts();
    printString("PWM example for SamD!\r\n"); 
    uint32_t Duty=0;
    while(1)
    {        
        printInteger(TC0_CC0_16);
        printString(" ");
        printInteger(TC0_CC1_16);
        printString("\r\n");
        setDuty(Duty);
        delay(1000000);        
        Duty++;
        if (Duty > 99)
            Duty = 0;
    }
   
}
    
