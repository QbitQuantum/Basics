void QueryDpcTimer(HWND m_hWnd,ULONG ID,CMyList *m_list)
{
	DWORD dwReadByte;
	int i=0;
	int ItemNum = m_list->GetItemCount();

	SHFILEINFO shfileinfo;
	DpcTimerImg.Create(16,16, ILC_COLOR32, 2, 80);
	HIMAGELIST hImageList = NULL;

	SetDlgItemTextW(m_hWnd,ID,L"正在扫描DpcTimer，请稍后...");

	if (DpcTimer)
	{
		VirtualFree(DpcTimer,sizeof(MyDpcTimer)*MAX_DPCTIMER_COUNT*2,MEM_RESERVE | MEM_COMMIT);
		DpcTimer = 0;
	}
	DpcTimer = (PMyDpcTimer)VirtualAlloc(0,sizeof(MyDpcTimer)*MAX_DPCTIMER_COUNT*2,MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (DpcTimer)
	{
		memset(DpcTimer,0,sizeof(MyDpcTimer)*MAX_DPCTIMER_COUNT*2);

		ReadFile((HANDLE)LIST_DPC_TIMER,DpcTimer,sizeof(MyDpcTimer)*MAX_DPCTIMER_COUNT*2,&dwReadByte,0);

		for (i=0;i< (int)DpcTimer->ulCount;i++)
		{
			WCHAR lpwzTextOut[100];
			memset(lpwzTextOut,0,sizeof(lpwzTextOut));
			wsprintfW(lpwzTextOut,L"共有 %d 个数据，正在扫描第 %d 个，请稍后...",DpcTimer->ulCount,i);
			SetDlgItemTextW(m_hWnd,ID,lpwzTextOut);

			WCHAR lpwzKTimer[256] = {0};
			WCHAR lpwzKDpc[256] = {0};
			WCHAR lpwzPeriod[256] = {0};
			WCHAR lpwzDpcRoutineAddress[256] = {0};
			WCHAR lpwzFullSysName[256] = {0};

			memset(lpwzKTimer,0,sizeof(lpwzKTimer));
			memset(lpwzKDpc,0,sizeof(lpwzKDpc));
			memset(lpwzPeriod,0,sizeof(lpwzPeriod));
			memset(lpwzDpcRoutineAddress,0,sizeof(lpwzDpcRoutineAddress));
			memset(lpwzFullSysName,0,sizeof(lpwzFullSysName));

			MultiByteToWideChar(
				CP_ACP,
				0, 
				DpcTimer->MyTimer[i].lpszModule,
				-1, 
				lpwzFullSysName, 
				strlen(DpcTimer->MyTimer[i].lpszModule)
				);
//********************************************************************
			WCHAR lpwzDosFullPath[256];
			WCHAR lpwzWinDir[256];
			WCHAR lpwzSysDisk[256];

			memset(lpwzWinDir,0,sizeof(lpwzWinDir));
			memset(lpwzSysDisk,0,sizeof(lpwzSysDisk));
			memset(lpwzDosFullPath,0,sizeof(lpwzDosFullPath));

			GetWindowsDirectoryW(lpwzWinDir,sizeof(lpwzWinDir));
			memcpy(lpwzSysDisk,lpwzWinDir,4);

			if (wcsstr(lpwzFullSysName,L"\\??\\"))
			{
				//开始这种路径的处理
				memset(lpwzDosFullPath,0,sizeof(lpwzDosFullPath));
				wcsncpy(lpwzDosFullPath,lpwzFullSysName+wcslen(L"\\??\\"),wcslen(lpwzFullSysName)-wcslen(L"\\??\\"));
				goto Next;
			}
			if (wcsstr(lpwzFullSysName,L"\\WINDOWS\\system32\\"))
			{
				memset(lpwzDosFullPath,0,sizeof(lpwzDosFullPath));
				wcscat(lpwzDosFullPath,lpwzSysDisk);
				wcscat(lpwzDosFullPath,lpwzFullSysName);
				//MessageBoxW(lpwzDosFullPath,lpwzFullSysName,0);
				goto Next;
			}
			if (wcsstr(lpwzFullSysName,L"\\SystemRoot\\"))
			{
				WCHAR lpwzTemp[256];
				memset(lpwzTemp,0,sizeof(lpwzTemp));
				memset(lpwzDosFullPath,0,sizeof(lpwzDosFullPath));
				wcscat(lpwzTemp,lpwzSysDisk);
				wcscat(lpwzTemp,L"\\WINDOWS\\");
				wcscat(lpwzDosFullPath,lpwzTemp);
				wcsncpy(lpwzDosFullPath+wcslen(lpwzTemp),lpwzFullSysName+wcslen(L"\\SystemRoot\\"),wcslen(lpwzFullSysName) - wcslen(L"\\SystemRoot\\"));
				goto Next;
			}
			if (!wcsstr(lpwzFullSysName,L"\\"))
			{
				memset(lpwzDosFullPath,0,sizeof(lpwzDosFullPath));
				wcscat(lpwzDosFullPath,lpwzSysDisk);
				wcscat(lpwzDosFullPath,L"\\WINDOWS\\system32\\drivers\\");
				wcscat(lpwzDosFullPath,lpwzFullSysName);
				goto Next;
			}
Next:

//********************************************************************
			wsprintfW(lpwzKTimer,L"0x%08X",DpcTimer->MyTimer[i].TimerAddress);
			wsprintfW(lpwzKDpc,L"0x%08X",DpcTimer->MyTimer[i].DpcAddress);
			wsprintfW(lpwzPeriod,L"%d",DpcTimer->MyTimer[i].Period);
			wsprintfW(lpwzDpcRoutineAddress,L"0x%08X",DpcTimer->MyTimer[i].DpcRoutineAddress);

			if (_wcsnicmp(lpwzDosFullPath,L"Unknown",wcslen(lpwzDosFullPath)) == 0)
			{
				m_list->InsertItem(i,lpwzKTimer,RGB(255,20,147));
			}else
			{
				m_list->InsertItem(i,lpwzKTimer,RGB(77,77,77));
			}
			m_list->SetItemText(i,1,lpwzKDpc);
			m_list->SetItemText(i,2,lpwzPeriod);
			m_list->SetItemText(i,3,lpwzDpcRoutineAddress);
			m_list->SetItemText(i,4,lpwzDosFullPath);


			hImageList=(HIMAGELIST)::SHGetFileInfo(lpwzDosFullPath,0,&shfileinfo,sizeof(shfileinfo),SHGFI_ICON);
			DpcTimerImg.Add(shfileinfo.hIcon);
			m_list->SetImageList(&DpcTimerImg);
			m_list->SetItemImageId(i,i);
			DestroyIcon(shfileinfo.hIcon);
		}
	}else{
		WCHAR lpwzTextOut[100];
		memset(lpwzTextOut,0,sizeof(lpwzTextOut));
		wsprintfW(lpwzTextOut,L"申请内存错误， 请重新运行A盾\r\n错误代码:%d\n",GetLastError());
		MessageBox(0,lpwzTextOut,0,0);
	}
	WCHAR lpwzTextOut[100];
	memset(lpwzTextOut,0,sizeof(lpwzTextOut));
	wsprintfW(lpwzTextOut,L"DpcTimer扫描完毕，共有 %d 个数据",i);
	SetDlgItemTextW(m_hWnd,ID,lpwzTextOut);
}