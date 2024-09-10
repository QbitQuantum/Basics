int misc_init_r (void)
{
	/* adjust flash start and size as well as the offset */
	gd->bd->bi_flashstart = 0 - flash_info[0].size;
	gd->bd->bi_flashoffset= flash_info[0].size - CONFIG_SYS_MONITOR_LEN;
#if 0
	volatile unsigned short *fpga_mode =
		(unsigned short *)((ulong)CONFIG_SYS_FPGA_BASE_ADDR + CONFIG_SYS_FPGA_CTRL);
	volatile unsigned char *duart0_mcr =
		(unsigned char *)((ulong)DUART0_BA + 4);
	volatile unsigned char *duart1_mcr =
		(unsigned char *)((ulong)DUART1_BA + 4);

	bd_t *bd = gd->bd;
	char *	tmp;                    /* Temporary char pointer      */
	unsigned char *dst;
	ulong len = sizeof(fpgadata);
	int status;
	int index;
	int i;
	unsigned long CPC0_CR0Reg;

	dst = malloc(CONFIG_SYS_FPGA_MAX_SIZE);
	if (gunzip (dst, CONFIG_SYS_FPGA_MAX_SIZE, (uchar *)fpgadata, &len) != 0) {
		printf ("GUNZIP ERROR - must RESET board to recover\n");
		do_reset (NULL, 0, 0, NULL);
	}

	status = fpga_boot(dst, len);
	if (status != 0) {
		printf("\nFPGA: Booting failed ");
		switch (status) {
		case ERROR_FPGA_PRG_INIT_LOW:
			printf("(Timeout: INIT not low after asserting PROGRAM*)\n ");
			break;
		case ERROR_FPGA_PRG_INIT_HIGH:
			printf("(Timeout: INIT not high after deasserting PROGRAM*)\n ");
			break;
		case ERROR_FPGA_PRG_DONE:
			printf("(Timeout: DONE not high after programming FPGA)\n ");
			break;
		}

		/* display infos on fpgaimage */
		index = 15;
		for (i=0; i<4; i++) {
			len = dst[index];
			printf("FPGA: %s\n", &(dst[index+1]));
			index += len+3;
		}
		putc ('\n');
		/* delayed reboot */
		for (i=20; i>0; i--) {
			printf("Rebooting in %2d seconds \r",i);
			for (index=0;index<1000;index++)
				udelay(1000);
		}
		putc ('\n');
		do_reset(NULL, 0, 0, NULL);
	}

	puts("FPGA:  ");

	/* display infos on fpgaimage */
	index = 15;
	for (i=0; i<4; i++) {
		len = dst[index];
		printf("%s ", &(dst[index+1]));
		index += len+3;
	}
	putc ('\n');

	free(dst);

	/*
	 * Reset FPGA via FPGA_DATA pin
	 */
	SET_FPGA(FPGA_PRG | FPGA_CLK);
	udelay(1000); /* wait 1ms */
	SET_FPGA(FPGA_PRG | FPGA_CLK | FPGA_DATA);
	udelay(1000); /* wait 1ms */
#endif

#if 0
	/*
	 * Enable power on PS/2 interface
	 */
	*fpga_mode |= CONFIG_SYS_FPGA_CTRL_PS2_RESET;

	/*
	 * Enable interrupts in exar duart mcr[3]
	 */
	*duart0_mcr = 0x08;
	*duart1_mcr = 0x08;
#endif
	return (0);
}