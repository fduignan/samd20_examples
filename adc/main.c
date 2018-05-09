/* User LED is on PA0 */
/* This example outputs ADC conversion results on the UART
 * AIN[0] on Pin 3 (PA2) will be used as an analogue input
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
 monitor load_image /home/frank/Documents/programming/samd/Baremetal/samd20_examples/adc/main.elf 0
 monitor reset 
*/
void delay(uint32_t dly)
{
    while(dly--);
}
void initADC()
{
    // Power up the ADC 
    PM_APBCMASK |= BIT16;
    // Select a generic clock for the ADC 
    // Will route the main 48MHz clock to ADC.
    GCLK_CLKCTRL = 0x17 + BIT14;    
    while(  (GCLK_STATUS & BIT7)); // wait for sync to complete
    ADC_REFCTRL = 0x82; // select Vdd/2 as reference with buffer offset compensation 
    ADC_AVGCTRL = 0; // no averaging
    ADC_SAMPCTRL = 0x3f; // maximum sample & hold time
    // ADC conversion clock = 48MHz / PRESCALER.  Set prescaler=512 (setting 7)
    ADC_CTRLB = 0x0700; // set prescaler to 512,12bit, no correction, single shot, right adjust, single ended
    ADC_WINCTRL = 0; // no windowing
    // Load the calibration data from non volatile memory
    ADC_CALIB = ((NVM_CALIBRATION_AREA.ADC_BIAS_CAL) << 8) + NVM_CALIBRATION_AREA.ADC_LINEARITY;        
    ADC_CTRLA = BIT1; // enable the ADC
    
    // Enable special function on AIN[0]
    PAPMUX1 = 0x01;  // enable special function B on PA2 (Pin 3)    
    PAPPINCFG2 |= BIT0; // enable special function multplexing on Pin 3     
}
uint32_t readADC(int channel)
{
    ADC_INTFLAG = BIT0; // clear result ready bit    
    ADC_INPUTCTRL = (channel & 0x1f) + (0x19 << 8); // set the channel number, negative mux to ioground
    while(ADC_STATUS & BIT7); //wait for sync to complete
    ADC_SWTRIG = BIT1; // start a conversion
    while(ADC_STATUS & BIT7); //wait for sync to complete
    while ((ADC_INTFLAG & BIT0)==0); // wait for conversion to complete    
    return ADC_RESULT;
}
int main()
{ 
    int i=0;
    PADIRSET = BIT0; // make Port A bit 0 an output, no gain, no scanning , single ended
    // Startup delay to allow escape from a potentially bricked chip: ONLY DELETE WHEN SURE OF PROPER CLOCK OPERATION
    for (i=0;i<10;i++)
    {
        PAOUTTGL = BIT0; // Toggle Port A bit 0
        delay(1000000);   // Wait  
    }    
    initUART(); // get SERCOM0 going
    initADC();  // get ADC going
    enable_interrupts();
    printString("Hello SamD!\r\n");    
    while(1)
    {       
        printInteger(readADC(0));
        printString("\r\n");
        PAOUTTGL = BIT0; // Toggle Port A bit 0
        delay(1000000);   // Wait  
        
    }
   
}
    

    
