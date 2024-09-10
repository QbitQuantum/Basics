//查找目标程序有无目标模块
void pe_findDllModule(LPTSTR lpFilePath,LPSTR lpDllName,ppe_retn_msg p_msg)
{
	//打开文件
	HANDLE hFile = CreateFile(lpFilePath,
		GENERIC_WRITE | GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	//打开文件失败
	if(hFile == INVALID_HANDLE_VALUE)
	{
		p_msg->isSuccessed = false;
		swprintf(p_msg->tsMsg,L"can't create file! error code : %d",GetLastError());
		//
		return;
	}

	//获得文件大小
	DWORD dwFileSize = GetFileSize(hFile , 0 );

	//映射文件
	HANDLE hMap = CreateFileMapping(hFile ,
		0 ,
		PAGE_READWRITE ,
		0 ,
		dwFileSize ,
		0);

	//文件映射内存失败
	if(hMap == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);

		p_msg->isSuccessed = false;
		swprintf(p_msg->tsMsg,L"can't create file mapping! error code : %d",GetLastError());
		//
		return ;
	}

	//获得映射基址
	LPBYTE lpBase = (LPBYTE)MapViewOfFile(hMap , FILE_MAP_READ | FILE_MAP_WRITE , 0 , 0 , dwFileSize);

	//文件映射内存失败
	if(lpBase == NULL)
	{
		CloseHandle(hFile);
		CloseHandle(hMap);
		UnmapViewOfFile(lpBase);

		p_msg->isSuccessed = false;
		swprintf(p_msg->tsMsg,L"can't map view of file! error code : %d",GetLastError());
		//
		return ;
	}

	//获得dos头部
	PIMAGE_DOS_HEADER pImage_dos_header=(PIMAGE_DOS_HEADER)lpBase;
	//获得nt头部
	PIMAGE_NT_HEADERS pImage_nt_header = (PIMAGE_NT_HEADERS)((ULONG)lpBase + pImage_dos_header->e_lfanew);
	//获得导入表
	PIMAGE_IMPORT_DESCRIPTOR pImage_import_descriptor = (PIMAGE_IMPORT_DESCRIPTOR)ImageRvaToVa(pImage_nt_header,lpBase,pImage_nt_header->OptionalHeader.DataDirectory[1].VirtualAddress,NULL);
	
	//遍历导入表
	while(pImage_import_descriptor->Name != NULL)
	{
		if (pImage_import_descriptor->OriginalFirstThunk == 0 && pImage_import_descriptor->FirstThunk == 0) 
		{
			break;
		}

		//如果找到目标模块的话
		if(!strcmpi((LPSTR)ImageRvaToVa(pImage_nt_header,lpBase,pImage_import_descriptor->Name,NULL),lpDllName))
		{
			CloseHandle(hFile);
			CloseHandle(hMap);
			UnmapViewOfFile(lpBase);

			p_msg->isSuccessed = true;
			return;
		}

		//
		pImage_import_descriptor ++;
	}

	CloseHandle(hFile);
	CloseHandle(hMap);
	UnmapViewOfFile(lpBase);

	//看来是没有找到
	p_msg->isSuccessed = false;
	swprintf(p_msg->tsMsg,L"no error!");
}