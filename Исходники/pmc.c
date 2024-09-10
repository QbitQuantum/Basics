/**
 * \brief Enable Wait Mode. Enter condition: (WAITMODE bit = 1) + FLPM
 *
 * \note In this function, FLPM will retain, WAITMODE bit will be set, 
 * Generally, this function will be called by pmc_sleep() in order to 
 * complete all sequence entering wait mode.
 * See \ref pmc_sleep() for entering different sleep modes.
 */
void pmc_enable_waitmode(void)
{
	uint32_t i;

	/* Flash in wait mode */
	i = PMC->PMC_FSMR;
	i &= ~PMC_FSMR_FLPM_Msk;
	i |= ul_flash_in_wait_mode;
	PMC->PMC_FSMR = i;

	/* Set the WAITMODE bit = 1 */
	PMC->CKGR_MOR |= CKGR_MOR_KEY_PASSWD | CKGR_MOR_WAITMODE;

	/* Waiting for Master Clock Ready MCKRDY = 1 */
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY));

	/* Waiting for MOSCRCEN bit cleared is strongly recommended
	 * to ensure that the core will not execute undesired instructions
	 */
	for (i = 0; i < 500; i++) {
		__NOP();
	}
	while (!(PMC->CKGR_MOR & CKGR_MOR_MOSCRCEN));

#if (!SAMG)
	/* Restore Flash in idle mode */
	i = PMC->PMC_FSMR;
	i &= ~PMC_FSMR_FLPM_Msk;
	i |= PMC_WAIT_MODE_FLASH_IDLE;
	PMC->PMC_FSMR = i;
#endif
}