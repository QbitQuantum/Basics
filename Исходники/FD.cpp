DWORD CFD::FDFileConnect	( PFILE_ITEM_INFO pItem )
{
	DeleteFile ( pItem->szFileName ) ;

	// 打开目标文件
	HANDLE hFile = CreateFile (pItem->szFileName, GENERIC_READ|GENERIC_WRITE, \
		FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL ) ;
	if ( hFile == INVALID_HANDLE_VALUE )
		return GetLastError() ;

	// 创建文件内存映射内核对象
	HANDLE hMapFile = CreateFileMapping(hFile,NULL,PAGE_READWRITE,0,pItem->dwLowFileSize,NULL) ;
	if ( hMapFile == NULL )
	{
		CloseHandle ( hFile ) ;
		return GetLastError() ;
	}

	CString TempStr ;
	DWORD	dwCurAddr = 0, dwCurPart = 0 ;
	LPVOID lpMapAddr = 0 ;

	// 分块循环映射文件
	for ( UINT i = 1; i <= pItem->dwPartNum; i++ )
	{
		dwCurPart = pItem->dwLowFileSize - dwCurAddr ;
		if ( dwCurPart > pItem->dwPartSize )
			dwCurPart = pItem->dwPartSize ;

		lpMapAddr = MapViewOfFile ( hMapFile, FILE_MAP_WRITE, 0, dwCurAddr, dwCurPart ) ;
		if ( lpMapAddr == NULL )
		{
			CloseHandle ( hMapFile ) ;
			CloseHandle ( hFile ) ;
			return GetLastError() ;
		}

		dwCurAddr += dwCurPart ;

		TempStr.Format ( "%s.PART_%d", pItem->szFileName, i ) ;
		
		// 打开子文件，并进行内存映射
		HANDLE hNewFile = CreateFile ( TempStr,GENERIC_READ, \
			FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL ) ;
		if ( hFile == INVALID_HANDLE_VALUE )
		{
			UnmapViewOfFile ( lpMapAddr ) ;
			CloseHandle ( hMapFile ) ;
			CloseHandle ( hFile ) ;
			return GetLastError() ;
		}
		
		HANDLE hNewMapFile = CreateFileMapping (hNewFile,NULL,PAGE_READONLY,0,0,NULL ) ;
		if ( hNewMapFile == NULL )
		{	
			UnmapViewOfFile ( lpMapAddr ) ;
			CloseHandle ( hMapFile ) ;
			CloseHandle ( hFile ) ;
			CloseHandle ( hNewFile ) ;
			return GetLastError() ;
		}

		LPVOID lpNewMapAddr = MapViewOfFile ( hNewMapFile, FILE_MAP_READ, 0, 0, 0 ) ;
		if ( lpMapAddr == NULL )
		{	
			UnmapViewOfFile ( lpMapAddr ) ;
			CloseHandle ( hMapFile ) ;
			CloseHandle ( hFile ) ;
			CloseHandle ( hNewMapFile ) ;
			CloseHandle ( hNewFile ) ;
			return GetLastError() ;
		}

		memcpy ( lpMapAddr, lpNewMapAddr, dwCurPart ) ;
		FlushViewOfFile ( lpMapAddr, dwCurPart ) ;

		UnmapViewOfFile ( lpMapAddr ) ;
		UnmapViewOfFile ( lpNewMapAddr ) ;
		CloseHandle ( hNewMapFile ) ;
		CloseHandle ( hNewFile ) ;
	}

	CloseHandle ( hMapFile ) ;
	CloseHandle ( hFile ) ;

	// 删除所有子文件
	this->DeleteAllPartFiles ( pItem->szFileName ) ;

	return 0 ;
}