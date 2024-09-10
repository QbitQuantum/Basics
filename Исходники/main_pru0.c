void main(void) {
    /* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	while(!(__R31&(1<<3))) {
		__R30 ^= 1<<5;
		__delay_cycles(TIME);
		// __R30 &= ~(1<<5);
		// __delay_cycles(TIME);
	}
	__delay_cycles(TIME);	// Give some time for press to release
	// Call assembly language
 	start(TIME);
	__halt();
}