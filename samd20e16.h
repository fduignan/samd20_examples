// Simplified IO Device map for SAMD20E16 processor
// First release April 2018
// Author : Frank Duignan

#include <stdint.h>
#define BIT0 (1 << 0)
#define BIT1 (1 << 1)
#define BIT2 (1 << 2)
#define BIT3 (1 << 3)
#define BIT4 (1 << 4)
#define BIT5 (1 << 5)
#define BIT6 (1 << 6)
#define BIT7 (1 << 7)
#define BIT8 (1 << 8)
#define BIT9 (1 << 9)
#define BIT10 (1 << 10)
#define BIT11 (1 << 11)
#define BIT12 (1 << 12)
#define BIT13 (1 << 13)
#define BIT14 (1 << 14)
#define BIT15 (1 << 15)
#define BIT16 (1 << 16)
#define BIT17 (1 << 17)
#define BIT18 (1 << 18)
#define BIT19 (1 << 19)
#define BIT20 (1 << 20)
#define BIT21 (1 << 21)
#define BIT22 (1 << 22)
#define BIT23 (1 << 23)
#define BIT24 (1 << 24)
#define BIT25 (1 << 25)
#define BIT26 (1 << 26)
#define BIT27 (1 << 27)
#define BIT28 (1 << 28)
#define BIT29 (1 << 29)
#define BIT30 (1 << 30)
#define BIT31 (1 << 31)

// Macros to reduce typing later on
#define  REGISTER_32(ADDRESS) (*((volatile uint32_t *)(ADDRESS)))
#define  REGISTER_16(ADDRESS) (*((volatile uint16_t *)(ADDRESS)))
#define  REGISTER_8(ADDRESS) (*((volatile uint8_t *)(ADDRESS)))

// Macros to enable/disable global interrupts
#define enable_interrupts() asm(" cpsie i ")
#define disable_interrupts() asm(" cpsid i ")
#define cpu_sleep() asm(" wfi ")
#define PAC0_BASE       0x40000000
#define PM_BASE         0x40000400
#define SYSCTRL_BASE    0x40000800
#define GCLK_BASE       0x40000c00
#define WDT_BASE        0x40001000
#define RTC_BASE        0x40001400
#define EIC_BASE        0x40001800
#define PAC1_BASE       0x41000000
#define DSU_BASE        0x41002000
#define NVM_BASE        0x41004000
#define PORTA_BASE      0x41004400
#define PORTB_BASE      0x41004480
#define PAC2_BASE       0x42000000
#define EVSYS_BASE      0x42000400
#define SERCOM0_BASE    0x42000800
#define SERCOM1_BASE    0x42000c00
#define SERCOM2_BASE    0x42001000
#define SERCOM3_BASE    0x42001400
#define SERCOM4_BASE    0x42001800
#define SERCOM5_BASE    0x42001c00
#define TC0_BASE        0x42002000
#define TC1_BASE        0x42002400
#define TC2_BASE        0x42002800
#define TC3_BASE        0x42002c00
#define TC4_BASE        0x42003000
#define TC5_BASE        0x42003400
#define TC6_BASE        0x42003800
#define TC7_BASE        0x42003c00
#define ADC_BASE        0x42004000
#define AC_BASE         0x42004400
#define DAC_BASE        0x42004800
#define PTC_BASE        0x42004c00


// PAC0
#define PAC0_WPCLR      REGISTER_32(PAC0_BASE + 0x0000)
#define PAC0_WPSET      REGISTER_32(PAC0_BASE + 0x0004)
// PM
#define PM_CTRL         REGISTER_8(PM_BASE + 0x0000)
#define PM_SLEEP        REGISTER_8(PM_BASE + 0x0001)
#define PM_CPUSEL       REGISTER_8(PM_BASE + 0x0008)
#define PM_APBASEL      REGISTER_8(PM_BASE + 0x0009)
#define PM_APBBSEL      REGISTER_8(PM_BASE + 0x000a)
#define PM_APBCSEL      REGISTER_8(PM_BASE + 0x000b)
#define PM_AHBMASK      REGISTER_32(PM_BASE + 0x0014)
#define PM_APBAMASK     REGISTER_32(PM_BASE + 0x0018)
#define PM_APBBMASK     REGISTER_32(PM_BASE + 0x001c)
#define PM_APBCMASK     REGISTER_32(PM_BASE + 0x0020)
#define PM_INTENCLR     REGISTER_8(PM_BASE + 0x0034)
#define PM_INTENSET     REGISTER_8(PM_BASE + 0x0035)
#define PM_INFLAG       REGISTER_8(PM_BASE + 0x0036)
#define PM_RCAUSE       REGISTER_8(PM_BASE + 0x0038)
// SYSCTRL
#define SYSCTRL_INTENCLR    REGISTER_32(SYSCTRL_BASE + 0x0000)
#define SYSCTRL_INTENSET    REGISTER_32(SYSCTRL_BASE + 0x0004)
#define SYSCTRL_INTFLAG     REGISTER_32(SYSCTRL_BASE + 0x0008)
#define SYSCTRL_PCLKSR      REGISTER_32(SYSCTRL_BASE + 0x000c)
#define SYSCTRL_XOSC        REGISTER_32(SYSCTRL_BASE + 0x0010)
#define SYSCTRL_XOSC32K     REGISTER_32(SYSCTRL_BASE + 0x0014)
#define SYSCTRL_OSC32K      REGISTER_32(SYSCTRL_BASE + 0x0018)
#define SYSCTRL_OSCULP32K   REGISTER_32(SYSCTRL_BASE + 0x001c)
#define SYSCTRL_OSC8M       REGISTER_32(SYSCTRL_BASE + 0x0020)
#define SYSCTRL_DFLLCTRL    REGISTER_32(SYSCTRL_BASE + 0x0024)
#define SYSCTRL_DFLLVAL     REGISTER_32(SYSCTRL_BASE + 0x0028)
#define SYSCTRL_DFLLMUL     REGISTER_32(SYSCTRL_BASE + 0x002c)
#define SYSCTRL_BOD33       REGISTER_32(SYSCTRL_BASE + 0x0034)
#define SYSCTRL_VREG        REGISTER_32(SYSCTRL_BASE + 0x003c)
#define SYSCTRL_VREF        REGISTER_32(SYSCTRL_BASE + 0x0040)

// GCLK 
#define GCLK_CTRL       REGISTER_8(GCLK_BASE + 0x0000)
#define GCLK_STATUS     REGISTER_8(GCLK_BASE + 0x0001)
#define GCLK_CLKCTRL    REGISTER_16(GCLK_BASE + 0x0002)
#define GCLK_GENCTRL    REGISTER_32(GCLK_BASE + 0x0004)
#define GCLK_GENDIV     REGISTER_32(GCLK_BASE + 0x0008)

// WDT 
#define WDT_CTRL        REGISTER_8(WDT_BASE + 0x0000)
#define WDT_CONFIG      REGISTER_8(WDT_BASE + 0x0001)
#define WDT_EWCTRL      REGISTER_8(WDT_BASE + 0x0002)
#define WDT_INTENCLR    REGISTER_8(WDT_BASE + 0x0004)
#define WDT_INTENSET    REGISTER_8(WDT_BASE + 0x0005)
#define WDT_INTFLAG     REGISTER_8(WDT_BASE + 0x0006)
#define WDT_STATUS      REGISTER_8(WDT_BASE + 0x0007)   
#define WDT_CLEAR       REGISTER_8(WDT_BASE + 0x0008)   

// RTC definitions for MODE0 (32 bit) operation only.
#define RTC_CTRL        REGISTER_16(RTC_BASE + 0x0000)
#define RTC_READREQ     REGISTER_16(RTC_BASE + 0x0002)
#define RTC_EVCTRL      REGISTER_16(RTC_BASE + 0x0004)
#define RTC_INTENCLR    REGISTER_8(RTC_BASE + 0x0006)
#define RTC_INTENSET    REGISTER_8(RTC_BASE + 0x0007)
#define RTC_INTFLAG     REGISTER_8(RTC_BASE + 0x0008)
#define RTC_STATUS      REGISTER_8(RTC_BASE + 0x000a)
#define RTC_DBGCTRL     REGISTER_8(RTC_BASE + 0x000b)
#define RTC_FREQCORR    REGISTER_8(RTC_BASE + 0x000c)
#define RTC_COUNT       REGISTER_32(RTC_BASE + 0x0010)
#define RTC_COMP0       REGISTER_32(RTC_BASE + 0x0018)

// EIC 
#define EIC_CTRL        REGISTER_8(EIC_BASE + 0x0000)
#define EIC_STATUS      REGISTER_8(EIC_BASE + 0x0001)
#define EIC_NMICTRL     REGISTER_8(EIC_BASE + 0x0002)
#define EIC_NMIFLAG     REGISTER_8(EIC_BASE + 0x0003)
#define EIC_EVCTRL      REGISTER_32(EIC_BASE + 0x0004)
#define EIC_INTENCLR    REGISTER_32(EIC_BASE + 0x0008)
#define EIC_INTENSET    REGISTER_32(EIC_BASE + 0x000c)
#define EIC_INTENFLAG   REGISTER_32(EIC_BASE + 0x0010)
#define EIC_WAKEUP      REGISTER_32(EIC_BASE + 0x0014)
#define EIC_CONFIG0      REGISTER_32(EIC_BASE + 0x0018)
#define EIC_CONFIG1      REGISTER_32(EIC_BASE + 0x001c)

// PAC1
#define PAC1_WPCLR      REGISTER_32(PAC1_BASE + 0x0000)
#define PAC1_WPSET      REGISTER_32(PAC1_BASE + 0x0004)

// DSU (Device Service Unit (debug interface)
#define DSU_CTRL        REGISTER_8(DSU_BASE + 0x0000)
#define DSU_STATUSA     REGISTER_8(DSU_BASE + 0x0001)
#define DSU_STATUSB     REGISTER_8(DSU_BASE + 0x0002)
#define DSU_ADDR        REGISTER_32(DSU_BASE + 0x0004)
#define DSU_LENGTH      REGISTER_32(DSU_BASE + 0x0008)
#define DSU_DATA        REGISTER_32(DSU_BASE + 0x000c)
#define DSU_DCC0        REGISTER_32(DSU_BASE + 0x0010)
#define DSU_DCC1        REGISTER_32(DSU_BASE + 0x0014)
#define DSU_DID         REGISTER_32(DSU_BASE + 0x0018)
#define DSU_ENTRY0      REGISTER_32(DSU_BASE + 0x1000)
#define DSU_ENTRY1      REGISTER_32(DSU_BASE + 0x1004)
#define DSU_END         REGISTER_32(DSU_BASE + 0x1008)
#define DSU_MEMTYPE     REGISTER_32(DSU_BASE + 0x1fcc)
#define DSU_PID4        REGISTER_32(DSU_BASE + 0x1fd0)
#define DSU_PID0        REGISTER_32(DSU_BASE + 0x1fe0)
#define DSU_PID1        REGISTER_32(DSU_BASE + 0x1fe4)
#define DSU_PID2        REGISTER_32(DSU_BASE + 0x1fe8)
#define DSU_PID3        REGISTER_32(DSU_BASE + 0x1fec)
#define DSU_CID0        REGISTER_32(DSU_BASE + 0x1ff0)
#define DSU_CID1        REGISTER_32(DSU_BASE + 0x1ff4)
#define DSU_CID2        REGISTER_32(DSU_BASE + 0x1ff8)
#define DSU_CID3        REGISTER_32(DSU_BASE + 0x1ffc)

// NVMCTRL 
#define NVM_CTRLA       REGISTER_16(NVM_BASE + 0x0000)
#define NVM_CTRLB       REGISTER_32(NVM_BASE + 0x0004)
#define NVM_PARAM       REGISTER_32(NVM_BASE + 0x0008)
#define NVM_INTENCLR    REGISTER_8(NVM_BASE + 0x000c)
#define NVM_INTENSET    REGISTER_8(NVM_BASE + 0x0010)
#define NVM_INTFLAG     REGISTER_8(NVM_BASE + 0x0014)
#define NVM_STATUS      REGISTER_8(NVM_BASE + 0x0018)
#define NVM_ADDR        REGISTER_32(NVM_BASE + 0x001c)
#define NVM_LOCK        REGISTER_8(NVM_BASE + 0x0020)

// PORTA
#define PADIR       REGISTER_32(PORTA_BASE + 0x0000)
#define PADIRCLR    REGISTER_32(PORTA_BASE + 0x0004)
#define PADIRSET    REGISTER_32(PORTA_BASE + 0x0008)
#define PADIRTGL    REGISTER_32(PORTA_BASE + 0x000c)
#define PAOUT       REGISTER_32(PORTA_BASE + 0x0010)
#define PAOUTCLR    REGISTER_32(PORTA_BASE + 0x0014)
#define PAOUTSET    REGISTER_32(PORTA_BASE + 0x0018)
#define PAOUTTGL    REGISTER_32(PORTA_BASE + 0x001c)
#define PAIN        REGISTER_32(PORTA_BASE + 0x0020)
#define PACTRL      REGISTER_32(PORTA_BASE + 0x0024)
#define PAWRCONFIG  REGISTER_32(PORTA_BASE + 0x0028)
#define PAPMUX0     REGISTER_8(PORTA_BASE + 0x0030)
#define PAPMUX1     REGISTER_8(PORTA_BASE + 0x0031)
#define PAPMUX2     REGISTER_8(PORTA_BASE + 0x0032)
#define PAPMUX3     REGISTER_8(PORTA_BASE + 0x0033)
#define PAPMUX4     REGISTER_8(PORTA_BASE + 0x0034)
#define PAPMUX5     REGISTER_8(PORTA_BASE + 0x0035)
#define PAPMUX6     REGISTER_8(PORTA_BASE + 0x0036)
#define PAPMUX7     REGISTER_8(PORTA_BASE + 0x0037)
#define PAPMUX8     REGISTER_8(PORTA_BASE + 0x0038)
#define PAPMUX9     REGISTER_8(PORTA_BASE + 0x0039)
#define PAPMUX10    REGISTER_8(PORTA_BASE + 0x003a)
#define PAPMUX11    REGISTER_8(PORTA_BASE + 0x003b)
#define PAPMUX12    REGISTER_8(PORTA_BASE + 0x003c)
#define PAPMUX13    REGISTER_8(PORTA_BASE + 0x003d)
#define PAPMUX14    REGISTER_8(PORTA_BASE + 0x003e)
#define PAPMUX15    REGISTER_8(PORTA_BASE + 0x003f)
#define PAPPINCFG0  REGISTER_8(PORTA_BASE + 0x0040)
#define PAPPINCFG1  REGISTER_8(PORTA_BASE + 0x0041)
#define PAPPINCFG2  REGISTER_8(PORTA_BASE + 0x0042)
#define PAPPINCFG3  REGISTER_8(PORTA_BASE + 0x0043)
#define PAPPINCFG4  REGISTER_8(PORTA_BASE + 0x0044)
#define PAPPINCFG5  REGISTER_8(PORTA_BASE + 0x0045)
#define PAPPINCFG6  REGISTER_8(PORTA_BASE + 0x0046)
#define PAPPINCFG7  REGISTER_8(PORTA_BASE + 0x0047)
#define PAPPINCFG8  REGISTER_8(PORTA_BASE + 0x0048)
#define PAPPINCFG9  REGISTER_8(PORTA_BASE + 0x0049)
#define PAPPINCFG10 REGISTER_8(PORTA_BASE + 0x004a)
#define PAPPINCFG11 REGISTER_8(PORTA_BASE + 0x004b)
#define PAPPINCFG12 REGISTER_8(PORTA_BASE + 0x004c)
#define PAPPINCFG13 REGISTER_8(PORTA_BASE + 0x004d)
#define PAPPINCFG14 REGISTER_8(PORTA_BASE + 0x004e)
#define PAPPINCFG15 REGISTER_8(PORTA_BASE + 0x004f)
#define PAPPINCFG16 REGISTER_8(PORTA_BASE + 0x0050)
#define PAPPINCFG17 REGISTER_8(PORTA_BASE + 0x0051)
#define PAPPINCFG18 REGISTER_8(PORTA_BASE + 0x0052)
#define PAPPINCFG19 REGISTER_8(PORTA_BASE + 0x0053)
#define PAPPINCFG20 REGISTER_8(PORTA_BASE + 0x0054)
#define PAPPINCFG21 REGISTER_8(PORTA_BASE + 0x0055)
#define PAPPINCFG22 REGISTER_8(PORTA_BASE + 0x0056)
#define PAPPINCFG23 REGISTER_8(PORTA_BASE + 0x0057)
#define PAPPINCFG24 REGISTER_8(PORTA_BASE + 0x0058)
#define PAPPINCFG25 REGISTER_8(PORTA_BASE + 0x0059)
#define PAPPINCFG26 REGISTER_8(PORTA_BASE + 0x005a)
#define PAPPINCFG27 REGISTER_8(PORTA_BASE + 0x005b)
#define PAPPINCFG28 REGISTER_8(PORTA_BASE + 0x005c)
#define PAPPINCFG29 REGISTER_8(PORTA_BASE + 0x005d)
#define PAPPINCFG30 REGISTER_8(PORTA_BASE + 0x005e)
#define PAPPINCFG31 REGISTER_8(PORTA_BASE + 0x005f)
// PORTB
#define PBDIR       REGISTER_32(PORTB_BASE + 0x0000)
#define PBDIRCLR    REGISTER_32(PORTB_BASE + 0x0004)
#define PBDIRSET    REGISTER_32(PORTB_BASE + 0x0008)
#define PBDIRTGL    REGISTER_32(PORTB_BASE + 0x000c)
#define PBOUT       REGISTER_32(PORTB_BASE + 0x0010)
#define PBOUTCLR    REGISTER_32(PORTB_BASE + 0x0014)
#define PBOUTSET    REGISTER_32(PORTB_BASE + 0x0018)
#define PBOUTTGL    REGISTER_32(PORTB_BASE + 0x001c)
#define PBIN        REGISTER_32(PORTB_BASE + 0x0020)
#define PBCTRL      REGISTER_32(PORTB_BASE + 0x0024)
#define PBWRCONFIG  REGISTER_32(PORTB_BASE + 0x0028)
#define PBPMUX0     REGISTER_8(PORTB_BASE + 0x0030)
#define PBPMUX1     REGISTER_8(PORTB_BASE + 0x0031)
#define PBPMUX2     REGISTER_8(PORTB_BASE + 0x0032)
#define PBPMUX3     REGISTER_8(PORTB_BASE + 0x0033)
#define PBPMUX4     REGISTER_8(PORTB_BASE + 0x0034)
#define PBPMUX5     REGISTER_8(PORTB_BASE + 0x0035)
#define PBPMUX6     REGISTER_8(PORTB_BASE + 0x0036)
#define PBPMUX7     REGISTER_8(PORTB_BASE + 0x0037)
#define PBPMUX8     REGISTER_8(PORTB_BASE + 0x0038)
#define PBPMUX9     REGISTER_8(PORTB_BASE + 0x0039)
#define PBPMUX10    REGISTER_8(PORTB_BASE + 0x003a)
#define PBPMUX11    REGISTER_8(PORTB_BASE + 0x003b)
#define PBPMUX12    REGISTER_8(PORTB_BASE + 0x003c)
#define PBPMUX13    REGISTER_8(PORTB_BASE + 0x003d)
#define PBPMUX14    REGISTER_8(PORTB_BASE + 0x003e)
#define PBPMUX15    REGISTER_8(PORTB_BASE + 0x003f)
#define PBPPINCFG0  REGISTER_8(PORTB_BASE + 0x0040)
#define PBPPINCFG1  REGISTER_8(PORTB_BASE + 0x0041)
#define PBPPINCFG2  REGISTER_8(PORTB_BASE + 0x0042)
#define PBPPINCFG3  REGISTER_8(PORTB_BASE + 0x0043)
#define PBPPINCFG4  REGISTER_8(PORTB_BASE + 0x0044)
#define PBPPINCFG5  REGISTER_8(PORTB_BASE + 0x0045)
#define PBPPINCFG6  REGISTER_8(PORTB_BASE + 0x0046)
#define PBPPINCFG7  REGISTER_8(PORTB_BASE + 0x0047)
#define PBPPINCFG8  REGISTER_8(PORTB_BASE + 0x0048)
#define PBPPINCFG9  REGISTER_8(PORTB_BASE + 0x0049)
#define PBPPINCFG10 REGISTER_8(PORTB_BASE + 0x004a)
#define PBPPINCFG11 REGISTER_8(PORTB_BASE + 0x004b)
#define PBPPINCFG12 REGISTER_8(PORTB_BASE + 0x004c)
#define PBPPINCFG13 REGISTER_8(PORTB_BASE + 0x004d)
#define PBPPINCFG14 REGISTER_8(PORTB_BASE + 0x004e)
#define PBPPINCFG15 REGISTER_8(PORTB_BASE + 0x004f)
#define PBPPINCFG16 REGISTER_8(PORTB_BASE + 0x0050)
#define PBPPINCFG17 REGISTER_8(PORTB_BASE + 0x0051)
#define PBPPINCFG18 REGISTER_8(PORTB_BASE + 0x0052)
#define PBPPINCFG19 REGISTER_8(PORTB_BASE + 0x0053)
#define PBPPINCFG20 REGISTER_8(PORTB_BASE + 0x0054)
#define PBPPINCFG21 REGISTER_8(PORTB_BASE + 0x0055)
#define PBPPINCFG22 REGISTER_8(PORTB_BASE + 0x0056)
#define PBPPINCFG23 REGISTER_8(PORTB_BASE + 0x0057)
#define PBPPINCFG24 REGISTER_8(PORTB_BASE + 0x0058)
#define PBPPINCFG25 REGISTER_8(PORTB_BASE + 0x0059)
#define PBPPINCFG26 REGISTER_8(PORTB_BASE + 0x005a)
#define PBPPINCFG27 REGISTER_8(PORTB_BASE + 0x005b)
#define PBPPINCFG28 REGISTER_8(PORTB_BASE + 0x005c)
#define PBPPINCFG29 REGISTER_8(PORTB_BASE + 0x005d)
#define PBPPINCFG30 REGISTER_8(PORTB_BASE + 0x005e)
#define PBPPINCFG31 REGISTER_8(PORTB_BASE + 0x005f)
// PAC2
#define PAC2_WPCLR      REGISTER_32(PAC2_BASE + 0x0000)
#define PAC2_WPSET      REGISTER_32(PAC2_BASE + 0x0004)
// EVSYS
#define EVSYS_CTRL      REGISTER_8(PORTB_BASE + 0x0000)
#define EVSYS_CHANNEL   REGISTER_32(PORTB_BASE + 0x0004)
#define EVSYS_USER      REGISTER_16(PORTB_BASE + 0x0008)
#define EVSYS_CHSTATUS  REGISTER_32(PORTB_BASE + 0x000c)
#define EVSYS_INTENCLR  REGISTER_32(PORTB_BASE + 0x0010)
#define EVSYS_INTENSET  REGISTER_32(PORTB_BASE + 0x0014)
#define EVSYS_INTFLAG   REGISTER_32(PORTB_BASE + 0x0018)

// SERCOM0 There are different modes: USART,SPI,I2C Slave, I2C Master
#define SERCOM0_CTRLA       REGISTER_32(SERCOM0_BASE + 0x0000)
#define SERCOM0_CTRLB       REGISTER_32(SERCOM0_BASE + 0x0004)
#define SERCOM0_DBGCTRL     REGISTER_8(SERCOM0_BASE + 0x0008)
#define SERCOM0_BAUD        REGISTER_16(SERCOM0_BASE + 0x000a)
#define SERCOM0_INTENCLR    REGISTER_8(SERCOM0_BASE + 0x000c)
#define SERCOM0_INTENSET    REGISTER_8(SERCOM0_BASE + 0x000d)
#define SERCOM0_INTFLAG     REGISTER_8(SERCOM0_BASE + 0x000e)
#define SERCOM0_STATUS      REGISTER_16(SERCOM0_BASE + 0x0010)
#define SERCOM0_ADDR        REGISTER_32(SERCOM0_BASE + 0x0014)
#define SERCOM0_DATA        REGISTER_16(SERCOM0_BASE + 0x0018)

// SERCOM1 There are different modes: USART,SPI,I2C Slave, I2C Master
#define SERCOM1_CTRLA       REGISTER_32(SERCOM1_BASE + 0x0000)
#define SERCOM1_CTRLB       REGISTER_32(SERCOM1_BASE + 0x0004)
#define SERCOM1_DBGCTRL     REGISTER_8(SERCOM1_BASE + 0x0008)
#define SERCOM1_BAUD        REGISTER_16(SERCOM1_BASE + 0x000a)
#define SERCOM1_INTENCLR    REGISTER_8(SERCOM1_BASE + 0x000c)
#define SERCOM1_INTENSET    REGISTER_8(SERCOM1_BASE + 0x000d)
#define SERCOM1_INTFLAG     REGISTER_8(SERCOM1_BASE + 0x000e)
#define SERCOM1_STATUS      REGISTER_16(SERCOM1_BASE + 0x0010)
#define SERCOM1_ADDR        REGISTER_32(SERCOM1_BASE + 0x0014)
#define SERCOM1_DATA        REGISTER_16(SERCOM1_BASE + 0x0018)

// SERCOM2 There are different modes: USART,SPI,I2C Slave, I2C Master
#define SERCOM2_CTRLA       REGISTER_32(SERCOM2_BASE + 0x0000)
#define SERCOM2_CTRLB       REGISTER_32(SERCOM2_BASE + 0x0004)
#define SERCOM2_DBGCTRL     REGISTER_8(SERCOM2_BASE + 0x0008)
#define SERCOM2_BAUD        REGISTER_16(SERCOM2_BASE + 0x000a)
#define SERCOM2_INTENCLR    REGISTER_8(SERCOM2_BASE + 0x000c)
#define SERCOM2_INTENSET    REGISTER_8(SERCOM2_BASE + 0x000d)
#define SERCOM2_INTFLAG     REGISTER_8(SERCOM2_BASE + 0x000e)
#define SERCOM2_STATUS      REGISTER_16(SERCOM2_BASE + 0x0010)
#define SERCOM2_ADDR        REGISTER_32(SERCOM2_BASE + 0x0014)
#define SERCOM2_DATA        REGISTER_16(SERCOM2_BASE + 0x0018)

// SERCOM3 There are different modes: USART,SPI,I2C Slave, I2C Master
#define SERCOM3_CTRLA       REGISTER_32(SERCOM3_BASE + 0x0000)
#define SERCOM3_CTRLB       REGISTER_32(SERCOM3_BASE + 0x0004)
#define SERCOM3_DBGCTRL     REGISTER_8(SERCOM3_BASE + 0x0008)
#define SERCOM3_BAUD        REGISTER_16(SERCOM3_BASE + 0x000a)
#define SERCOM3_INTENCLR    REGISTER_8(SERCOM3_BASE + 0x000c)
#define SERCOM3_INTENSET    REGISTER_8(SERCOM3_BASE + 0x000d)
#define SERCOM3_INTFLAG     REGISTER_8(SERCOM3_BASE + 0x000e)
#define SERCOM3_STATUS      REGISTER_16(SERCOM3_BASE + 0x0010)
#define SERCOM3_ADDR        REGISTER_32(SERCOM3_BASE + 0x0014)
#define SERCOM3_DATA        REGISTER_16(SERCOM3_BASE + 0x0018)

// SERCOM4 There are different modes: USART,SPI,I2C Slave, I2C Master
#define SERCOM4_CTRLA       REGISTER_32(SERCOM4_BASE + 0x0000)
#define SERCOM4_CTRLB       REGISTER_32(SERCOM4_BASE + 0x0004)
#define SERCOM4_DBGCTRL     REGISTER_8(SERCOM4_BASE + 0x0008)
#define SERCOM4_BAUD        REGISTER_16(SERCOM4_BASE + 0x000a)
#define SERCOM4_INTENCLR    REGISTER_8(SERCOM4_BASE + 0x000c)
#define SERCOM4_INTENSET    REGISTER_8(SERCOM4_BASE + 0x000d)
#define SERCOM4_INTFLAG     REGISTER_8(SERCOM4_BASE + 0x000e)
#define SERCOM4_STATUS      REGISTER_16(SERCOM4_BASE + 0x0010)
#define SERCOM4_ADDR        REGISTER_32(SERCOM4_BASE + 0x0014)
#define SERCOM4_DATA        REGISTER_16(SERCOM4_BASE + 0x0018)

// SERCOM5 There are different modes: USART,SPI,I2C Slave, I2C Master
#define SERCOM5_CTRLA       REGISTER_32(SERCOM5_BASE + 0x0000)
#define SERCOM5_CTRLB       REGISTER_32(SERCOM5_BASE + 0x0004)
#define SERCOM5_DBGCTRL     REGISTER_8(SERCOM5_BASE + 0x0008)
#define SERCOM5_BAUD        REGISTER_16(SERCOM5_BASE + 0x000a)
#define SERCOM5_INTENCLR    REGISTER_8(SERCOM5_BASE + 0x000c)
#define SERCOM5_INTENSET    REGISTER_8(SERCOM5_BASE + 0x000d)
#define SERCOM5_INTFLAG     REGISTER_8(SERCOM5_BASE + 0x000e)
#define SERCOM5_STATUS      REGISTER_16(SERCOM5_BASE + 0x0010)
#define SERCOM5_ADDR        REGISTER_32(SERCOM5_BASE + 0x0014)
#define SERCOM5_DATA        REGISTER_16(SERCOM5_BASE + 0x0018)

// TC0  only 32 bit mode is defined here.
#define TC0_CTRLA           REGISTER_16(TC0_BASE + 0x0000)
#define TC0_READREQ         REGISTER_16(TC0_BASE + 0x0002)
#define TC0_CTRLBCLR        REGISTER_8(TC0_BASE + 0x0004)
#define TC0_CTRLBSET        REGISTER_8(TC0_BASE + 0x0005)
#define TC0_CTRLC           REGISTER_8(TC0_BASE + 0x0006)
#define TC0_DBGCTRL         REGISTER_8(TC0_BASE + 0x0008)
#define TC0_EVCTRL          REGISTER_16(TC0_BASE + 0x000a)
#define TC0_INTCLR          REGISTER_8(TC0_BASE + 0x000c)
#define TC0_INTSET          REGISTER_8(TC0_BASE + 0x000d)
#define TC0_INTFLAG         REGISTER_8(TC0_BASE + 0x000e)
#define TC0_STATUS          REGISTER_8(TC0_BASE + 0x000f)
#define TC0_COUNT           REGISTER_32(TC0_BASE + 0x0010)
#define TC0_CC0             REGISTER_32(TC0_BASE + 0x0018)
#define TC0_CC1             REGISTER_32(TC0_BASE + 0x001c)

// TC1  only 32 bit mode is defined here.
#define TC1_CTRLA           REGISTER_16(TC1_BASE + 0x0000)
#define TC1_READREQ         REGISTER_16(TC1_BASE + 0x0002)
#define TC1_CTRLBCLR        REGISTER_8(TC1_BASE + 0x0004)
#define TC1_CTRLBSET        REGISTER_8(TC1_BASE + 0x0005)
#define TC1_CTRLC           REGISTER_8(TC1_BASE + 0x0006)
#define TC1_DBGCTRL         REGISTER_8(TC1_BASE + 0x0008)
#define TC1_EVCTRL          REGISTER_16(TC1_BASE + 0x000a)
#define TC1_INTCLR          REGISTER_8(TC1_BASE + 0x000c)
#define TC1_INTSET          REGISTER_8(TC1_BASE + 0x000d)
#define TC1_INTFLAG         REGISTER_8(TC1_BASE + 0x000e)
#define TC1_STATUS          REGISTER_8(TC1_BASE + 0x000f)
#define TC1_COUNT           REGISTER_32(TC1_BASE + 0x0010)
#define TC1_CC0             REGISTER_32(TC1_BASE + 0x0018)
#define TC1_CC1             REGISTER_32(TC1_BASE + 0x001c)

// TC2  only 32 bit mode is defined here.
#define TC2_CTRLA           REGISTER_16(TC2_BASE + 0x0000)
#define TC2_READREQ         REGISTER_16(TC2_BASE + 0x0002)
#define TC2_CTRLBCLR        REGISTER_8(TC2_BASE + 0x0004)
#define TC2_CTRLBSET        REGISTER_8(TC2_BASE + 0x0005)
#define TC2_CTRLC           REGISTER_8(TC2_BASE + 0x0006)
#define TC2_DBGCTRL         REGISTER_8(TC2_BASE + 0x0008)
#define TC2_EVCTRL          REGISTER_16(TC2_BASE + 0x000a)
#define TC2_INTCLR          REGISTER_8(TC2_BASE + 0x000c)
#define TC2_INTSET          REGISTER_8(TC2_BASE + 0x000d)
#define TC2_INTFLAG         REGISTER_8(TC2_BASE + 0x000e)
#define TC2_STATUS          REGISTER_8(TC2_BASE + 0x000f)
#define TC2_COUNT           REGISTER_32(TC2_BASE + 0x0010)
#define TC2_CC0             REGISTER_32(TC2_BASE + 0x0018)
#define TC2_CC1             REGISTER_32(TC2_BASE + 0x001c)

// TC3  only 32 bit mode is defined here.
#define TC3_CTRLA           REGISTER_16(TC3_BASE + 0x0000)
#define TC3_READREQ         REGISTER_16(TC3_BASE + 0x0002)
#define TC3_CTRLBCLR        REGISTER_8(TC3_BASE + 0x0004)
#define TC3_CTRLBSET        REGISTER_8(TC3_BASE + 0x0005)
#define TC3_CTRLC           REGISTER_8(TC3_BASE + 0x0006)
#define TC3_DBGCTRL         REGISTER_8(TC3_BASE + 0x0008)
#define TC3_EVCTRL          REGISTER_16(TC3_BASE + 0x000a)
#define TC3_INTCLR          REGISTER_8(TC3_BASE + 0x000c)
#define TC3_INTSET          REGISTER_8(TC3_BASE + 0x000d)
#define TC3_INTFLAG         REGISTER_8(TC3_BASE + 0x000e)
#define TC3_STATUS          REGISTER_8(TC3_BASE + 0x000f)
#define TC3_COUNT           REGISTER_32(TC3_BASE + 0x0010)
#define TC3_CC0             REGISTER_32(TC3_BASE + 0x0018)
#define TC3_CC1             REGISTER_32(TC3_BASE + 0x001c)

// TC4  only 32 bit mode is defined here.
#define TC4_CTRLA           REGISTER_16(TC4_BASE + 0x0000)
#define TC4_READREQ         REGISTER_16(TC4_BASE + 0x0002)
#define TC4_CTRLBCLR        REGISTER_8(TC4_BASE + 0x0004)
#define TC4_CTRLBSET        REGISTER_8(TC4_BASE + 0x0005)
#define TC4_CTRLC           REGISTER_8(TC4_BASE + 0x0006)
#define TC4_DBGCTRL         REGISTER_8(TC4_BASE + 0x0008)
#define TC4_EVCTRL          REGISTER_16(TC4_BASE + 0x000a)
#define TC4_INTCLR          REGISTER_8(TC4_BASE + 0x000c)
#define TC4_INTSET          REGISTER_8(TC4_BASE + 0x000d)
#define TC4_INTFLAG         REGISTER_8(TC4_BASE + 0x000e)
#define TC4_STATUS          REGISTER_8(TC4_BASE + 0x000f)
#define TC4_COUNT           REGISTER_32(TC4_BASE + 0x0010)
#define TC4_CC0             REGISTER_32(TC4_BASE + 0x0018)
#define TC4_CC1             REGISTER_32(TC4_BASE + 0x001c)

// TC5  only 32 bit mode is defined here.
#define TC5_CTRLA           REGISTER_16(TC5_BASE + 0x0000)
#define TC5_READREQ         REGISTER_16(TC5_BASE + 0x0002)
#define TC5_CTRLBCLR        REGISTER_8(TC5_BASE + 0x0004)
#define TC5_CTRLBSET        REGISTER_8(TC5_BASE + 0x0005)
#define TC5_CTRLC           REGISTER_8(TC5_BASE + 0x0006)
#define TC5_DBGCTRL         REGISTER_8(TC5_BASE + 0x0008)
#define TC5_EVCTRL          REGISTER_16(TC5_BASE + 0x000a)
#define TC5_INTCLR          REGISTER_8(TC5_BASE + 0x000c)
#define TC5_INTSET          REGISTER_8(TC5_BASE + 0x000d)
#define TC5_INTFLAG         REGISTER_8(TC5_BASE + 0x000e)
#define TC5_STATUS          REGISTER_8(TC5_BASE + 0x000f)
#define TC5_COUNT           REGISTER_32(TC5_BASE + 0x0010)
#define TC5_CC0             REGISTER_32(TC5_BASE + 0x0018)
#define TC5_CC1             REGISTER_32(TC5_BASE + 0x001c)

// TC6  only 32 bit mode is defined here.
#define TC6_CTRLA           REGISTER_16(TC6_BASE + 0x0000)
#define TC6_READREQ         REGISTER_16(TC6_BASE + 0x0002)
#define TC6_CTRLBCLR        REGISTER_8(TC6_BASE + 0x0004)
#define TC6_CTRLBSET        REGISTER_8(TC6_BASE + 0x0005)
#define TC6_CTRLC           REGISTER_8(TC6_BASE + 0x0006)
#define TC6_DBGCTRL         REGISTER_8(TC6_BASE + 0x0008)
#define TC6_EVCTRL          REGISTER_16(TC6_BASE + 0x000a)
#define TC6_INTCLR          REGISTER_8(TC6_BASE + 0x000c)
#define TC6_INTSET          REGISTER_8(TC6_BASE + 0x000d)
#define TC6_INTFLAG         REGISTER_8(TC6_BASE + 0x000e)
#define TC6_STATUS          REGISTER_8(TC6_BASE + 0x000f)
#define TC6_COUNT           REGISTER_32(TC6_BASE + 0x0010)
#define TC6_CC0             REGISTER_32(TC6_BASE + 0x0018)
#define TC6_CC1             REGISTER_32(TC6_BASE + 0x001c)

// TC7  only 32 bit mode is defined here.
#define TC7_CTRLA           REGISTER_16(TC7_BASE + 0x0000)
#define TC7_READREQ         REGISTER_16(TC7_BASE + 0x0002)
#define TC7_CTRLBCLR        REGISTER_8(TC7_BASE + 0x0004)
#define TC7_CTRLBSET        REGISTER_8(TC7_BASE + 0x0005)
#define TC7_CTRLC           REGISTER_8(TC7_BASE + 0x0006)
#define TC7_DBGCTRL         REGISTER_8(TC7_BASE + 0x0008)
#define TC7_EVCTRL          REGISTER_16(TC7_BASE + 0x000a)
#define TC7_INTCLR          REGISTER_8(TC7_BASE + 0x000c)
#define TC7_INTSET          REGISTER_8(TC7_BASE + 0x000d)
#define TC7_INTFLAG         REGISTER_8(TC7_BASE + 0x000e)
#define TC7_STATUS          REGISTER_8(TC7_BASE + 0x000f)
#define TC7_COUNT           REGISTER_32(TC7_BASE + 0x0010)
#define TC7_CC0             REGISTER_32(TC7_BASE + 0x0018)
#define TC7_CC1             REGISTER_32(TC7_BASE + 0x001c)


// ADC       
#define ADC_CTRLA           REGISTER_8(ADC_BASE + 0x0000)
#define ADC_REFCTRL         REGISTER_8(ADC_BASE + 0x0001)
#define ADC_AVGCTRL         REGISTER_8(ADC_BASE + 0x0002)
#define ADC_SAMPCTRL        REGISTER_8(ADC_BASE + 0x0003)
#define ADC_CTRLB           REGISTER_16(ADC_BASE + 0x0004)
#define ADC_WINCTRL         REGISTER_8(ADC_BASE + 0x0008)
#define ADC_SWTRIG          REGISTER_8(ADC_BASE + 0x000c)
#define ADC_INPUTCTRL       REGISTER_32(ADC_BASE + 0x0010)
#define ADC_EVCTRL          REGISTER_8(ADC_BASE + 0x0014)
#define ADC_INTENCLR        REGISTER_8(ADC_BASE + 0x0016)
#define ADC_INTENSET        REGISTER_8(ADC_BASE + 0x0017)
#define ADC_INTFLAG         REGISTER_8(ADC_BASE + 0x0018)
#define ADC_STATUS          REGISTER_8(ADC_BASE + 0x0019)
#define ADC_RESULT          REGISTER_16(ADC_BASE + 0x001a)
#define ADC_WINLT           REGISTER_16(ADC_BASE + 0x001c)
#define ADC_WINUT           REGISTER_16(ADC_BASE + 0x0020)
#define ADC_GAINCORR        REGISTER_16(ADC_BASE + 0x0024)
#define ADC_OFFSETCORR      REGISTER_16(ADC_BASE + 0x0026)
#define ADC_CALIB           REGISTER_8(ADC_BASE + 0x0028)

// AC  : analogue comparators
#define AC_CTRLA            REGISTER_8(AC_BASE + 0x0000)
#define AC_CTRLB            REGISTER_8(AC_BASE + 0x0001)
#define AC_EVCTRL           REGISTER_16(AC_BASE + 0x0002)
#define AC_INTENCLR         REGISTER_8(AC_BASE + 0x0004)
#define AC_INTENSET         REGISTER_8(AC_BASE + 0x0005)
#define AC_INTFLAG          REGISTER_8(AC_BASE + 0x0006)
#define AC_STATUSA          REGISTER_8(AC_BASE + 0x0008)
#define AC_STATUSB          REGISTER_8(AC_BASE + 0x0009)
#define AC_STATUSC          REGISTER_8(AC_BASE + 0x000a)
#define AC_WINCTRL          REGISTER_8(AC_BASE + 0x000c)
#define AC_COMPCTRL0        REGISTER_32(AC_BASE + 0x0010)
#define AC_COMPCTRL1        REGISTER_32(AC_BASE + 0x0014)
#define AC_SCALER0          REGISTER_8(AC_BASE + 0x0020)
#define AC_SCALER1          REGISTER_8(AC_BASE + 0x0021)
// DAC   
#define DAC_CTRLA           REGISTER_8(DAC_BASE + 0x0000)
#define DAC_CTRLB           REGISTER_8(DAC_BASE + 0x0001)
#define DAC_EVCTRL          REGISTER_8(DAC_BASE + 0x0002)
#define DAC_INTENCLR        REGISTER_8(DAC_BASE + 0x0004)
#define DAC_INTENSET        REGISTER_8(DAC_BASE + 0x0005)
#define DAC_INTENFLAG       REGISTER_8(DAC_BASE + 0x0006)
#define DAC_STATUS          REGISTER_8(DAC_BASE + 0x0007)
#define DAC_DATA            REGISTER_16(DAC_BASE + 0x0008)
#define DAC_DATABUF         REGISTER_16(DAC_BASE + 0x000c)

// PTC       THIS PERIPHERAL IS NOT DESCRIBED IN THE DATASHEET - BINARY BLOB NEEDED :(

// Core peripherals
#define STK_BASE	0xe000e010
#define SCB_BASE	0xe000ed00
#define NVIC_BASE 	0xe000e100


// NVIC
#define NVIC_ISER		REGISTER_32(NVIC_BASE + 0)
#define NVIC_ICER		REGISTER_32(NVIC_BASE + 0x80)
#define NVIC_ISPR		REGISTER_32(NVIC_BASE + 0x100)
#define NVIC_ICPR		REGISTER_32(NVIC_BASE + 0x180)
#define NVIC_IPR0		REGISTER_32(NVIC_BASE + 0x300)
#define NVIC_IPR1		REGISTER_32(NVIC_BASE + 0x304)
#define NVIC_IPR2		REGISTER_32(NVIC_BASE + 0x308)
#define NVIC_IPR3		REGISTER_32(NVIC_BASE + 0x30c)
#define NVIC_IPR4		REGISTER_32(NVIC_BASE + 0x310)
#define NVIC_IPR5		REGISTER_32(NVIC_BASE + 0x314)
#define NVIC_IPR6		REGISTER_32(NVIC_BASE + 0x318)
#define NVIC_IPR7		REGISTER_32(NVIC_BASE + 0x31c)

// STK
#define SYST_CSR	REGISTER_32(STK_BASE + 0x00)
#define SYST_RVR	REGISTER_32(STK_BASE + 0x04)
#define SYST_CVR	REGISTER_32(STK_BASE + 0x08)
#define SYST_CALIB	REGISTER_32(STK_BASE + 0x0c)

// SCB_BASE
#define CPUID		REGISTER_32(SCB_BASE + 0)
#define ICSR		REGISTER_32(SCB_BASE + 4)
#define VTOR        REGISTER_32(SCB_BASE + 8)
#define AIRCR		REGISTER_32(SCB_BASE + 0x0c)
#define SCR			REGISTER_32(SCB_BASE + 0x10)
#define CCR			REGISTER_32(SCB_BASE + 0x14)
#define SHPR2		REGISTER_32(SCB_BASE + 0x1c)
#define SHPR3		REGISTER_32(SCB_BASE + 0x20)
