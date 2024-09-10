void main()
{
	
	uint32_t gpio;

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	gpio = 0x000F;

	__R30 = 0x0;

	/* Toggle the LEDs */
	/* TODO: Create stop condition, else it will toggle indefinitely */
	while(1)
	{
		__R30 ^= gpio;

		__delay_cycles(100000000);

	}
	
	/* Halt the PRU core - shouldn't get here */
	__halt();

}