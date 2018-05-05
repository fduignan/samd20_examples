// Serial I/O routines
#include "serial.h"
#include <stdint.h>
#include "../samd20e16.h"

SerialBuffer TXBuffer,RXBuffer;
void UART_isr(void);
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
    SERCOM0_CTRLB = BIT17 + BIT9 ; // enable RX, Start-of-frame wakeup, 1 stop bit, 8 bits;
    // 0x00030200 RXEN,TXEN,SFDE,
    while(SERCOM0_STATUS & BIT15); // wait for sync to complete
    SERCOM0_CTRLA = BIT30 + BIT20 + BIT2 + BIT1; // LSB first, UART mode , internal clock, PAD1 = RX, PAD0 = TX, ENABLE    
    // 0x40000006 DORD,ENABLE,MODE001 (USART INTERNAL CLOCK), ENABLE
    while(SERCOM0_STATUS & BIT15); // wait for synchronization between clock domains to complete    
    // The actual special function is selected by writing to the upper 4 bits of PAPMUX5 
    // To select function C, write  '2' to these bits
    PAPMUX4 = 0x22;    
    PAPPINCFG8 |= BIT0; // enable special function multplexing on Pin 11                
    PAPPINCFG9 |= BIT0; // enable special function multplexing on Pin 
    SERCOM0_INTFLAG = 0x0f; // clear (some) pending interrupts (if any)
    SERCOM0_INTENSET = BIT2 + BIT1; // enable TXC, RXC interrupts
    NVIC_ISER = BIT7; // allow SERCOM0 interrupts pass through the NVIC
}
void SERCOM0_Handler(void)
{
	int Source=SERCOM0_INTFLAG; // have to cache the interrupt id register
                                // as the 'if' clause below were reading it
                                // and hence changing its contents.
	if (Source & BIT2) // RX Interrupt
	{
		putBuf(&RXBuffer,SERCOM0_DATA);
	}
	if (Source & BIT1) // DRE (TX) Interrupt
	{
		if (TXBuffer.count > 0)
			SERCOM0_DATA = getBuf(&TXBuffer);
        else
        {
            SERCOM0_CTRLB &= ~BIT16; // no more data, disable the transmitter
            SERCOM0_INTFLAG = BIT1; 
        }
	}
}
void putBuf(SerialBuffer *sbuf, char c)
{
	if (sbuf->count < SBUFSIZE)
	{
		disable_interrupts();
		sbuf->count++;
		sbuf->buffer[sbuf->head] = c;
		sbuf->head=(sbuf->head+1) % SBUFSIZE;
		enable_interrupts();
	}
}
char getBuf(SerialBuffer *sbuf)
{
	char c=0;
	if (sbuf->count >0 )
	{
		disable_interrupts();
		sbuf->count--;
		c=sbuf->buffer[sbuf->tail];
		sbuf->tail=(sbuf->tail+1) % SBUFSIZE;
		enable_interrupts();
	}
	return c;
}
int rx_count()
{
	return RXBuffer.count;
}
int tx_count()
{
	return TXBuffer.count;
}
void eputc(char c)
{
	if (SERCOM0_CTRLB & BIT16) // transmitter enabled?
    {
        putBuf(&TXBuffer,c);	// Transmitter enabled (in use) so buffer		
    }
	else
	{
        SERCOM0_CTRLB |= BIT16; // enable transmitter
        while(SERCOM0_STATUS & BIT15); // wait for sync to complete           
        SERCOM0_DATA = c; // Transmitter was not enabled, so write out direct to TX register
	}
}
char egetc()
{
	return getBuf(&RXBuffer);
}
void printString(char *String)
{
	while(*String)
	{
		eputc(*String);
		String++;
	}
}
char HexDigit(int Value)
{
	if ((Value >=0) && (Value < 10))
		return Value+'0';
	else if ((Value >9) && (Value < 16))
		return Value-10 + 'A';
	else
		return 'z';
}
void printInteger(unsigned int Number)
{
	// Output the number over the serial port as
	// as hexadecimal string.
	char TxString[9];
	int Index=8;
	TxString[Index]=0; // terminate the string
	Index--;
	while(Index >=0)
	{
		TxString[Index]=HexDigit(Number & 0x0f);
		Number = Number >> 4;
		Index--;
	}
	printString(TxString);
}
