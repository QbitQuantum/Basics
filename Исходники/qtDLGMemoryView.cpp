void qtDLGMemoryView::DisplayMemory()
{
	PTCHAR sTemp = (PTCHAR)clsMemManager::CAlloc(MAX_PATH * sizeof(TCHAR));
	PTCHAR sTemp2 = (PTCHAR)clsMemManager::CAlloc(MAX_PATH * sizeof(TCHAR));

	MEMORY_BASIC_INFORMATION mbi;

	tblMemoryView->setRowCount(0);
	for(size_t i = m_processCountEntry; i < m_processCountEnd;i++)
	{
		quint64 dwAddress = NULL;
		while(VirtualQueryEx(m_pMainWindow->coreDebugger->PIDs[i].hProc,(LPVOID)dwAddress,&mbi,sizeof(mbi)))
		{
			tblMemoryView->insertRow(tblMemoryView->rowCount());

			// PID
			tblMemoryView->setItem(tblMemoryView->rowCount() -1,0,
				new QTableWidgetItem(QString().sprintf("%08X",m_pMainWindow->coreDebugger->PIDs[i].dwPID)));
			

			// Base Address
#ifdef _AMD64_
			wsprintf(sTemp,L"%016I64X",mbi.BaseAddress);
#else
			wsprintf(sTemp,L"%016X",mbi.BaseAddress);
#endif
			tblMemoryView->setItem(tblMemoryView->rowCount() -1,1,
				new QTableWidgetItem(QString().fromStdWString(sTemp)));

			// Size
			wsprintf(sTemp,L"%08X",mbi.RegionSize);
			tblMemoryView->setItem(tblMemoryView->rowCount() -1,2,
				new QTableWidgetItem(QString().fromStdWString(sTemp)));

			// Path
			size_t	iModPos = NULL,
					iModLen = NULL;

			memset(sTemp,0,MAX_PATH * sizeof(TCHAR));
			memset(sTemp2,0,MAX_PATH * sizeof(TCHAR));
			GetMappedFileName(m_pMainWindow->coreDebugger->PIDs[i].hProc,(LPVOID)dwAddress,sTemp2,MAX_PATH);

			iModLen = wcslen(sTemp2);
			if(iModLen > 0)
			{
				for(size_t i = iModLen; i > 0 ; i--)
				{
					if(sTemp2[i] == '\\')
					{
						iModPos = i;
						break;
					}
				}
						
				memcpy_s(sTemp,MAX_PATH,(LPVOID)&sTemp2[iModPos + 1],(iModLen - iModPos) * sizeof(TCHAR));

				tblMemoryView->setItem(tblMemoryView->rowCount() -1,3,
					new QTableWidgetItem(QString().fromStdWString(sTemp)));			
			}
			else
				tblMemoryView->setItem(tblMemoryView->rowCount() -1,3,
					new QTableWidgetItem(QString("")));		

			// Mem Type
			switch (mbi.State)
			{
			case MEM_FREE:			wsprintf(sTemp,L"%s",L"Free");		break;
			case MEM_RESERVE:       wsprintf(sTemp,L"%s",L"Reserve");	break;
			case MEM_COMMIT:
				switch (mbi.Type)
				{
				case MEM_FREE:		wsprintf(sTemp,L"%s",L"Free");     break;
				case MEM_RESERVE:   wsprintf(sTemp,L"%s",L"Reserve");  break;
				case MEM_IMAGE:		wsprintf(sTemp,L"%s",L"Image");    break;
				case MEM_MAPPED:    wsprintf(sTemp,L"%s",L"Mapped");   break;
				case MEM_PRIVATE:   wsprintf(sTemp,L"%s",L"Private");  break;
				}
				break;
			}
			tblMemoryView->setItem(tblMemoryView->rowCount() -1,4,
				new QTableWidgetItem(QString().fromStdWString(sTemp)));

			// Access
			wsprintf(sTemp,L"%s",L"Unknown");
			if(mbi.State == MEM_FREE) mbi.Protect = PAGE_NOACCESS;
			if(mbi.State == MEM_RESERVE) mbi.Protect = PAGE_NOACCESS;
			switch (mbi.Protect & ~(PAGE_GUARD | PAGE_NOCACHE | PAGE_WRITECOMBINE))
			{
			case PAGE_READONLY:          wsprintf(sTemp,L"%s",L"-R--"); break;
			case PAGE_READWRITE:         wsprintf(sTemp,L"%s",L"-RW-"); break;
			case PAGE_WRITECOPY:         wsprintf(sTemp,L"%s",L"-RWC"); break;
			case PAGE_EXECUTE:           wsprintf(sTemp,L"%s",L"E---"); break;
			case PAGE_EXECUTE_READ:      wsprintf(sTemp,L"%s",L"ER--"); break;
			case PAGE_EXECUTE_READWRITE: wsprintf(sTemp,L"%s",L"ERW-"); break;
			case PAGE_EXECUTE_WRITECOPY: wsprintf(sTemp,L"%s",L"ERWC"); break; 
			case PAGE_NOACCESS:          wsprintf(sTemp,L"%s",L"----"); break;
			}
			tblMemoryView->setItem(tblMemoryView->rowCount() -1,5,
				new QTableWidgetItem(QString().fromStdWString(sTemp)));

			dwAddress += mbi.RegionSize;
		}
	}
	clsMemManager::CFree(sTemp2);
	clsMemManager::CFree(sTemp);
}