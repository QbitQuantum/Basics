int sdc_init(void) {
	
	int i;
	uint8 n, ty = 0, ocr[4];
	
    if(initted)
        return 0;
	
	if(spi_init(0)) {
		return -1;
	}
	
	timer_spin_sleep(20);
	SELECT();
	
	/* 80 dummy clocks */
	for (n = 10; n; n--) 
		(void)spi_slow_sr_byte(0xff);

	
	if (send_slow_cmd(CMD0, 0) == 1) {			/* Enter Idle state */

#ifdef SD_DEBUG
		dbglog(DBG_DEBUG, "%s: Enter Idle state\n", __func__);
#endif
		timer_spin_sleep(20);
//		thd_sleep(100);
		
		i = 0;
		
		if (send_slow_cmd(CMD8, 0x1AA) == 1) {	/* SDC Ver2+  */
		
			for (n = 0; n < 4; n++) 
				ocr[n] = spi_slow_sr_byte(0xff);
			
			if (ocr[2] == 0x01 && ocr[3] == 0xAA) { /* The card can work at vdd range of 2.7-3.6V */
			
				do {
					
					/* ACMD41 with HCS bit */
					if (send_slow_cmd(CMD55, 0) <= 1 && send_slow_cmd(CMD41, 1UL << 30) == 0) 
						break;
						
					++i;
					
				} while (i < 300000);
				
				if (i < 300000 && send_slow_cmd(CMD58, 0) == 0) { /* Check CCS bit */
				
					for (n = 0; n < 4; n++) 
						ocr[n] = spi_slow_sr_byte(0xff);
						
					ty = (ocr[0] & 0x40) ? 6 : 2;
				}
			}
			
		} else { /* SDC Ver1 or MMC */
		
			ty = (send_slow_cmd(CMD55, 0) <= 1 && send_slow_cmd(CMD41, 0) <= 1) ? 2 : 1; /* SDC : MMC */
			
			do {
				
				if (ty == 2) {
					
					if (send_slow_cmd(CMD55, 0) <= 1 && send_slow_cmd(CMD41, 0) == 0) /* ACMD41 */
						break;
						
				} else {
					
					if (send_slow_cmd(CMD1, 0) == 0) { /* CMD1 */
						is_mmc = 1;
						break;
					}								
				}
				
				++i;
				
			} while (i < 300000);
			
			if (!(i < 300000) || send_slow_cmd(CMD16, 512) != 0)	/* Select R/W block length */
				ty = 0;
		}
	}
	
	send_slow_cmd(CMD59, 1);		// crc check
	
#ifdef SD_DEBUG
	dbglog(DBG_DEBUG, "%s: card type = 0x%02x\n", __func__, ty & 0xff);
#endif

	if(!(ty & 4)) {
		byte_mode = 1;
	}
	
	DESELECT();
	(void)spi_slow_sr_byte(0xff); /* Idle (Release DO) */

	if (ty) { /* Initialization succeded */
//		sdc_print_ident();
		initted = 1;
		return 0;
	}
	
	/* Initialization failed */
	sdc_shutdown();
	return -1;
}