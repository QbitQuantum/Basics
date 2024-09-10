void main(){
	/* Configure GPI and GPO as Mode 0 (Direct Connect) */
	CT_CFG.GPCFG0 = 0x0000;

	/* Clear GPO pins */
	__R30 &= 0xFFFF0000;

	/* Spin in loop until interrupt on HOST 1 is detected */
	while(1){
		if (__R31 & HOST1_MASK){
			TOGGLE_BLUE;
			/* Clear interrupt event */
			CT_INTC.SICR = 16; /*TODO: Clear event 16*/;
			/* Delay to ensure the event is cleared in INTC */
			__delay_cycles(5);
		}
	}

	/* Halt the PRU core - shouldn't get here */
	__halt();
}