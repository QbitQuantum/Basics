DWORD WINAPI NetmailOutThread(LPVOID param)
{
	SQLHDBC   hdbc;
	SQLHSTMT  hstmt;
	SQLRETURN sqlret;
	SQLLEN cb;
	HANDLE hHeap;

	FTNAddr LastAddr;
	HANDLE hPktFile;
	wchar_t tmpFileName[MAX_PATH], finalPktFileName[MAX_PATH],FileboxDirName[MAX_PATH];
	wchar_t LogStr[255];
	unsigned int PktNumber;
	char PktPwd[9];

	NetmailOutQueue NDOQ;



	int WaitTime;
	int result; 

	HANDLE hEvent[2];
	
	InterlockedIncrement(&(cfg.ThreadCount));

	WaitTime=INFINITE;


	hEvent[0]=cfg.hExitEvent;
	hEvent[1]=cfg.hNetmailOutEvent;
	AddLogEntry(L"Netmail out thread started");

loop:
	result=WaitForMultipleObjects(2,hEvent,FALSE,WaitTime);
	if (result==WAIT_TIMEOUT)
	{
		SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
		SQLDisconnect(hdbc);
		SQLFreeHandle(SQL_HANDLE_DBC,hdbc);
		WaitTime=INFINITE;
		HeapDestroy(hHeap);
		goto loop;

	}
	if (WaitTime==INFINITE)
	{
		hHeap=HeapCreate(HEAP_NO_SERIALIZE,16384,0);
		SQLAllocHandle(SQL_HANDLE_DBC, cfg.henv, &hdbc); 
		sqlret=SQLDriverConnectW(hdbc, NULL, cfg.ConnectionString, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
		if (sqlret != SQL_SUCCESS && sqlret != SQL_SUCCESS_WITH_INFO)
		{		
			SetEvent(cfg.hExitEvent);
			goto threadexit;
			//fatal error
		}
		SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
		
		WaitTime=10000;
	}

	switch(result)
	{
	case (WAIT_OBJECT_0):
		{
			goto threadexit;
		}
	case (WAIT_OBJECT_0+1):
		{
			
			NDOQ.First=NULL;
			NDOQ.Last=NULL;
			
			EnterCriticalSection(&NetmailRouteCritSect);
			SQLExecDirectW(hstmt, L"execute sp_DirectNetmail", SQL_NTS); // обработать директный нетмейл для использующих FTN Service линков
			LeaveCriticalSection(&NetmailRouteCritSect);

			sqlret=SQLExecDirectW(hstmt,L"select MessageID,FromZone,FromNet,FromNode,FromPoint,ToZone,ToNet,ToNode,ToPoint,CreateTime,FromName,ToName,Subject,MsgId,ReplyTo,MsgText,KillSent,Pvt,FileAttach,Arq,RRq,ReturnReq,Direct,Cfm,recv from Netmail where direct=1 and sent=0 and Locked=0 order by ToZone,ToNet,ToNode,MessageID",SQL_NTS);
			if ((sqlret==SQL_SUCCESS)||(sqlret==SQL_SUCCESS_WITH_INFO))
			{
				GetNetmailMessages(hstmt,hHeap,&NDOQ);
			}	
			
			sqlret=SQLExecDirectW(hstmt,L"select MessageID,FromZone,FromNet,FromNode,FromPoint,ToZone,ToNet,ToNode,ToPoint,CreateTime,FromName,ToName,Subject,MsgId,ReplyTo,MsgText,KillSent,Pvt,FileAttach,Arq,RRq,ReturnReq,Direct,Cfm,recv from Netmail,MyAka where direct=0 and sent=0 and Locked=0 and MyAka.Point=0 and Netmail.ToPoint<>0 and Netmail.ToZone=MyAka.Zone and Netmail.ToNet=MyAka.Net and Netmail.ToNode=MyAka.Node order by ToPoint,MessageID",SQL_NTS);
			if ((sqlret==SQL_SUCCESS)||(sqlret==SQL_SUCCESS_WITH_INFO))
			{
				GetNetmailMessages(hstmt, hHeap, &NDOQ);
			}	
			
			sqlret = SQLExecDirectW(hstmt, L"select MessageID,FromZone,FromNet,FromNode,FromPoint,ToZone,ToNet,ToNode,ToPoint,CreateTime,FromName,ToName,Subject,MsgId,ReplyTo,MsgText,KillSent,Pvt,FileAttach,Arq,RRq,ReturnReq,Direct,Cfm,recv from Netmail,Links where direct=0 and sent=0 and Locked=0 and Netmail.ToZone=Links.Zone and Netmail.ToNet=Links.Net and Netmail.ToNode=Links.Node and Links.NetmailDirect<>0 and Links.LinkType=2 order by Links.LinkID,MessageID", SQL_NTS);
			if ((sqlret == SQL_SUCCESS) || (sqlret == SQL_SUCCESS_WITH_INFO))
			{
				GetNetmailMessages(hstmt, hHeap, &NDOQ);
			}

			
			LastAddr.FullAddr=0;
			hPktFile=INVALID_HANDLE_VALUE;
			
			while (NDOQ.First!=NULL)
			{
				lpNetmailMessage lpTmp;
				wsprintfW(LogStr,L"Direct netmail From %u:%u/%u.%u To %u:%u/%u.%u",NDOQ.First->FromAddr.zone,NDOQ.First->FromAddr.net,NDOQ.First->FromAddr.node,NDOQ.First->FromAddr.point,NDOQ.First->ToAddr.zone,NDOQ.First->ToAddr.net,NDOQ.First->ToAddr.node,NDOQ.First->ToAddr.point);
				AddLogEntry(LogStr);
				
				if (LastAddr.FullAddr!=NDOQ.First->ToAddr.FullAddr)
				{
					if(LastAddr.FullAddr!=0)
					{
						ClosePktFile(hPktFile);
						CreateDirectoryW(FileboxDirName,NULL);
						MoveFileExW(tmpFileName,finalPktFileName,MOVEFILE_COPY_ALLOWED);
						
					}
					LastAddr.FullAddr=NDOQ.First->ToAddr.FullAddr;
					//create file
					PktNumber=GetPktNumber(hstmt);
					wsprintfW(FileboxDirName, L"%s\\%u.%u.%u.%u", cfg.FileboxesDir, NDOQ.First->ToAddr.zone, NDOQ.First->ToAddr.net, NDOQ.First->ToAddr.node, NDOQ.First->ToAddr.point);
					wsprintfW(tmpFileName, L"%s\\%08X.NETMAIL", cfg.TmpOutboundDir, PktNumber);
					wsprintfW(finalPktFileName,L"%s\\%08X.PKT",FileboxDirName,PktNumber);
					hPktFile=CreateFileW(tmpFileName,GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_NEW,0,NULL);
					
					
					
					memset(PktPwd, 0, 9);
					SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_USHORT, SQL_SMALLINT, 0, 0, &(NDOQ.First->ToAddr.zone), 0, NULL);
					SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_USHORT, SQL_SMALLINT, 0, 0, &(NDOQ.First->ToAddr.net), 0, NULL);
					SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_USHORT, SQL_SMALLINT, 0, 0, &(NDOQ.First->ToAddr.node), 0, NULL);
					SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_USHORT, SQL_SMALLINT, 0, 0, &(NDOQ.First->ToAddr.point), 0, NULL);
					sqlret = SQLExecDirectW(hstmt, L"Select PktPassword from Links where Zone=? and Net=? and Node=? and Point=?", SQL_NTS);
					if ((sqlret == SQL_SUCCESS) || (sqlret == SQL_SUCCESS_WITH_INFO))
					{
						sqlret = SQLFetch(hstmt);
						if ((sqlret == SQL_SUCCESS) || (sqlret == SQL_SUCCESS_WITH_INFO))
						{
							SQLGetData(hstmt, 1, SQL_C_CHAR, PktPwd, 9, &cb);
						}
					}
					SQLCloseCursor(hstmt);
					SQLFreeStmt(hstmt, SQL_RESET_PARAMS);



					WritePktHeader(hPktFile,&(cfg.MyAddr),&(NDOQ.First->ToAddr),PktPwd); 
					
				}
				//
				WriteNetmailMessage(hPktFile,hHeap,NDOQ.First);
				//
				
				SQLBindParameter(hstmt,1,SQL_PARAM_INPUT,SQL_C_ULONG,SQL_INTEGER,0,0,&(NDOQ.First->MessageID),0,NULL);
				sqlret=SQLExecDirectW(hstmt,L"{call sp_NetmailMessageSent(?)}",SQL_NTS);
				SQLFreeStmt(hstmt,SQL_RESET_PARAMS);

				//
				lpTmp=NDOQ.First->NextMsg;
				HeapFree(hHeap,0,NDOQ.First->MsgText);
				if (NDOQ.First->ReplyTo!=NULL) HeapFree(hHeap,0,NDOQ.First->ReplyTo);
				if (NDOQ.First->MsgId!=NULL) HeapFree(hHeap,0,NDOQ.First->MsgId);
				HeapFree(hHeap,0,NDOQ.First->Subject);
				HeapFree(hHeap,0,NDOQ.First->ToName);
				HeapFree(hHeap,0,NDOQ.First->FromName);
				HeapFree(hHeap,0,NDOQ.First);
				NDOQ.First=lpTmp;
			}

			if (hPktFile!=INVALID_HANDLE_VALUE)
			{
				ClosePktFile(hPktFile);
				CreateDirectoryW(FileboxDirName,NULL);
				MoveFileExW(tmpFileName,finalPktFileName,MOVEFILE_COPY_ALLOWED);
			}

			
			//
			EnterCriticalSection(&NetmailRouteCritSect);
					
			SQLExecDirectW(hstmt, L"EXECUTE sp_RouteNetmail",SQL_NTS);
			
			LeaveCriticalSection(&NetmailRouteCritSect);
			
			SetEvent(cfg.hMailerCallGeneratingEvent);

			//make polls
			sqlret = SQLExecDirectW(hstmt, L"select Zone,Net,Node from Links,NetmailOutbound,Netmail where Links.LinkID=NetmailOutbound.ToLinkID and Netmail.MessageID=NetmailOutbound.MessageID and Netmail.Locked=0 and Links.DialOut<>0 and Links.LinkType<=2 and Links.Point=0", SQL_NTS);
			if ((sqlret == SQL_SUCCESS) || (sqlret == SQL_SUCCESS_WITH_INFO))
			{
				unsigned short zone, net, node;
				SQLBindCol(hstmt, 1, SQL_C_USHORT, &zone, 0, NULL);
				SQLBindCol(hstmt, 2, SQL_C_USHORT, &net, 0, NULL);
				SQLBindCol(hstmt, 3, SQL_C_USHORT, &node, 0, NULL);
				
				sqlret = SQLFetch(hstmt);
				while ((sqlret == SQL_SUCCESS) || (sqlret == SQL_SUCCESS_WITH_INFO))
				{
					if (zone == cfg.MyAddr.zone)
					{
						wsprintfW(LogStr,L"Creating poll to %u:%u/%u", zone, net, node);
						AddLogEntry(LogStr);
												
						swprintf_s(tmpFileName, MAX_PATH, L"%s\\%04hX%04hX.CLO", cfg.BinkOutboundDir, net, node);
						hPktFile = CreateFileW(tmpFileName, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
						CloseHandle(hPktFile);
						//
					}
					sqlret = SQLFetch(hstmt);
				}
				SQLCloseCursor(hstmt);
				SQLFreeStmt(hstmt, SQL_UNBIND);
			}

	
		}
	}
	goto loop;

threadexit:
	_InterlockedDecrement(&(cfg.ThreadCount));
	SetEvent(cfg.hThreadEndEvent);
	return 0;
}