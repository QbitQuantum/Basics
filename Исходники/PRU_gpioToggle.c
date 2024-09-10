void main(){
	volatile uint32_t gpio;

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	/* Toggle GPO pins TODO: Figure out which to use */
	gpio = 0x000F;

	/* TODO: Create stop condition, else it will toggle indefinitely */
	while(1){
		__R30 ^= gpio;
		__delay_cycles(100000000);
	}

	/* Halt the PRU core */
	__halt();
}