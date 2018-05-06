/* User LED is on PA0 */
/* This example uses SERCOM0 (UART mode) to send data to a host PC
 * 
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
 monitor load_image /home/frank/Documents/programming/samd/Baremetal/samd20_examples/serial_irq/main.elf 0
 monitor reset 
*/
void delay(uint32_t dly)
{
    while(dly--);
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
    enable_interrupts();
    printString("Hello SamD!\r\n"); 
    while(1)
    {
        if (rx_count())
        {
            printString("\r\nYou entered: "); 
            eputc(egetc());
            PAOUTTGL = BIT0; // Toggle Port A bit 0
            delay(100000);   // Wait  
        }
        
    }
   
}
    
