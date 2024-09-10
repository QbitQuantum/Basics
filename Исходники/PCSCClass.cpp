bool CPCSCClass::Transmit(CString cstrApdu)
{
	unsigned char sendbuff[270];
	unsigned char recvbuff[270];
	int apdulen = 0;
	DWORD recvlen = 2;
	CConvertData cvrtObj;
	memset(sendbuff,0,270);
	memset(recvbuff,0,270);

	cvrtObj.HexStringToByteArray(cstrApdu,NULL,&apdulen);
	cvrtObj.HexStringToByteArray(cstrApdu,sendbuff,&apdulen);
	
	mylog.AddToLogs(0,m_logobj,"send:",sendbuff,apdulen,true);

	if(apdulen < 5)
	{
		mylog.AddToLogs(m_logobj,"error: command too short");
	}

	if(apdulen == 5) recvlen = 2 + sendbuff[4];

	RetCode = SCardTransmit(
					hCard,
					&IO_REQ,
					sendbuff,
					apdulen,
					NULL,  //   IN OUT LPSCARD_IO_REQUEST pioRecvPci,
					recvbuff,
					&recvlen);
	
	if (RetCode != SCARD_S_SUCCESS)
	{	
		mylog.AddToLogs(m_logobj,"error: SCardTransmit failed");
		mylog.AddToLogs(m_logobj,TranslatePCSCError());
		return false;
	}
	
	mylog.AddToLogs(m_logobj,"SCardTransmit Success");

	mylog.AddToLogs(0,m_logobj,"recv:",recvbuff,recvlen,true);

	return true;
}