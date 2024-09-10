void main(){
	uint32_t *pDdr = (uint32_t *) &CT_DDR;
	uint32_t score;

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	/* Wait until receipt of interrupt on host 0 */
	while((__R31 & 0x40000000) == 0){
	}

	/* Clear system event in SECR1 */
	CT_INTC.SECR1 = 0x1;

	/* Clear system event enable in ECR1 */
	CT_INTC.ECR1 = 0x1;

	/* Point C30 (L3) to 0x3000 offset and C31 (DDR) to 0x0 offset */
	PRU0_CTRL.CTPPR1 = 0x00003000;

	/* Load value from DDR, decrement, and store it in L3 */
	score = pDdr[0];
	score--;
	CT_L3 = score;

	/* Halt PRU core */
	__halt();
}