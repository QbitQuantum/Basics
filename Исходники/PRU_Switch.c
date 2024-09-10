void main()
{
	/* Configure GPI and GPO as Mode 0 (Direct Connect) */
    CT_CFG.GPCFG0 = 0x0000;
	
    /* Turn on all LEDs */
	__R30 = (LED_Group1 | LED_Group2);

	/* TODO: Create stop condition, else it will toggle indefinitely */
	while(1)
	{

		/* Both Switch 1 & 2 are pressed */
		if( (__R31 & SW1_2) == 0)
			__R30 = (LED_Group1 | LED_Group2);

		/* Switch 1 is pressed */
		else if( (__R31 & SW1) != SW1)
			__R30 = LED_Group1;// & ~LED_Group2;

		/* Switch 2 is pressed */
		else if( (__R31 & SW2) != SW2)
			__R30 = LED_Group2;// & ~(LED_Group2);

		/* Neither Switch 1/2 are pressed */
		else
			__R30 = ~(LED_Group1 | LED_Group2);

	}
	
	/* Halt the PRU core - shouldn't get here */
	__halt();
}