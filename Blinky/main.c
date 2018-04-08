/* User LED is on PA0 */

#include <stdint.h>
#include "../samd20e16.h"
/*
 target remote :3333
 monitor at91samd chip-erase
 monitor reset halt
 monitor load_image /home/frank/Documents/programming/samd/Baremetal/Blinky/main.elf 0
 monitor reset
 
*/

void delay(uint32_t dly)
{
    while(dly--);
}
int main()
{
    PADIRSET = BIT0; // make Port A bit 0 an output
    while(1)
    {
        PAOUTTGL = BIT0; // Toggle Port A bit 0
        delay(100000);   // Wait
    }
   
}
    
