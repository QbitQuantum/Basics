static void USER_FUNC lum_sendStudyWaveData(ORIGIN_WAVE_DATA* pWaveInfo)
{
	static U8 g_sendCount = 0;
	U8 index;
	U16 clkCount;
	BOOL gpioHighLevel;


	//lum_disableAllIrq();
	if(pWaveInfo->firstHighlevel != 0)
	{
		GpioSetRegOneBit(GPIO_C_OUT, 0x04);
		lum_delay15us(300);
	}
	for(index=0; index<pWaveInfo->waveCount; index++)
	{
		gpioHighLevel = ((index%2) == pWaveInfo->firstHighlevel)?TRUE:FALSE;
		for(clkCount = 0; clkCount<pWaveInfo->waveData[index]; clkCount++) //only for clk timing
		{
			if(gpioHighLevel)
			{
				GpioSetRegOneBit(GPIO_C_OUT, 0x04);
			}
			else
			{
				GpioClrRegOneBit(GPIO_C_OUT, 0x04);
			}
			lum_delay15us(1);
			__nop(); // 1
			__nop(); // 2
			__nop(); // 3
			__nop(); // 4
			__nop(); // 5
			__nop(); // 6
			__nop(); // 7
			__nop(); // 8
			__nop(); // 9

		}
	}

	//lum_enableAllIrq();
	hfgpio_fset_out_low(HFGPIO_F_SDO_2);

	g_sendCount++;
	if(g_sendCount < MAX_WAVE_RESEND_COUNT)
	{
		lum_start433StudyTimer(MAX_SEND_WAVE_TIME_DELAY);
	}
	else
	{
		g_sendCount = 0;
		lum_setRfMode(RF_SLEEP);
		g_searchFreqData.chipStatus = SX1208_IDLE;
	}
}