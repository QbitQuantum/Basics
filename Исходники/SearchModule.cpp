DWORD WINAPI SearchWorkThreadMgrProc(LPVOID lpParm)
{
	CQuickSearchDlg * lpDlg = (CQuickSearchDlg *)lpParm;
	if (lpDlg == NULL)
	{
		lpDlg->NotifyStatusMsg(_T("线程的非法引用！请退出程序，然后重试。"));
		return ERROR_INVALID_PARAMETER;
	}
	if (!EnablePrivilege(SE_DEBUG_NAME, TRUE))
	{
		lpDlg->NotifyStatusMsg(_T("提权失败！"));
		return ERROR_ACCESS_DENIED;
	}
	for (int i = 0; lpDlg->GetSafeHwnd() == NULL && i < 10; i++)
		Sleep(100);

	lpDlg->NotifyStatusMsg(_T("就绪..."));
	while (TRUE)
	{
		TCHAR szMsg[nMSG_SIZE] = { 0 };
		ULONG nFoundedCont = 0;

		WaitForSingleObject(g_hSearchEvent, INFINITE);
		if (WaitForSingleObject(g_hQuitEvent, 50) == WAIT_OBJECT_0)
		{
			// 执行搜索之前检测有无退出信号
			break;
		}

		lpDlg->InitList();
		SEARCH_PROGRRESS_INFO spi[26] = { 0 };
		for (short i = 0; i < 26; i++)
		{
			spi[i].m_nFoundCount = 0;
			spi[i].m_nViewCount = 0;
			spi[i].m_lpDlg = lpDlg;
			spi[i].m_Update = update;
			ParseSearchObject(lpDlg->GetSearchString().GetBuffer(), spi[i].m_vecSearchStrings);
			lpDlg->GetSearchString().ReleaseBuffer();
		}

		g_nTotalFound = 0;			// 已经找到的数量
		g_nTotalView = 0;			// 已经查找了的数量
		CString strSearchStartPath(lpDlg->GetSearchLocation());
		short nSearchThreadIndex = 0;
		HANDLE hSearchThread[26] = { 0 };
		DWORD dwSeachThreadId[26] = { 0 };
		if (strSearchStartPath == _T("0"))
		{
			TCHAR szAllDriverLetters[100] = { 0 };
			DWORD len = GetLogicalDriveStrings(sizeof(szAllDriverLetters) / sizeof(TCHAR), szAllDriverLetters);
			for (TCHAR * lpszCurrentDriverLetter = szAllDriverLetters; *lpszCurrentDriverLetter; lpszCurrentDriverLetter += _tcslen(lpszCurrentDriverLetter) + 1)
			{
				// 创建搜索线程
				Sleep(nSearchThreadIndex * 1000);
				StringCchPrintf(spi[nSearchThreadIndex].m_szStartLocation, MAX_PATH - 1, _T("%C:"), lpszCurrentDriverLetter[0]);
				spi[nSearchThreadIndex].m_bFastMode = lpDlg->GetFastMode();
				hSearchThread[nSearchThreadIndex] = CreateThread(
					NULL,         // 使用默认的安全描述符
					0,            // 使用默认的栈大小
					(LPTHREAD_START_ROUTINE)SearchThreadProc,
					(LPVOID)(spi + nSearchThreadIndex),
					CREATE_SUSPENDED,						// 先挂起
					dwSeachThreadId + nSearchThreadIndex);	// 取得线程ID
				if (hSearchThread[nSearchThreadIndex])
				{
					if (spi[nSearchThreadIndex].m_bFastMode)
						if (!SetThreadPriority(hSearchThread[nSearchThreadIndex], THREAD_PRIORITY_TIME_CRITICAL))
							if (!SetThreadPriority(hSearchThread[nSearchThreadIndex], THREAD_PRIORITY_HIGHEST))
								if (!SetThreadPriority(hSearchThread[nSearchThreadIndex], THREAD_PRIORITY_ABOVE_NORMAL))
									if (!SetThreadPriority(hSearchThread[nSearchThreadIndex], THREAD_PRIORITY_HIGHEST))
										SetThreadPriority(hSearchThread[nSearchThreadIndex], THREAD_PRIORITY_NORMAL);
					ResumeThread(hSearchThread[nSearchThreadIndex]);
					SetThreadPriorityBoost(hSearchThread[nSearchThreadIndex], !spi[nSearchThreadIndex].m_bFastMode);	// 系统动态调整线程优先级选项
					nSearchThreadIndex++;
				}
			}
			WaitForMultipleObjects(nSearchThreadIndex, hSearchThread, TRUE, INFINITE);
			for (short i = 0; i < nSearchThreadIndex; i++)
			{
				if (hSearchThread[i])
					CloseHandle(hSearchThread[i]);
			}
		}
		else
		{
			// 创建搜索线程
			DWORD ThreadID = 0;
			StringCchPrintf(spi[0].m_szStartLocation, MAX_PATH - 1, _T("%s"), strSearchStartPath);
			spi[0].m_bFastMode = lpDlg->GetFastMode();
			hSearchThread[0] = CreateThread(
				NULL,         // 使用默认的安全描述符
				0,            // 使用默认的栈大小
				(LPTHREAD_START_ROUTINE)SearchThreadProc,
				(LPVOID)&spi[0],
				CREATE_SUSPENDED,						// 先挂起
				&ThreadID);	// 取得线程ID
			if (hSearchThread)
			{
				if (spi[0].m_bFastMode)
					if (!SetThreadPriority(hSearchThread[nSearchThreadIndex], THREAD_PRIORITY_TIME_CRITICAL))
						if (!SetThreadPriority(hSearchThread[nSearchThreadIndex], THREAD_PRIORITY_HIGHEST))
							if (!SetThreadPriority(hSearchThread[nSearchThreadIndex], THREAD_PRIORITY_ABOVE_NORMAL))
								if (!SetThreadPriority(hSearchThread[nSearchThreadIndex], THREAD_PRIORITY_HIGHEST))
									SetThreadPriority(hSearchThread[nSearchThreadIndex], THREAD_PRIORITY_NORMAL);
				ResumeThread(hSearchThread[nSearchThreadIndex]);
				SetThreadPriorityBoost(hSearchThread[nSearchThreadIndex], !spi[nSearchThreadIndex].m_bFastMode);	// 系统动态调整线程优先级选项

				WaitForSingleObject(hSearchThread[nSearchThreadIndex], INFINITE);
				CloseHandle(hSearchThread[nSearchThreadIndex]);
				nSearchThreadIndex++;
			}
		}
		if (g_vecCurrentFindData.size())
		{
			lpDlg->InitList();
			lpDlg->NotifyStatusMsg(_T("正在更新搜索结果列表，请稍候..."));
			lpDlg->UpdateList(g_vecCurrentFindData);
			ULONG nViewCount = 0, nFoundCount = 0;
			for (short i = 0; i < nSearchThreadIndex; i++)
			{
				nViewCount += spi[i].m_nViewCount;
				nFoundCount += spi[i].m_nFoundCount;
			}
			StringCchPrintf(szMsg, nMSG_SIZE - 1, _T("搜索完成，在%d个项目中共找到了%d个对象。"), nViewCount, nFoundCount);
			lpDlg->NotifyStatusMsg(szMsg);
		}
		else
		{
			lpDlg->NotifyStatusMsg(_T("未找到！"));
		}

		// 搜索完了，重置状态
		g_vecCurrentFindData.clear();
		std::vector<FIND_DATA> vecCurrentFindDataTemp;
		g_vecCurrentFindData.swap(vecCurrentFindDataTemp);
		g_hBrokenEvent ? ResetEvent(g_hBrokenEvent) : 0;
		g_hSearchEvent ? ResetEvent(g_hSearchEvent) : 0;

		if (WaitForSingleObject(g_hQuitEvent, 50) == WAIT_OBJECT_0)
		{
			// 搜索任务完成之后检测有无退出信号
			OutputDebugString(_T("Quiting..."));
			break;
		}
	}

	return 0;
}