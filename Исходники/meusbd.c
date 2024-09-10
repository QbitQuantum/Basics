//----- (000025B8) --------------------------------------------------------
__myevic__ uint32_t hidGetInfoCmd( CMD_T *pCmd )
{
	uint32_t u32StartAddr;
	uint32_t u32ParamLen;

	u32StartAddr = pCmd->u32Arg1;
	u32ParamLen = pCmd->u32Arg2;

	myprintf( "Get Info command - Start Addr: %d    Param Len: %d\n", pCmd->u32Arg1, pCmd->u32Arg2 );

	if ( u32ParamLen )
	{
		dfChecksum = Checksum( (uint8_t *)DataFlash.params, FMC_FLASH_PAGE_SIZE - 4 );

		if ( u32StartAddr + u32ParamLen > FMC_FLASH_PAGE_SIZE )
		{
			u32ParamLen = FMC_FLASH_PAGE_SIZE - u32StartAddr;
		}

		MemCpy( hidData, ((uint8_t *)&DataFlash) + u32StartAddr, u32ParamLen );

		hidInDataPtr = hidData;
		hidStartInReport( u32ParamLen );
	}

	return 0;
}