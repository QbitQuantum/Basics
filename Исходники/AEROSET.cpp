DWORD WINAPI CommMonitor( LPSTR lpData)
{
    //监控串口接收数据，并完成数据格式分析，将结果放入结果队列
	int		nItemCount,SampleIDLen,nDataOff,nResultLen,iSampleID;
	bool	bLogFile;
	char    TempWorkingID[7];
	LPSTR   lpPointer;
	//应答包
	char * p_Ack="\x2\x6\x3";
	char * p_Nak="\x2\x16\x3";
	char * p_IntSessionTXT="\x2I\x20\x3";
	char * p_ReleaseMaster="\x2M\x20\x20\x20\x20\x20\x3";
	char  PackageType;
	char SampleID[10];
	SYSTEMTIME SystemTime;
	CommData
    //通信类型1'、1''、2、3、4、5
	
	Init()
	ResetOpPointer()				

	FillDevName()					
	SetCommWaitMask(EV_RXFLAG)
	PurgeComm( hComm, PURGE_RXCLEAR );	
	memset(lpOpPointer , 0, c_RxBufferLength );
	if(NewLogFile("AEROSET.txt"))
	{
		bLogFile=TRUE;
	}

	while (TRUE)
	{


		WaitEvent(EV_RXFLAG)//等待接受数据包
		GetInQueueLength(dwReadLength)//分析数据
		ReadCommBlock(dwReadLength)
		PackageType=*(lpOpPointer+1);//数据包的类型
		if(bLogFile)
		{
			WriteLogData(hLogFile,lpOpPointer,dwReadLength);
		}
		//校验接收到的数据，若正确，则处理，否则给否定应答。
		/*
			checksum  calculation
		*/

		/*结果的数据块中可能包含病人信息、ID信息、结果数据等组。*/
		PackageType=*(lpOpPointer+1);
		switch(PackageType)
		{
		case 'Q':
			WriteCommBlock(p_Ack,3)//肯定应答
			//WriteCommChar(ACK)
			break;

		case 'R':
			//结果处理
			WriteCommBlock(p_Ack,3)//肯定应答
			iSampleID=StrToInt(lpOpPointer+c_SampleIDOff,c_SamlpeIDLen);
			itoa(iSampleID,&SampleID[0],10);
			SampleIDLen=strlen(SampleID);
			TempWorkingID[0]=lpDevice->DevItemType;
			if(SampleIDLen>=6)
			{
				strncpy(&TempWorkingID[1],&SampleID[SampleIDLen-5],5);
			}
			else
				strncpy(&TempWorkingID[6-SampleIDLen],SampleID,SampleIDLen);
			TempWorkingID[6]='\0';
			GetLocalTime(&SystemTime);
			nItemCount=0;
			for(nDataOff =c_DataOff; *(lpOpPointer+nDataOff)!=ETB ;)
			{
				strncpy(OutResult[nItemCount].WorkingID,TempWorkingID,7);
				OutResult[nItemCount].ItemNo=nItemCount+1;
				lpPointer=lpOpPointer+nDataOff;
				DeleSpace(4)
				strncpy(OutResult[nItemCount].ItemID,lpPointer,nResultLen);
				OutResult[nItemCount].ItemID[nResultLen]='\0';
				lpPointer=lpOpPointer+nDataOff+c_ResultOff;
				DeleSpace(c_ResultLen )
				FillResult(nItemCount, lpPointer ,nResultLen ) 
				FillDate(nItemCount, SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay, SystemTime.wHour,SystemTime.wMinute,SystemTime.wSecond)
				nDataOff = nDataOff + c_OneDataLen;
				nItemCount++;
			}
			if(nItemCount>0)
			{
				(*lpResultProcessRoutine)(lpDevice->nDevNO, OutResult, nItemCount);
				lpDevice->dwRecordCount+=nItemCount;
			}
		
			//WriteCommChar(ACK)
		///	WriteCommBlock(p_Ack,3)//肯定应答
			break;
		case ACK:
		case NAK:
			break;
       
		}
	

		ResetRxPointer()		
	

	}
	if(bLogFile)
	{
		CloseLogFile(hLogFile);
	}
	return TRUE;
} // end of CommWatchProc()