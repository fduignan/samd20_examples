/* User LED is on PA0 */
/* This example uses SERCOM0 (UART mode) to send data to a host PC
 * 
 */
#include <stdint.h>
#include "../samd20e16.h"
/*
 How to program: run openocd first
 Next, run arm-none-eabi-gdb in another window and execute these commands (adjust directory to suit)
 target remote :3333
 monitor at91samd chip-erase
 monitor reset halt
 monitor load_image /home/frank/Documents/programming/samd/Baremetal/samd20_examples/serial/main.elf 0
 monitor reset 
*/
void delay(uint32_t dly)
{
    while(dly--);
}

void initUART()
{    
    // UART is on:    
    PM_APBCMASK |= BIT2; // turn on SERCOM0
    // Reset SERCOM 0
    SERCOM0_CTRLA = 1; // reset the UART
    while(SERCOM0_STATUS & BIT15); // wait for sync to complete   
    while ( SERCOM0_CTRLA & BIT0 ); // wait for reset to complete
    // Will route the main 48MHz clock to SERCOM0 as the baud rate base clock.
    GCLK_CLKCTRL = 0x0d + BIT14;        
    while(  (GCLK_STATUS & BIT7)); // wait for sync to complete
    SERCOM0_BAUD = 65325; // configure for 9600 bps
    while(SERCOM0_STATUS & BIT15); // wait for sync to complete   
    SERCOM0_CTRLB = BIT17 + BIT16 + BIT9 ; // enable TX, RX, Start-of-frame wakeup, 1 stop bit, 8 bits;
    // 0x00030200 RXEN,TXEN,SFDE,
    while(SERCOM0_STATUS & BIT15); // wait for sync to complete
    SERCOM0_CTRLA = BIT30 + BIT20 + BIT2 + BIT1; // LSB first, UART mode , internal clock, PAD1 = RX, PAD0 = TX, ENABLE    
    // 0x40000006 DORD,ENABLE,MODE001 (USART INTERNAL CLOCK), ENABLE
    while(SERCOM0_STATUS & BIT15); // wait for synchronization between clock domains to complete    
   // Will use pins 5 and 6 (PA4 and PA5) for TX, RX 
    // To select function D, write  '3' to these bits
    PAPMUX2 = 0x33;    
    PAPPINCFG4 |= BIT0; // enable special function multplexing on Pin 5                
    PAPPINCFG5 |= BIT0; // enable special function multplexing on Pin 6
}
void eputc(char c)
{
    SERCOM0_DATA = c;
    while((SERCOM0_INTFLAG & BIT1)==0);// wait for TXC flag
    
}
void printString(char *String)
{
    while (*String)
    {
        eputc(*String++);
    }
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
    while(1)
    {
        printString("Hello SamD!\r\n");
        i = SERCOM0_INTFLAG;
        PAOUTTGL = BIT0; // Toggle Port A bit 0
        delay(10000);   // Wait  
        
    }
   
}
    
