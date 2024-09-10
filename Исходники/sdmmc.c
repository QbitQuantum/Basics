//---------------------------------------------------------------------------------
int sdmmc_sdcard_init() {
//---------------------------------------------------------------------------------
	u16 sdaddr;
	u32 resp0;
	u32 resp1;
	u32 resp2;
	u32 resp3;
	u32 resp4;
	u32 resp5;
	u32 resp6;
	u32 resp7;

	u32 ocr, ccs, hcs, response;

	sdmmc_cardready = 0;

	int oldIME = enterCriticalSection();

	sdmmc_write16(REG_SDCLKCTL, 0x20);
	sdmmc_write16(REG_SDOPT, 0x40EA); // XXX: document me!
	sdmmc_write16(0x02, 0x400);

	sdmmc_mask16(REG_SDCLKCTL, 0, 0x100);
	sdmmc_write16(REG_SDCLKCTL, sdmmc_read16(REG_SDCLKCTL));
	sdmmc_mask16(REG_SDCLKCTL, 0x100, 0);
	sdmmc_mask16(REG_SDCLKCTL, 0, 0x200);
	sdmmc_mask16(REG_SDCLKCTL, 0, 0x100);

	// CMD0
	sdmmc_send_command(0x0000, 0x0000, 0x0000);
	sdmmc_send_command(0x0408, 0x01aa, 0x0000);
	sdmmc_gotcmd8reply = 1;

	if(sdmmc_timeout)
		sdmmc_gotcmd8reply = 0;

	if(sdmmc_gotcmd8reply)
		hcs = (1<<30);
	else
		hcs = 0;

	ocr = 0x00ff8000;

	while (1) {
		sdmmc_send_acmd41(ocr | hcs, &response);

		if (response & 0x80000000)
			break;
	}

	ccs = response & (1<<30);

	if(ccs && hcs) 
		sdmmc_sdhc = 1;
	else
		sdmmc_sdhc = 0;

	// CMD2 - get CID
	sdmmc_send_command(2, 0, 0);
	
	resp0 = sdmmc_read16(REG_SDRESP0);
	resp1 = sdmmc_read16(REG_SDRESP1);
	resp2 = sdmmc_read16(REG_SDRESP2);
	resp3 = sdmmc_read16(REG_SDRESP3);
	resp4 = sdmmc_read16(REG_SDRESP4);
	resp5 = sdmmc_read16(REG_SDRESP5);
	resp6 = sdmmc_read16(REG_SDRESP6);
	resp7 = sdmmc_read16(REG_SDRESP7);

	sdmmc_cid[0] = resp0 | (u32)(resp1<<16);
	sdmmc_cid[1] = resp2 | (u32)(resp3<<16);
	sdmmc_cid[2] = resp4 | (u32)(resp5<<16);
	sdmmc_cid[3] = resp6 | (u32)(resp7<<16);

	// CMD3
	sdmmc_send_command(3, 0, 0);
	
	resp0 = sdmmc_read16(REG_SDRESP0);
	resp1 = sdmmc_read16(REG_SDRESP1);
	
	sdaddr = resp1;
	
	// CMD9 - get CSD
	sdmmc_send_command(9, 0, sdaddr);
	
	resp0 = sdmmc_read16(REG_SDRESP0);
	resp1 = sdmmc_read16(REG_SDRESP1);
	resp2 = sdmmc_read16(REG_SDRESP2);
	resp3 = sdmmc_read16(REG_SDRESP3);
	resp4 = sdmmc_read16(REG_SDRESP4);
	resp5 = sdmmc_read16(REG_SDRESP5);
	resp6 = sdmmc_read16(REG_SDRESP6);
	resp7 = sdmmc_read16(REG_SDRESP7);
	
	sdmmc_write16(REG_SDCLKCTL, 0x100);	
	
	// CMD7
	sdmmc_send_command(7, 0, sdaddr);
	
	resp0 = sdmmc_read16(REG_SDRESP0);
	resp1 = sdmmc_read16(REG_SDRESP1);
	
	// CMD55
	sdmmc_send_command(55, 0, sdaddr);
	
	// ACMD6
	sdmmc_send_command(6, 2, 0);
	
	resp0 = sdmmc_read16(REG_SDRESP0);
	resp1 = sdmmc_read16(REG_SDRESP1);

	sdmmc_send_command(13, 0, sdaddr);
	
	resp0 = sdmmc_read16(REG_SDRESP0);
	resp1 = sdmmc_read16(REG_SDRESP1);

	sdmmc_send_command(16, 0x200, 0x0);
	
	resp0 = sdmmc_read16(REG_SDRESP0);
	resp1 = sdmmc_read16(REG_SDRESP1);	
	
	sdmmc_write16(REG_SDCLKCTL, sdmmc_read16(REG_SDCLKCTL));
	sdmmc_write16(REG_SDBLKLEN, 0x200);

	sdmmc_mask16(REG_SDCLKCTL, 0x100, 0);

	sdmmc_cardready = 1;
	leaveCriticalSection(oldIME);

	return 0;
}