DWORD WINAPI PBThreadProc(LPVOID lpParameter)
{
	ShowWindow(hProgressBarWnd,SW_SHOW);
	PBRANGE range;

	SendMessage(hProgressBarWnd, PBM_SETRANGE, (WPARAM)0, (LPARAM)(MAKELPARAM(0, 100)));   //设置进度条的范围
	SendMessage(hProgressBarWnd, PBM_GETRANGE,    //获取进度条的范围
		(WPARAM)TRUE,          //TRUE 表示返回值为范围的最小值,FALSE表示返回最大值
		(LPARAM)&range);

	DWORD dwFlags;
	//int lastError;
	if(!InternetGetConnectedState(&dwFlags, 0))//wininet.h
	{
		MessageBox(hWnd, _T("没有网络连接！"), _T("提示"), MB_OK);
		//lastError = GetLastError();
		return 0;
	}

	TCHAR strAgent[64] = {0};
	_stprintf_s(strAgent, _T("Agent %ld"), timeGetTime());//mmsystem.h,winmm.lib
	HINTERNET hopen;
	if(!(dwFlags & INTERNET_CONNECTION_PROXY))
	{
		hopen = InternetOpen(strAgent, INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY, NULL, NULL, 0);
	}
	else
	{
		hopen = InternetOpen(strAgent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	}

	if(!hopen)
	{
		MessageBox(hWnd, _T("打不开网络连接！"), _T("提示"), MB_OK);
		return 0;
	}

	FILE *fp = NULL;
	TCHAR szUrlAdd[MAX_PATH] = {0}; 
	GetWindowText(hFileAddrWnd, szUrlAdd, MAX_PATH );

	//TCHAR pBuf[MAX_PATH] = {0};                            //存放路径的变量
	//GetCurrentDirectory(MAX_PATH, pBuf);                   //获取程序的当前目录
	//_tcscat_s(pBuf, _tcsrchr(szUrlAdd, '/'));

	TCHAR szFilePath[MAX_PATH] = {0};
	GetDlgItemText(hWnd,IDC_FILE_SAVEPATH,szFilePath,MAX_PATH);
	if(!_tcscmp(szFilePath,_T("")))
	{
		MessageBox(hWnd,_T("请设置保存路径后再下载"),_T("提示"),MB_OK);
		EnableWindow(hFileAddrWnd,TRUE);
		EnableWindow(hStopBtnWnd,FALSE);
		EnableWindow(hBrowserBtnWnd,TRUE);
		return 0;
	}

	_tfopen_s(&fp,szFilePath, _T("ab+"));
	if(fp == NULL)
	{
		MessageBox(hWnd, _T("打开本地文件失败！"), _T("提示"), MB_OK);
		EnableWindow(hFileAddrWnd,TRUE);
		return 0;
	}

	int fileSize = 0;
	TCHAR *pszHead = NULL;
	TCHAR szHead[256] = {0};

	if (bPaused)
	{
		bPaused = FALSE;
		fseek(fp, 0, SEEK_END);
		fileSize = ftell(fp);
		_stprintf_s(szHead, _T("Range: bytes=%d-\r\nAccept: */*\r\n\r\n"), fileSize);
		pszHead = szHead;
	}
	else
	{
		pszHead = _T("Accept: */*\r\n\r\n");
	}

	void *szTemp[16384] = {0};
	HINTERNET hConnect;
	if(!(hConnect = InternetOpenUrl(hopen, szUrlAdd, szHead, wcslen(szHead), INTERNET_FLAG_DONT_CACHE|INTERNET_FLAG_PRAGMA_NOCACHE, 0)))
	{
		fclose(fp);
		MessageBox(hWnd, _T("打开网络地址失败！"), _T("提示"), MB_OK);
		EnableWindow(hFileAddrWnd,TRUE);
		return 0;
	}

	DWORD dwByteToRead = 0, dwSizeOfRq = 4, dwBytes = 0, dwSize = 0, sum = fileSize;
	if(!HttpQueryInfo(hConnect, HTTP_QUERY_CONTENT_LENGTH|HTTP_QUERY_FLAG_NUMBER, (LPVOID)&dwByteToRead, &dwSizeOfRq, NULL))
	{
		dwByteToRead = 0;
	}

	EnableWindow(hDownLoadBtnWnd, FALSE);
	EnableWindow(hPauseBtnWnd, TRUE);
	SetDlgItemText(hWnd, IDC_BTN_DOWNLOAD, _T("正在下载..."));
	TCHAR sumData[64] = {0};

	do
	{
		if(!InternetReadFile(hConnect, szTemp, 16384, &dwSize))
		{
			InternetCloseHandle(hopen);
			fclose(fp);
			MessageBox(hWnd, _T("网络中断！"), _T("提示"), MB_OK);
			EnableWindow(hFileAddrWnd,TRUE);
			return 0;
		}

		if(dwSize == 0)
		{
			break;
		}
		else
		{
			sum += dwSize;
			fwrite(szTemp, dwSize, 1, fp);
			double percentValue = (sum * 100.0) / (dwByteToRead + fileSize);
			
			_stprintf_s(sumData, _T("%.2f %%"), percentValue);

			//设置进度条当前值
			SendMessage(hProgressBarWnd, PBM_SETPOS, (WPARAM)percentValue, (LPARAM)0);

			//SetDlgItemText(hWnd, IDC_BTN_DOWNLOAD, sumData);
			SetDlgItemText(hWnd, IDC_PROGRESS_RANGE, sumData);

		}
	}while(!bPaused && !bStop);

	if (bPaused && !bStop) 
	{
		InternetCloseHandle(hopen);
		fclose(fp);
		MessageBox(hWnd, _T("已暂停！"), _T("提示"), MB_OK);
		SetDlgItemText(hWnd, IDC_BTN_PAUSE, _T("继续"));
		return 0;
	}
	if(bStop)//bStop = true
	{
		InternetCloseHandle(hopen);
		fclose(fp);
		MessageBox(hWnd, _T("已停止下载！"), _T("提示"), MB_OK);
		SetDlgItemText(hWnd, IDC_PROGRESS_RANGE, _T("0 %"));
		EnableWindow(hFileAddrWnd,TRUE);
		EnableWindow(hDownLoadBtnWnd,TRUE);
		EnableWindow(hPauseBtnWnd,FALSE);
		EnableWindow(hStopBtnWnd,FALSE);
		SetDlgItemText(hWnd,IDC_BTN_DOWNLOAD,_T("下载"));
		SendMessage(hProgressBarWnd, PBM_SETPOS, (WPARAM)0, (LPARAM)0); //将进度条复位
		SetDlgItemText(hWnd,IDC_FILE_SAVEPATH,_T(""));
		EnableWindow(hBrowserBtnWnd,TRUE);
		bStop = FALSE;
		return 0;
	}

	EnableWindow(hDownLoadBtnWnd , TRUE);
	SetDlgItemText(hWnd, IDC_BTN_DOWNLOAD, _T("下载"));

	EnableWindow(hPauseBtnWnd , FALSE);
	SetDlgItemText(hWnd, IDC_BTN_PAUSE, _T("暂停"));

	InternetCloseHandle(hopen);
	fclose(fp);

	MessageBox(hWnd, _T("下载成功"), _T("提示"), MB_OK);
	SendMessage(hProgressBarWnd, PBM_SETPOS, (WPARAM)range.iLow, (LPARAM)0); //将进度条复位
	SetDlgItemText(hWnd, IDC_PROGRESS_RANGE, _T("0 %"));
	EnableWindow(hFileAddrWnd,TRUE);
	EnableWindow(hStopBtnWnd,FALSE);

	return 0;
}