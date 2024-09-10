/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit (void)
{
#if CORTEX_VECTORS_RAM
    // Then assume need to map vectors to RAM
    LPC_SYSCON->SYSMEMREMAP = ((LPC_SYSCON->SYSMEMREMAP)& ~3) | 1;
#else
    //	LPC_SYSCON->SYSMEMREMAP |= 3; // Map to flash
#endif

#if (CLOCK_SETUP)                                 /* Clock Setup              */
#if (SYSCLK_SETUP)                                /* System Clock Setup       */
#if (SYSOSC_SETUP)                                /* System Oscillator Setup  */
    uint32_t i;

    LPC_SYSCON->PDRUNCFG     &= ~(1 << 5);          /* Power-up System Osc      */
    LPC_SYSCON->SYSOSCCTRL    = SYSOSCCTRL_Val;
    for (i = 0; i < 200; i++) __NOP();
    LPC_SYSCON->SYSPLLCLKSEL  = SYSPLLCLKSEL_Val;   /* Select PLL Input         */
    LPC_SYSCON->SYSPLLCLKUEN  = 0x01;               /* Update Clock Source      */
    LPC_SYSCON->SYSPLLCLKUEN  = 0x00;               /* Toggle Update Register   */
    LPC_SYSCON->SYSPLLCLKUEN  = 0x01;
    while (!(LPC_SYSCON->SYSPLLCLKUEN & 0x01));     /* Wait Until Updated       */
#if (SYSPLL_SETUP)                                /* System PLL Setup         */
    LPC_SYSCON->SYSPLLCTRL    = SYSPLLCTRL_Val;
    LPC_SYSCON->PDRUNCFG     &= ~(1 << 7);          /* Power-up SYSPLL          */
    while (!(LPC_SYSCON->SYSPLLSTAT & 0x01));	      /* Wait Until PLL Locked    */
#endif
#endif
#if (WDTOSC_SETUP)                                /* Watchdog Oscillator Setup*/
    LPC_SYSCON->WDTOSCCTRL    = WDTOSCCTRL_Val;
    LPC_SYSCON->PDRUNCFG     &= ~(1 << 6);          /* Power-up WDT Clock       */
#endif
    LPC_SYSCON->MAINCLKSEL    = MAINCLKSEL_Val;     /* Select PLL Clock Output  */
    LPC_SYSCON->MAINCLKUEN    = 0x01;               /* Update MCLK Clock Source */
    LPC_SYSCON->MAINCLKUEN    = 0x00;               /* Toggle Update Register   */
    LPC_SYSCON->MAINCLKUEN    = 0x01;
    while (!(LPC_SYSCON->MAINCLKUEN & 0x01));       /* Wait Until Updated       */
#endif

    LPC_SYSCON->SYSAHBCLKDIV  = SYSAHBCLKDIV_Val;
    LPC_SYSCON->SYSAHBCLKCTRL = AHBCLKCTRL_Val;
    LPC_SYSCON->SSP0CLKDIV    = SSP0CLKDIV_Val;
    LPC_SYSCON->UARTCLKDIV    = UARTCLKDIV_Val;
    LPC_SYSCON->SSP1CLKDIV    = SSP1CLKDIV_Val;
#endif

#if __SYSTEM_CLOCK < 20000000
    FLASHCFG = 0;
#elif __SYSTEM_CLOCK < 40000000
    FLASHCFG = 1;
#else
    FLASHCFG = 2;
#endif

#if (MEMMAP_SETUP || MEMMAP_INIT)       /* Memory Mapping Setup               */
    LPC_SYSCON->SYSMEMREMAP = SYSMEMREMAP_Val;
#endif
    //SystemCoreClockUpdate();
}