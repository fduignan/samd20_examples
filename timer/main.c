/* User LED is on PA0 */
/* This example uses TC0 to generate a periodic interrupt
 * It also outputs the current value of TC0_COUNT on the serial port
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
 monitor load_image /home/frank/Documents/programming/samd/Baremetal/samd20_examples/timer/main.elf 0
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
    PM_APBCMASK |= BIT8; // Turn on the timer register clock
    TC0_CTRLA |= BIT3+BIT1; // enable the timer in 32 bit mode
    GCLK_CLKCTRL = 0x13 + BIT14; // route the 48MHz clock output from generic clock generator 0 to TC0
    while(  (GCLK_STATUS & BIT7)); // wait for sync to complete
    TC0_CC0 = 48000000; // 1s period
    TC0_INTENSET = BIT4; // enable interrupts on MC0
    NVIC_ISER = BIT13; // enable TC0 interrupts in the NVIC
    
}
void Timer0_Handler()
{
    TC0_INTFLAG = BIT4; // ack the interrupt
    TC0_COUNT = 0;
    PAOUTTGL = BIT0; // Toggle Port A bit 0
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
    printString("Timer example for SamD!\r\n"); 
    while(1)
    {        
        printInteger(TC0_COUNT);
        printString("\r\n");
        delay(1000000);        
    }
   
}
    
