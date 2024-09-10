DSTATUS disk_initialize(void)
{
	u8 n, cmd, ty, ocr[4], rep, timeout;
	u16 tmr;

	power_on();							/* Force socket power on */

	for (n = 10; n; n--) xmit_spi(0xFF);	/* Dummy clocks */

	ty = 0;
	timeout=100;

    // Trying to enter Idle state
	do {
		DESELECT();
		xmit_spi(0xFF);
		SELECT();
		rep = send_cmd(CMD0,0);
	} while ((rep != 1) && (--timeout));

    if(timeout == 0)
    {
		DESELECT();
		xmit_spi(0xFF);
		SELECT();
		rep = send_cmd(CMD12,0);
		rep = send_cmd(CMD0,0);
		if (rep != 1)
        {
            return STA_NOINIT;
        }
	}

	rep = send_cmd(CMD8, 0x1AA);

    // SDHC
	if ( rep == 1)
    {
		for (n = 0; n < 4; n++) ocr[n] = rcvr_spi();		/* Get trailing return value of R7 resp */

		if (ocr[2] == 0x01 && ocr[3] == 0xAA) {				/* The card can work at vdd range of 2.7-3.6V */
			for (tmr = 25000; tmr && send_cmd(ACMD41, 1UL << 30); tmr--) ;	/* Wait for leaving idle state (ACMD41 with HCS bit) */

			if (tmr && send_cmd(CMD58, 0) == 0) {		/* Check CCS bit in the OCR */
				for (n = 0; n < 4; n++) ocr[n] = rcvr_spi();
				ty = (ocr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;	/* SDv2 */
			}
		}

	}

    // SDSC or MMC
    else
    {
		if (send_cmd(ACMD41, 0) <= 1) 	{
			ty = CT_SD1; cmd = ACMD41;	/* SDv1 */
		} else {
			ty = CT_MMC; cmd = CMD1;	/* MMCv3 */
		}

		for (tmr = 25000; tmr && send_cmd(cmd, 0); tmr--) ;	/* Wait for leaving idle state */

		if (!tmr || send_cmd(CMD16, 512) != 0)			/* Set R/W block length to 512 */
			ty = 0;

	}

	CardType = ty;
	release_spi();

    // Initialization succeded
	if (ty)
    {
		FCLK_FAST();
		return RES_OK;
	}

    // Initialization failed
    else
    {
		power_off();
		return STA_NOINIT;
	}
}