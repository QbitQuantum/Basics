FARPROC CHookAPI::HookAPI(LPCTSTR pstrDllName,LPCSTR pstrFuncName,FARPROC pfnNewFunc,HMODULE hModCaller)
{
	if(hModCaller==NULL)
		return NULL;

	ULONG size;
	//获取指向PE文件中的Import中IMAGE_DIRECTORY_DESCRIPTOR数组的指针
	PIMAGE_IMPORT_DESCRIPTOR pImportDesc=(PIMAGE_IMPORT_DESCRIPTOR)
		ImageDirectoryEntryToData(hModCaller,TRUE,IMAGE_DIRECTORY_ENTRY_IMPORT,&size);
	if(pImportDesc==NULL)
		return NULL;
	HMODULE hModule=LoadLibrary(pstrDllName);
	//纪录函数地址
	FARPROC pfnOriginFunc=GetProcAddress(hModule,pstrFuncName);

	//查找记录,看看有没有我们想要的DLL
	USES_CONVERSION;
	char* pstrDest=W2A(pstrDllName);
	for(;pImportDesc->Name;pImportDesc++)
	{
		LPSTR pszDllName=(LPSTR)((PBYTE)hModCaller+pImportDesc->Name);
		if(lstrcmpiA(pszDllName,pstrDest)==0)
			break;
	}
	if(pImportDesc->Name==NULL)
	{
		return NULL;
	}
	//寻找我们想要的函数
	PIMAGE_THUNK_DATA pThunk=(PIMAGE_THUNK_DATA)((PBYTE)hModCaller+pImportDesc->FirstThunk);
	for(;pThunk->u1.Function;pThunk++)
	{
		//ppfn记录了与IAT表相应的地址
		PROC*ppfn=(PROC*)&pThunk->u1.Function ;
		if(*ppfn==pfnOriginFunc)
		{
			DWORD dwOldProtect;
			//修改内存包含属性
			VirtualProtect(ppfn, sizeof(DWORD), PAGE_READWRITE, &dwOldProtect);
			WriteProcessMemory(GetCurrentProcess(),ppfn,&(pfnNewFunc),sizeof(pfnNewFunc),NULL);
			return pfnOriginFunc;
		}
	}

	return NULL;
}