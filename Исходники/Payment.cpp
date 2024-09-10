int CPayment::SendPaymentData(LPCTSTR sfxm,LONG Money,LPCTSTR bz)
{
	bool bIsStand = true;

	szPayState = "3";//请求正在处理

	//组包
	CIso8583Package *package = new CIso8583Package();
	if (package == NULL) 
	{
		szPayState = "E7";
		return -1;   //不成功，返回错误码
	}
	char c48Field[255];
	memset(c48Field,0,sizeof(c48Field));

	if( strcmp(sfxm,"3001") == 0)
	{
		bIsStand = false;
		const char *split = "|"; 
		char *pTemp = new char[128];
		strcpy(pTemp,bz);
		char *pToken = strtok (pTemp,split); 
		if( pToken == NULL ) return -1;
		int nOffset = strlen(pToken);
		memcpy(c48Field,pToken,strlen(pToken));
		pToken = strtok(NULL,"|");
		if( pToken == NULL ) return -1;
		memcpy(c48Field + nOffset,pToken,strlen(pToken));
		nOffset += strlen(pToken);
		pToken = strtok(NULL,"|");
		if( pToken == NULL ) return -1;
		memcpy(c48Field + nOffset,pToken,strlen(pToken));
		nOffset += strlen(pToken);
		pToken = strtok(NULL,"|");
		if( pToken == NULL ) return -1;
		memcpy(c48Field + nOffset,pToken,strlen(pToken));
		nOffset += strlen(pToken);

		package->SetFieldData(48,nOffset,(BYTE *)c48Field);//48域，目前随便填写，银联无法处理该业务

	}
	else
	{//处理其他收费项目
		int nOffset = 0;
		nOffset = strlen(sfxm);
		memcpy(c48Field,sfxm,nOffset);
		memcpy(c48Field + nOffset,bz,strlen(bz));
		nOffset += strlen(bz);
		package->SetFieldData(48,nOffset,(BYTE *)c48Field);//48域，目前随便填写，银联无法处理该业务
	}

	int iRes = BuildPackage(package,Money);
	if (iRes != 0) 
	{
		szPayState = "E7";
		return iRes;   //组包不成功，返回错误码
	}

	BYTE cHeader[30];
	int nOffset = 0;
	AscToBcd(cHeader + nOffset,(unsigned char *)szTPDU.GetBuffer(),szTPDU.GetLength());
	nOffset += szTPDU.GetLength() / 2;
	AscToBcd(cHeader + nOffset,(unsigned char *)szHeader.GetBuffer(),szHeader.GetLength());
	nOffset += szHeader.GetLength() / 2;
	cHeader[nOffset] = 0x02;
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

	TCHAR szCurPath[MAX_PATH];
	GetCurrentDirectory(sizeof(szCurPath),szCurPath);
	_tcscat(szCurPath,TEXT("\\Reversal.ini"));

	CSocket client;
	if( client.InitSocket() == FALSE)
	{
		szPayState = "E7";
		return -1;
	}
	if( client.Connect(szServerIP,atoi(szPort)) == false)
	{
		szPayState = "E7";
		return -1;
	}
	gLog.Log(cPackageData,nLen + 2);
	client.Send(cPackageData,nLen + 2);
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

		LONG lProCode = atol(szTraceCode.GetBuffer()) + 1;
		unsigned char cAsciiBuff[12];
		memset(cAsciiBuff,0,sizeof(cAsciiBuff));
		BinToAsc(cAsciiBuff,lProCode,6);
		WritePrivateProfileString(TEXT("TraceCode"),TEXT("TraceCode"),(char *)cAsciiBuff,szCurPath);
		if(strcmp(cResult,"A0") == 0) //根据银联网络的说法，MAC错误也需要冲正
		{
			WritePrivateProfileString(TEXT("Reversal"),TEXT("Ack"),"A0",szCurPath);
			WritePrivateProfileString(TEXT("Reversal"),TEXT("Flag"),"0",szCurPath);//0 -- 未处理
			CReversalTransaction transaction;
			transaction.SendReversalTransactionData();//冲正处理
		}
		else if( strcmp(cResult,"05") == 0)
		{//认证失败
			szPayState = "E2";
			return -1;
		}
		else if( strcmp(cResult,"51") == 0)
		{
			szPayState = "E5";
			return -1;
		}
		else if( strcmp(cResult, "55") == 0)
		{
			szPayState = "E2";
			return -1;
		}
		else if( strcmp(cResult, "75") == 0)
		{
			szPayState = "E1";
			return -1;
		}
		szPayState = "1";//交易成功
	}
	else
	{//网络原因，消费冲正
		szPayState = "E6";
		WritePrivateProfileString(TEXT("Reversal"),TEXT("Ack"),"98",szCurPath);//POS终端在时限内未能收到POS中心的应答消息而引发
		WritePrivateProfileString(TEXT("Reversal"),TEXT("Flag"),"0",szCurPath);//0 -- 未处理
		CReversalTransaction transaction;
		transaction.SendReversalTransactionData();//冲正处理
	}

	return 1;//交易成功
}