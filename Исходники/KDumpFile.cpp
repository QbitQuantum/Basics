int KDumpModuleAnalyzer::GetModuleInfo(KDumpModuleInfo *pRetDumpModuleInfo)
{
	int nResult = false;
	int nRetCode = false;

#ifdef _DEBUG
	struct IMAGEHLP_SYMBOL64_EX : IMAGEHLP_SYMBOL64
	{
		TCHAR _EX[MAX_PATH];
	};

	DWORD64 dwDisplacement;
	IMAGEHLP_SYMBOL64_EX Symbol;
	Symbol.MaxNameLength = sizeof(Symbol._EX) / sizeof(Symbol._EX[0]);
	nRetCode = SymGetSymFromAddr64(m_hProcess, m_Stackframe.AddrPC.Offset, &dwDisplacement, &Symbol);
	if (nRetCode)
	{
#ifdef OPEN_LOG_AND_BREAK
		KLogPrintf("%s\t%d\t%x\n", Symbol.Name, 0, m_Stackframe.AddrPC.Offset);
#endif
		printf("%s\t%d\t%x\n", Symbol.Name, 0, m_Stackframe.AddrPC.Offset);
	}
#endif

	KG_PROCESS_ERROR(pRetDumpModuleInfo);
	memset(pRetDumpModuleInfo, 0, sizeof(KDumpModuleInfo));
	
	pRetDumpModuleInfo->dwStackAddress = m_dwStackAddress;
	nRetCode = EnumerateLoadedModules64(m_hProcess, KDumpModuleAnalyzer::FindExceptionModule, (void *)pRetDumpModuleInfo);
	KG_PROCESS_ERROR(nRetCode);//EnumerateLoadedModules64 执行失败
	KG_PROCESS_ERROR(pRetDumpModuleInfo->nFindDumpModuleFlag);//FindExceptionModule 没有查找到
	
#ifdef OPEN_LOG_AND_BREAK
	KLogPrintf(
		"Name:%s\tBase:%llp\tOffset:%llp\tStack:%llp", 
		pRetDumpModuleInfo->szModuleName, 
		pRetDumpModuleInfo->dwModuleBase, 
		pRetDumpModuleInfo->dwStackAddress,
		m_dwStackAddress
	);
#endif

	nResult = true;
Exit0:
	return nResult;
}