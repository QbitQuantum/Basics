unsigned _stdcall VideoExcelReportPipeInstanceProc(void *arg)
{
	try
	{
		int i=0;
		DWORD dwResult   = 0;
		DWORD Pipe = 0;
		BOOL  bReadEvent = FALSE;

		OVERLAPPED Ovlap;
		const DWORD dwEventNum = 3;
		DWORD BytesTransferred = 0;
		HANDLE Event[dwEventNum];

		char  strReadBuf[VIDOE_EXCEL_REPORT_PIPE_MAX_BUF];
		memset(strReadBuf,0,sizeof(strReadBuf));

		Event[0] = g_hVideoExcelReportPipeRead;
		Event[1] = g_hVideoExcelReportPipeWrite;
		Event[2] = g_hVideoExcelReportPipeExit;

		// 创建命名管道
		if ((g_hVideoExcelReportPipeHandle = CreateNamedPipe(VIDEO_EXCEL_REPORT_PIPE_NAME,
			PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
			PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, 1,
			VIDOE_EXCEL_REPORT_PIPE_MAX_BUF, VIDOE_EXCEL_REPORT_PIPE_MAX_BUF, 1000, NULL)) == INVALID_HANDLE_VALUE)
		{
			TRACE("创建视频巡视报表管道%d失败,错误码:%d\n", i, GetLastError());
			return 1;
		}

		memset(&Ovlap,0,sizeof(Ovlap));
		Ovlap.hEvent = Event[0];

		// Listen for client connections using ConnectNamedPipe()
		if (ConnectNamedPipe(g_hVideoExcelReportPipeHandle, &Ovlap) == 0)
		{
			if (GetLastError() != ERROR_IO_PENDING)
			{
				TRACE("ConnectNamedPipe for pipe %d failed with error %d\n", i, GetLastError());

				CloseHandle(g_hVideoExcelReportPipeHandle);
				g_hVideoExcelReportPipeHandle = NULL;

				CloseHandle(g_hVideoExcelReportPipeRead);
				g_hVideoExcelReportPipeRead = NULL;

				CloseHandle(g_hVideoExcelReportPipeWrite);
				g_hVideoExcelReportPipeWrite = NULL;

				CloseHandle(g_hVideoExcelReportPipeExit);
				g_hVideoExcelReportPipeExit = NULL;

				return 3;
			}
		}

		TRACE("Server is now running\n");

		// Read and echo data back to Named Pipe clients forever
		while(true) 
		{
			dwResult = WaitForMultipleObjects(dwEventNum, Event, FALSE, INFINITE);
			if (dwResult == WAIT_FAILED)
			{
				TRACE("WaitForMultipleObjects failed with error %d\n",GetLastError());
				g_bVideoExcelReportPipeConnected = false;

				CloseHandle(g_hVideoExcelReportPipeHandle);
				g_hVideoExcelReportPipeHandle = NULL;

				CloseHandle(g_hVideoExcelReportPipeRead);
				g_hVideoExcelReportPipeRead = NULL;

				CloseHandle(g_hVideoExcelReportPipeWrite);
				g_hVideoExcelReportPipeWrite = NULL;

				CloseHandle(g_hVideoExcelReportPipeExit);
				g_hVideoExcelReportPipeExit = NULL;

				return 4;
			}

			if (dwResult == WAIT_OBJECT_0)//读
			{
				TRACE("\nReceived data or connection request!");
				bReadEvent = FALSE;
			}
			else if (dwResult == WAIT_OBJECT_0 + 1)//写
			{
				TRACE("\nWrite data!");
			}
			else //WAIT_OBJECT_2:application exit - close handle  default:error
			{
				break;
			}

			//重置事件
			ResetEvent(Event[dwResult-WAIT_OBJECT_0]);

			// Check overlapped results, and if they fail, reestablish 
			// communication for a new client; otherwise, process read 
			// and write operations with the client
			if (GetOverlappedResult(g_hVideoExcelReportPipeHandle, &Ovlap,&BytesTransferred, TRUE) == 0)
			{
				g_bVideoExcelReportPipeConnected = false;

				TRACE("GetOverlapped result failed %d start over\n", GetLastError());

				if (DisconnectNamedPipe(g_hVideoExcelReportPipeHandle) == 0)
				{
					TRACE("DisconnectNamedPipe failed with error %d\n",GetLastError());
					break;
				}

				if (ConnectNamedPipe(g_hVideoExcelReportPipeHandle,&Ovlap) == 0)
				{
					if (GetLastError() != ERROR_IO_PENDING)
					{
						// Severe error on pipe. Close this handle forever.
						TRACE("ConnectNamedPipe for pipe %d failed with error %d\n", i, GetLastError());
						break;
					}
				}
			} 
			else
			{
				g_bVideoExcelReportPipeConnected = true;

				if (!bReadEvent)//读
				{
					//收到连接请求或者客户端数据，重新设置阻塞
					TRACE("Received %d bytes, echo bytes back\n",BytesTransferred);

					if (ReadFile(g_hVideoExcelReportPipeHandle, strReadBuf,VIDOE_EXCEL_REPORT_PIPE_MAX_BUF, NULL, &Ovlap) == 0)
					{
						if (GetLastError() != ERROR_IO_PENDING)
						{
							TRACE("\nReadFile failed with error %d", GetLastError());
						}
					}
				}
				bReadEvent = TRUE;
			}
		}		

		g_bVideoExcelReportPipeConnected = false;

		if (g_hVideoExcelReportPipeHandle != NULL)
		{
			CloseHandle(g_hVideoExcelReportPipeHandle);
			g_hVideoExcelReportPipeHandle = NULL;
		}

		if (g_hVideoExcelReportPipeRead != NULL)
		{
			CloseHandle(g_hVideoExcelReportPipeRead);
			g_hVideoExcelReportPipeRead = NULL;
		}

		if (g_hVideoExcelReportPipeWrite != NULL)
		{
			CloseHandle(g_hVideoExcelReportPipeWrite);
			g_hVideoExcelReportPipeWrite = NULL;
		}

		return 10;
	}
	catch(...)
	{

	}
	return 11;
}