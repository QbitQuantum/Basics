void InitHostCore(BYTE fPowerUpBoot)
{
	if(fPowerUpBoot) {
		//check port 1.5. if high, it is a skip(NoInit) mode.
		SysNoInitMode = SYS_MODE_NORMAL;
#ifdef MODEL_TW8836FPGA
		if(1)	
#else
		if(PORT_NOINIT_MODE == 1)	
#endif
		{
			SysNoInitMode = SYS_MODE_NOINIT;
			//turn on the SKIP_MODE.
			access = 0;
					
			McuSpiClkSelect(MCUSPI_CLK_27M);
			return;
		}
	}

	Puts("\nInitHostCore");	
	//----- Set SPI mode
	SpiFlashVendor = SPIHost_QUADInit();
	SPIHost_SetReadModeByRegister(SPI_READ_MODE);		// Match DMA READ mode with SPI-read

	//----- Enable Chip Interrupt

	WriteHostPage(PAGE0_GENERAL );
	WriteHost(REG002, 0xFF );	// Clear Pending Interrupts
	WriteHost(REG003, 0xFE );	// enable SW. disable all other interrupts

	//enable remocon interrupt.
	EnableRemoInt();
}