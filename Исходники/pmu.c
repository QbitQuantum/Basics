void
WAKEUP_IRQHandlerPIO0_8 (void)
{
	if (LPC_SYSCON->MAINCLKSEL != MAINCLKSEL_SYSPLL_OUT)
	{
		/* switch to IRC oscillator */
		LPC_SYSCON->MAINCLKSEL = MAINCLKSEL_SYSPLL_OUT;
		/* push clock change */
		LPC_SYSCON->MAINCLKUEN = 0;
		LPC_SYSCON->MAINCLKUEN = 1;
		/* wait for clock change to be finished */
		while (!(LPC_SYSCON->MAINCLKUEN & 1));
		/* power down watchdog oscillator */
		LPC_SYSCON->PDRUNCFG |= WDTOSC_PD;
	}

	/* re-trigger match output */
	LPC_TMR16B0->EMR &= ~1;
	/* reset wakeup logic */
	LPC_SYSCON->STARTRSRP0CLR = STARTxPRP0_PIO0_8;
	/* disable deep sleep */
	SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;

	/* enable previous clock settings  */
	LPC_SYSCON->SYSAHBCLKCTRL = g_sysahbclkctrl;
	/* select MISO function for PIO0_8 */
	LPC_IOCON->PIO0_8 = 1;

	/* vodoo -NOP */
	__NOP ();
}