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
	main();
}

void Default_Handler()
{
	while(1);
}
