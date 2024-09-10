/**********************************************************************************************
10  PCSC_ApduT0
卡命令处理函数,该命令接收APDU Case2 Case3格式的指令。

HD_ApduT0( HANDLE hReader,  unsigned char *apduData, short srAPDULen, unsigned char *respData, short *respDataLen)

参数说明
hReader				由PCSC_OpenReader返回的设备句柄
apduData			APDU命令(字节串)用CLA、INS、P1、P2以及一个可变长度的条件体来表示，条件体的定义为Lc、Data（Lc个字节）和Le。
					根据Lc和Le值的不同，共有四种命令情况，如下表所示：
					情况	结构
					1	CLA INS P1 P2
					2	CLA INS P1 P2 Le
					3	CLA INS P1 P2 Lc Data
					4	CLA INS P1 P2 Lc Data Le
srAPDULen			存放发送的APDU数据的长度
respData			卡响应数据
respDataLen			卡响应数据的长度


返回值

当操作Case1和 Case2时，respData无意义。当操作Case3和 Case4时，函数返回0x9000，respData有意义；其余响应，respData无意义。
***********************************************************************************************/
LONG isobase2(HANDLE hReader, unsigned char *apduData, int svAPDULen, unsigned char *srResp, int *srRespLen)
{
	BYTE  ResponseBuffer[MAX_RESPDATA_LENGTH];
	DWORD ResponseLength = 1024;

	WORD retval = 0;

	*srRespLen = 0 ;
	*srResp = '\0' ;

	IO_Request.dwProtocol = ActiveProtocol;
	IO_Request.cbPciLength = (DWORD) sizeof(SCARD_IO_REQUEST);


	ResponseLength=2000;

	ret = SCardTransmit((SCARDHANDLE)hReader, &IO_Request, apduData, svAPDULen, 0, (BYTE *)&ResponseBuffer, &ResponseLength);
	if (ret != SCARD_S_SUCCESS)
	{
		return ret;
	}

	if ( ResponseLength >= 2 )
	{

		retval = ((BYTE)ResponseBuffer[ResponseLength-2]) * 256 + (BYTE)ResponseBuffer[ResponseLength-1] ;

		*srRespLen = (short)ResponseLength - 2;
		memcpy(srResp,ResponseBuffer,ResponseLength-2);

	}else{
		return ret;
	}

	return EXCUTE_SUC ;
}