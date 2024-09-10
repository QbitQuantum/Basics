unsigned short isobase3(HANDLE devNo,unsigned char *svAPDU,short svAPDULen,unsigned char *srResp,short *srRespLen, short ivCardSet)
{
	BYTE  ResponseBuffer[2000];
	DWORD ResponseLength ;

	WORD retval = CER_PCSC_SCardTransmit_Data_LOST;


//	IO_Request.dwProtocol = SCARD_PROTOCOL_T1;
	IO_Request.dwProtocol = ActiveProtocol;
	IO_Request.cbPciLength = (DWORD) sizeof(SCARD_IO_REQUEST);

	
	ResponseLength=2000;

	ret = SCardTransmit((SCARDHANDLE)devNo, &IO_Request, svAPDU, svAPDULen, 0, (BYTE *)&ResponseBuffer, &ResponseLength);
	if (ret != SCARD_S_SUCCESS)
	{
		DebugMessage(ret);
		return CER_PCSC_SCardTransmit;
	}


	if ( ResponseLength >= 2 )
	{
		retval = ((BYTE)ResponseBuffer[ResponseLength-2]) * 256 + (BYTE)ResponseBuffer[ResponseLength-1] ;

		//if rf
		if(retval==0x9000)
		{
			*srRespLen = (short)ResponseLength - 2;
			memcpy(srResp,ResponseBuffer,ResponseLength-2);
		}
	}
	else
	{
		DebugMessage(1);
		retval =  CER_PCSC_SCardTransmit_Data_LOST;
	}

	return retval ;

}