///////////////////////////////////// HookOneAPI 函数 /////////////////////////////////////////   
//进行IAT转换的关键函数，其参数含义：   
//pszCalleeModuleName：需要hook的模块名   
//pfnOriginApiAddress：要替换的自己API函数的地址   
//pfnDummyFuncAddress：需要hook的模块名的地址   
//hModCallerModule：我们要查找的模块名称，如果没有被赋值，   
//     将会被赋值为枚举的程序所有调用的模块   
void WINAPI HookOneAPI(LPCTSTR pszCalleeModuleName,PROC pfnOriginApiAddress,    
	PROC pfnDummyFuncAddress,HMODULE hModCallerModule)   
{   
	
	ULONG size;   
	short sts =0;
	//获取指向PE文件中的Import中IMAGE_DIRECTORY_DESCRIPTOR数组的指针   
	PIMAGE_IMPORT_DESCRIPTOR pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)   
		ImageDirectoryEntryToData(hModCallerModule,TRUE,IMAGE_DIRECTORY_ENTRY_IMPORT,&size);   
	MY_ASSERT (pImportDesc != NULL) ;
	//查找记录,看看有没有我们想要的DLL   
	for (;pImportDesc->Name;pImportDesc++)   
	{   
		LPSTR pszDllName = (LPSTR)((PBYTE)hModCallerModule+pImportDesc->Name);   
		if (lstrcmpiA(pszDllName,pszCalleeModuleName) == 0)   
			break;   
	}   
	MY_ASSERT (pImportDesc->Name != NULL) ;
	//寻找我们想要的函数   
	PIMAGE_THUNK_DATA pThunk =    
		(PIMAGE_THUNK_DATA)((PBYTE)hModCallerModule+pImportDesc->FirstThunk);//IAT   
	BOOL bFind=0;
	for (;pThunk->u1.Function;pThunk++)   
	{   
		//ppfn记录了与IAT表项相应的函数的地址   
		PROC * ppfn= (PROC *)&pThunk->u1.Function;     
		if (*ppfn == pfnOriginApiAddress)    
		{   
			//如果地址相同，也就是找到了我们想要的函数，进行改写，将其指向我们所定义的函数   
			MY_ASSERT(WriteProcessMemory(GetCurrentProcess(),ppfn,&(pfnDummyFuncAddress),   
				sizeof(pfnDummyFuncAddress),NULL));   
			bFind=1;
			break;
		}   
	} 
	MY_ASSERT(bFind);
Exit:
	TRACE("HookOneAPI %s %x->%x %x %d\n",pszCalleeModuleName,pfnOriginApiAddress, pfnDummyFuncAddress,hModCallerModule, sts);
}   