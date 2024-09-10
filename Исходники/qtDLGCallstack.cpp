void qtDLGCallstack::ShowCallStack()
{
	clsDebugger *pDebugger = qtDLGNanomite::GetInstance()->coreDebugger;
	
	HANDLE	hProc = pDebugger->GetCurrentProcessHandle(),
			hThread = OpenThread(THREAD_GETSET_CONTEXT,false,pDebugger->GetCurrentTID());
	PSYMBOL_INFOW pSymbol = (PSYMBOL_INFOW)malloc(sizeof(SYMBOL_INFOW) + MAX_PATH * 2);
	DWORD dwMaschineMode = NULL;
	LPVOID pContext;
	STACKFRAME64 stackFr = {0};
	stackFr.AddrPC.Mode = AddrModeFlat;
	stackFr.AddrFrame.Mode = AddrModeFlat;
	stackFr.AddrStack.Mode = AddrModeFlat;

	QString sFuncName,
		sFuncMod,
		sReturnToFunc,
		sReturnToMod;
	quint64 dwStackAddr,
		dwReturnTo,
		dwEIP,
		dwDisplacement;
	IMAGEHLP_LINEW64 imgSource = {0};
	IMAGEHLP_MODULEW64 imgMod = {0};

#ifdef _AMD64_
	BOOL bIsWOW64 = false;

	if(clsAPIImport::pIsWow64Process)
		clsAPIImport::pIsWow64Process(hProc,&bIsWOW64);

	if(bIsWOW64)
	{
		dwMaschineMode = IMAGE_FILE_MACHINE_I386;
		WOW64_CONTEXT cTT = pDebugger->wowProcessContext;
		pContext = &cTT;

		stackFr.AddrPC.Offset = cTT.Eip;
		stackFr.AddrFrame.Offset = cTT.Ebp;
		stackFr.AddrStack.Offset = cTT.Esp;	
	}
	else
	{
		dwMaschineMode = IMAGE_FILE_MACHINE_AMD64;
		CONTEXT cTT = pDebugger->ProcessContext;
		pContext = &cTT;

		stackFr.AddrPC.Offset = cTT.Rip;
		stackFr.AddrFrame.Offset = cTT.Rbp;
		stackFr.AddrStack.Offset = cTT.Rsp;	
	}
#else
	dwMaschineMode = IMAGE_FILE_MACHINE_I386;
	CONTEXT cTT = pDebugger->ProcessContext;
	pContext = &cTT;

	stackFr.AddrPC.Offset = cTT.Eip;
	stackFr.AddrFrame.Offset = cTT.Ebp;
	stackFr.AddrStack.Offset = cTT.Esp;	

#endif

	tblCallstack->setRowCount(0);

	do
	{
		if(!StackWalk64(dwMaschineMode,hProc,hThread,&stackFr,pContext,NULL,SymFunctionTableAccess64,SymGetModuleBase64,0))        
			break;

		memset(&imgSource,0,sizeof(IMAGEHLP_LINEW64));
		imgSource.SizeOfStruct = sizeof(IMAGEHLP_LINEW64);

		dwStackAddr = stackFr.AddrStack.Offset;
		dwEIP = stackFr.AddrPC.Offset;
		dwReturnTo = stackFr.AddrReturn.Offset;


		memset(&imgMod,0,sizeof(IMAGEHLP_MODULEW64));
		imgMod.SizeOfStruct = sizeof(IMAGEHLP_MODULEW64);
		memset(pSymbol,0,sizeof(SYMBOL_INFOW) + MAX_PATH * 2);
		pSymbol->SizeOfStruct = sizeof(SYMBOL_INFOW);
		pSymbol->MaxNameLen = MAX_PATH;

		SymGetModuleInfoW64(hProc,dwEIP,&imgMod);
		SymFromAddrW(hProc,dwEIP,&dwDisplacement,pSymbol);
		sFuncName = QString::fromWCharArray(pSymbol->Name);
		sFuncMod = QString::fromWCharArray(imgMod.ModuleName);


		memset(&imgMod,0,sizeof(IMAGEHLP_MODULEW64));
		imgMod.SizeOfStruct = sizeof(IMAGEHLP_MODULEW64);
		memset(pSymbol,0,sizeof(SYMBOL_INFOW) + MAX_PATH * 2);
		pSymbol->SizeOfStruct = sizeof(SYMBOL_INFOW);
		pSymbol->MaxNameLen = MAX_PATH;

		SymGetModuleInfoW64(hProc,dwReturnTo,&imgMod);
		SymFromAddrW(hProc,dwReturnTo,&dwDisplacement,pSymbol);
		sReturnToMod = QString::fromWCharArray(imgMod.ModuleName);
		sReturnToFunc = QString::fromWCharArray(pSymbol->Name);

		if(SymGetLineFromAddrW64(hProc,dwEIP,(PDWORD)&dwDisplacement,&imgSource))
		{
			OnCallStack(dwStackAddr,
				dwReturnTo,sReturnToFunc,sReturnToMod,
				dwEIP,sFuncName,sFuncMod,
				QString::fromWCharArray(imgSource.FileName),imgSource.LineNumber);
		}
		else
		{
			OnCallStack(dwStackAddr,
				dwReturnTo,sReturnToFunc,sReturnToMod,
				dwEIP,sFuncName,sFuncMod,
				QString(""),0);
		}

	}while(stackFr.AddrReturn.Offset != 0);

	free(pSymbol);
	CloseHandle(hThread);
}