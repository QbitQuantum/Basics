int main(){
	uint32_t *ddrPtr = (uint32_t *)&CT_DDR;
	uint32_t result;

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	/* Ensure C31 is pointed to the start of DDR (0 offset) */
	PRU0_CTRL.CTPPR1_bit.C31_BLK_POINTER = 0;

	/* Read value from DDR, store in the PRU_CFG pin_mx register */
	result = *ddrPtr;
	CT_CFG.PIN_MX = result;

	/* Halt PRU core */
	__halt();
}