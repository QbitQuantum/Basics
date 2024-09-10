static void bios_reinitbyswitch(void) {

	UINT8	prxcrt;
	UINT8	prxdupd;
	UINT8	biosflag;
	UINT8	extmem;
	UINT8	boot;

	if (!(pccore.dipsw[2] & 0x80)) {
#if defined(CPUCORE_IA32)
		mem[MEMB_SYS_TYPE] = 0x03;		// 80386〜
#else
		mem[MEMB_SYS_TYPE] = 0x01;		// 80286
#endif
	}
	else {
		mem[MEMB_SYS_TYPE] = 0x00;		// V30
	}

	mem[MEMB_BIOS_FLAG0] = 0x01;
	prxcrt = 0x08;
	if (!(pccore.dipsw[0] & 0x01)) {			// dipsw1-1 on
		prxcrt |= 0x40;
	}
	if (gdc.display & (1 << GDCDISP_ANALOG)) {
		prxcrt |= 0x04;							// color16
	}
	if (!(pccore.dipsw[0] & 0x80)) {			// dipsw1-8 on
		prxcrt |= 0x01;
	}
	if (grcg.chip) {
		prxcrt |= 0x02;
	}
	mem[MEMB_PRXCRT] = prxcrt;

	prxdupd = 0x18;
	if (grcg.chip >= 3) {
		prxdupd |= 0x40;
	}
	if (!(pccore.dipsw[1] & 0x80)) {			// dipsw2-8 on
		prxdupd |= 0x20;
	}
	mem[MEMB_PRXDUPD] = prxdupd;

	biosflag = 0x20;
	if (pccore.cpumode & CPUMODE_8MHZ) {
		biosflag |= 0x80;
	}
	biosflag |= mem[0xa3fea] & 7;
	if (pccore.dipsw[2] & 0x80) {
		biosflag |= 0x40;
	}
	mem[MEMB_BIOS_FLAG1] = biosflag;
	extmem = pccore.extmem;
	extmem = min(extmem, 14);
	mem[MEMB_EXPMMSZ] = (UINT8)(extmem << 3);
	if (pccore.extmem >= 15) {
		mem[0x0594] = pccore.extmem - 15;
	}
	mem[MEMB_CRT_RASTER] = 0x0f;

	// FDD initialize
	SETBIOSMEM32(MEMD_F2DD_POINTER, 0xfd801ad7);
	SETBIOSMEM32(MEMD_F2HD_POINTER, 0xfd801aaf);
	boot = mem[MEMB_MSW5] & 0xf0;
	if (boot != 0x20) {		// 1MB
		fddbios_equip(3, TRUE);
		mem[MEMB_BIOS_FLAG0] |= 0x02;
	}
	else {					// 640KB
		fddbios_equip(0, TRUE);
		mem[MEMB_BIOS_FLAG0] &= ~0x02;
	}
	mem[MEMB_F2HD_MODE] = 0xff;
	mem[MEMB_F2DD_MODE] = 0xff;

#if defined(SUPPORT_CRT31KHZ)
	mem[MEMB_CRT_BIOS] |= 0x80;
#endif
#if defined(SUPPORT_PC9821)
	mem[MEMB_CRT_BIOS] |= 0x04;		// 05/02/03
	mem[0x45c] = 0x40;
#endif

	// FDC
	if (fdc.support144) {
		mem[MEMB_F144_SUP] |= fdc.equip;
	}

	// IDE initialize
	if (pccore.hddif & PCHDD_IDE) {
		mem[MEMB_SYS_TYPE] |= 0x80;		// IDE
		CPU_AX = 0x8300;
		sasibios_operate();
	}
}