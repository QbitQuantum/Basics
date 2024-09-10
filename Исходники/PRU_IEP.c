void main(){
	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	/* Disable counter */
	CT_IEP.TMR_GLB_CFG_bit.CNT_ENABLE = 0;

	/* Reset Count register */
	CT_IEP.TMR_CNT = 0x0;

	/* Clear overflow status register */
	CT_IEP.TMR_GLB_STS_bit.CNT_OVF = 0x1;

	/* Set compare value */
	CT_IEP.TMR_CMP0 = 0x77359400; // 10 seconds @ 200MHz

	/* Clear compare status */
	CT_IEP.TMR_CMP_STS_bit.CMP_HIT = 0xFF;

	/* Disable compensation */
	CT_IEP.TMR_COMPEN_bit.COMPEN_CNT = 0x0;

	/* Enable CMP0 and reset on event */
	CT_IEP.TMR_CMP_CFG_bit.CMP0_RST_CNT_EN = 0x1;
	CT_IEP.TMR_CMP_CFG_bit.CMP_EN = 0x1;

	/* Clear the status of all interrupts */
	CT_INTC.SECR0 = 0xFFFFFFFF;
	CT_INTC.SECR1 = 0xFFFFFFFF;

	/* Enable counter */
	CT_IEP.TMR_GLB_CFG = 0x11;

	/* Poll until R31.31 is set */
	do{
		while((__R31 & 0x80000000) == 0){
		}
	/* Verify that the IEP is the source of the interrupt */
	} while ((CT_INTC.SECR0 & (1 << 7)) == 0);

	/* Disable counter */
	CT_IEP.TMR_GLB_CFG_bit.CNT_ENABLE = 0x0;

	/* Disable Compare0 */
	CT_IEP.TMR_CMP_CFG = 0x0;

	/* Clear Compare status */
	CT_IEP.TMR_CMP_STS = 0xFF;

	/* Clear the status of the interrupt */
	CT_INTC.SECR0 = (1 << 7);

	/* Halt the PRU core */
	__halt();
}