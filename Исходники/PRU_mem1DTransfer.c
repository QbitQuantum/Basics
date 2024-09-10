void main(){
	mem1DParams params;
	uint8_t *srcPtr;
	uint8_t *dstPtr;
	uint8_t data;
	uint8_t srcBuf[SIZE];
	uint8_t dstBuf[SIZE];

	buffer.cnt = SIZE;
	buffer.src = &srcBuf;
	buffer.dst = &dstBuf;

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	/* Configure C24 (PRU0 DRAM) and C25 (PRU1 DRAM) offsets as 0x0 */
	PRU0_CTRL.CTBIR0 = 0;
	PRU0_CTRL.CTBIR1 = 0;

	/* Load the MEM1D parameters */
	params = buffer;

	/* Copy the source and destination addresses into pointers.
	 * This allows a copy of the entirety of the buffer */
	srcPtr = ((uint8_t*)(params.src));
	dstPtr = ((uint8_t*)(params.dst));

	/* Continue copying until the count is 0 */
	while (params.cnt != 0){
		/* Load data from source pointer in DRAM into data buffer */
		data = *srcPtr;

		/* Copy data from data buffer into destination pointer in L3 */
		*dstPtr = data;

		/* Decrease the count */
		params.cnt -= COPY_LENGTH;

		/* Update source and destination pointers */
		params.src += COPY_LENGTH;
		params.dst += COPY_LENGTH;

		/* Store current state back into DRAM */
		buffer = params;
	}

	/* Halt PRU core */
	__halt();
}