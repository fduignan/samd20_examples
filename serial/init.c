#include <stdint.h>
#include "../samd20e16.h"
void init(void);
void Default_Handler(void);
int main(void);

// The following are 'declared' in the linker script
extern unsigned char  INIT_DATA_VALUES;
extern unsigned char  INIT_DATA_START;
extern unsigned char  INIT_DATA_END;
extern unsigned char  BSS_START;
extern unsigned char  BSS_END;
// the section "vectors" is placed at the beginning of flash 
// by the linker script
const void * Vectors[] __attribute__((section(".vectors"))) ={
	(void *)0x20002000, 	/* Top of stack (20k) */ 
	init,   		     /* Reset Handler */
	Default_Handler,	/* NMI */
	Default_Handler,	/* Hard Fault */
	Default_Handler,	/* MemManage */
	Default_Handler,	/* Bus Fault  */
	Default_Handler,	/* Usage Fault */
	Default_Handler,	/* Reserved */ 
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* SVCall */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Debug monitor */
	Default_Handler,	/* PendSV */
	Default_Handler,    /* SysTick */	
/* External interrupt handlers follow */
	Default_Handler, 	/* 0: External Interrupt Controller Non-Maskable Interrupt */
	Default_Handler, 	/* 1: Power manager */
	Default_Handler, 	/* 2: System control */
	Default_Handler, 	/* 3: WDT */
	Default_Handler, 	/* 4: External Interrupt Controller */
	Default_Handler, 	/* 5: Non-volatile memory control */
	Default_Handler, 	/* 6: Event System */
	Default_Handler, 	/* 7: SERCOM0 */
	Default_Handler, 	/* 8: SERCOM1 */
	Default_Handler, 	/* 9: SERCOM2 */
	Default_Handler, 	/* 10: SERCOM3 */
	Default_Handler, 	/* 11: SERCOM4 */
	Default_Handler, 	/* 12: SERCOM5 */
	Default_Handler, 	/* 13: Timer Counter 0 */
	Default_Handler, 	/* 14: Timer Counter 1 */
	Default_Handler, 	/* 15: Timer Counter 2 */
	Default_Handler, 	/* 16: Timer Counter 3 */
	Default_Handler, 	/* 17: Timer Counter 4 */
	Default_Handler, 	/* 18: Timer Counter 5 */
	Default_Handler, 	/* 19: Timer Counter 6 */
	Default_Handler, 	/* 20: Timer Counter 7 */
	Default_Handler, 	/* 21: ADC */
	Default_Handler, 	/* 22: Analogue comparator */
	Default_Handler, 	/* 23: DAC */
	Default_Handler, 	/* 24: Peripheral Touch Controller */	
};
void initClocks()
{
    // Run the main clock up to 48MHz.   Uses clock generator 3 and 0
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
void init()
{
// do global/static data initialization
	unsigned char *src;
	unsigned char *dest;
	unsigned len;
	src= &INIT_DATA_VALUES;
	dest= &INIT_DATA_START;
	len= &INIT_DATA_END-&INIT_DATA_START;
	while (len--)
		*dest++ = *src++;
// zero out the uninitialized global/static variables
	dest = &BSS_START;
	len = &BSS_END - &BSS_START;
	while (len--)
		*dest++=0;
    initClocks();
	main();
}

void Default_Handler()
{
	while(1);
}
