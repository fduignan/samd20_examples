/* User LED is on PA0 */
/* This example switches the CPU up to 48MHz.  A complicated sequence of steps obtained from stackexchange (see reference below)
 * The switch does not happen immediately after boot.  This allows you time to intervene before a badly written clock initialization
 * locks you out of your system :)
 */
#include <stdint.h>
#include "../samd20e16.h"
/*
 target remote :3333
 monitor at91samd chip-erase
 monitor reset halt
 monitor load_image /home/frank/Documents/programming/samd/Baremetal/samd20_examples/clock_test/main.elf 0
 monitor reset
 
*/


void delay(uint32_t dly)
{
    while(dly--);
}
void initClocks()
{
    // reference : https://electronics.stackexchange.com/questions/332569/how-to-configure-atmel-sam-d20-for-internal-48mhz-clock-source
    
    NVM_CTRLB = (2 << 1); // configure for 2 wait states : unlike the referenc above, I found 1 wait state to be insufficient (random crashes)
    PM_APBAMASK |= BIT3; // ensure clock system for GCLK is turned on.
    // 1
    GCLK_CTRL |= BIT0; // reset GCLK system
    while( (GCLK_CTRL & BIT0) && (GCLK_STATUS & BIT7)); // wait for reset and sync to complete
    // 2
    SYSCTRL_OSC8M &= ~BIT7; // turn off on-demand feature of the 8MHz clock to ensure it stays running
    // 3
    GCLK_GENDIV = 3 + (64 << 8); // select clock generator 3 with a division factor of 64
    // 4
    GCLK_GENCTRL  = 3 + (6 << 8) + BIT16; // select 8MHz internal clock source for generator 3 and enable it    
    while(  (GCLK_STATUS & BIT7)); // wait for sync to complete
    // 5
    GCLK_CLKCTRL = BIT14 + (3 << 8) +  + (0);
    while(  (GCLK_STATUS & BIT7)); // wait for sync to complete     
    // 6
    SYSCTRL_DFLLCTRL &= ~BIT7; // disable the on-demand feature of the PLL clock (to keep it on)
    while( (SYSCTRL_PCLKSR & BIT4) == 0); // wait for PLL to become ready
    // 7 
    SYSCTRL_DFLLMUL = 3072 + BIT26 + BIT24;
    while( (SYSCTRL_PCLKSR & BIT4) == 0); // wait for PLL to become ready
    // 8
    SYSCTRL_DFLLCTRL |= BIT2 + BIT9; // enable closed loop control and disable quick lock
    while( (SYSCTRL_PCLKSR & BIT4) == 0); // wait for PLL to become ready
    // 9
    SYSCTRL_INTFLAG = (BIT7 + BIT6 + BIT4); // clear interrupts
    // 10
    SYSCTRL_DFLLCTRL |= BIT1; // enable  the PLL
    while( (SYSCTRL_PCLKSR & BIT4) == 0); // wait for PLL to become ready
    // 11
    while ( !(SYSCTRL_INTFLAG & BIT7) && !( SYSCTRL_INTFLAG & BIT6) ); // wait for fine and coarse locks
    // 12
    while (!(SYSCTRL_INTFLAG & BIT4)); // wait for DFLL 
    // 
    GCLK_GENDIV = 0; // select no division for generator 0    
    GCLK_GENCTRL = 0 + (7 << 8) + BIT17 + BIT16; // for gen 0: select source=48MHz, improve duty cycle and enable
    while(  (GCLK_STATUS & BIT7)); // wait for sync to complete             
    
}
int main()
{
    int i=0;
    PADIRSET = BIT0; // make Port A bit 0 an output
    while(1)
    {
        PAOUTTGL = BIT0; // Toggle Port A bit 0
        delay(100000);   // Wait
        i++;
        if (i == 5)
        {            
            initClocks();
        }
    }
   
}
    
