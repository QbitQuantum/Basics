int CReversalTransaction::SendReversalTransactionData(char *pAccount,LONG Money,char *cTraceCode,char *cAck)
{
	//组包
	CIso8583Package *package = new CIso8583Package();
	int iRes = BuildPackage(package,pAccount,Money,cTraceCode,cAck);
	if (iRes != 0) return iRes;   //组包不成功，返回错误码

	BYTE cHeader[30];
	int nOffset = 0;
	AscToBcd(cHeader + nOffset,(unsigned char *)szTPDU.GetBuffer(),szTPDU.GetLength());
	nOffset += szTPDU.GetLength() / 2;
	AscToBcd(cHeader + nOffset,(unsigned char *)szHeader.GetBuffer(),szHeader.GetLength());
	nOffset += szHeader.GetLength() / 2;
	cHeader[nOffset] = 0x04;
	nOffset += 1;
	cHeader[nOffset] = 0x00;
	nOffset += 1;

	BYTE cData[512];
	memset(cData,0,512);
	unsigned int nLen = package->GetData(cData,512,cHeader,nOffset,false);
	delete package;

	char cLen[5] = {'\0'};
	itoa_hex(nLen,cLen,2);
	unsigned char cDataLen[3] = {'\0'};
	AscToBcd(cDataLen,(unsigned char *)cLen,4);
	BYTE cPackageData[512];
	memset(cPackageData,0,sizeof(cPackageData));
	memcpy(cPackageData,cDataLen,2);
	memcpy(cPackageData + 2,cData,nLen);

	CSocket client;
	if( client.InitSocket() == FALSE) return -1;
	if( client.Connect(szServerIP,atoi(szPort)) == false) return -1;
	gLog.Log(cData,nLen);
	client.Send(cData,nLen);
	BYTE RecvData[1024];
	memset(RecvData,0,1024);
	nLen = client.Receive(RecvData,1024);
	if(nLen != 0)
	{
		gLog.Log(RecvData,nLen);
		CIso8583Parse *receivePackage = new CIso8583Parse();
		char cResult[128];
		memset(cResult,0,128);
		Read8583Package(receivePackage,RecvData,39,2,(BYTE *)cResult);
		delete receivePackage;
		if(strcmp(cResult,"00") == 0)
		{
			TCHAR szCurPath[MAX_PATH];
			GetCurrentDirectory(sizeof(szCurPath),szCurPath);
			_tcscat(szCurPath,TEXT("\\Reversal.ini"));
			WritePrivateProfileString(TEXT("Reversal"),TEXT("Account"),"",szCurPath);
			WritePrivateProfileString(TEXT("Reversal"),TEXT("TraceCode"),"",szCurPath);
			WritePrivateProfileString(TEXT("Reversal"),TEXT("Money"),"",szCurPath);
			WritePrivateProfileString(TEXT("Reversal"),TEXT("Ack"),"",szCurPath);
			WritePrivateProfileString(TEXT("Reversal"),TEXT("Flag"),"1",szCurPath);//1 -- 已处理
		}
	}

	return 1;
}