void  Apply_patches(HWND hwnd)
{
	HWND hList = GetDlgItem(hwnd,IDC_LIST_SEGMEN);
	netnode n("$ Apply SegMen");
	char szFilePath[256 * 2] = {0};
	strncpy(szFilePath, database_idb, 256);
	char *lpTmpBuf = strrchr(szFilePath, '\\') + 1;
	if(lpTmpBuf == (char*)1)
	{
		return;
	}
	*lpTmpBuf = 0;
	get_root_filename(lpTmpBuf, 256);
	msg("=============================\n");
	msg("Apply Path:%s\n", szFilePath);
	if(IsDlgButtonChecked(hwnd, IDC_APPLY_CHECK_BACK))
	{
		char szBackPath[300] = {0};
		sprintf(szBackPath, "%s.back", szFilePath);
		msg("BackFile Path:%s.back\n", szFilePath);
		CopyFile(szFilePath, szBackPath, FALSE);
		n.altset(CHECK_BACKFILE_INDEX, 1);
	}
	else
	{
		n.altset(CHECK_BACKFILE_INDEX, 0);
	}
	HANDLE hFile=CreateFile(szFilePath, GENERIC_WRITE | GENERIC_READ, 0, 
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);   //获得文件句柄
	HANDLE hMapping=CreateFileMapping(hFile,NULL,PAGE_READWRITE,0,0,NULL);  //创建内存映射对象
	if(INVALID_HANDLE_VALUE == hMapping)
	{
		msg("CreateFileMapping :%08X ErrorCode:%d\n", hMapping, GetLastError());
		return ;
	}
	unsigned char* pvFile=(unsigned char*)MapViewOfFile(hMapping,FILE_MAP_ALL_ACCESS,0,0,0); //创建视图 就是映射文件到内存;

	int i;
	segment_t *curseg;
	int seg_qty = get_segm_qty();
	for(i=0 ; i < seg_qty; i++)
	{
		char segname[0x100] = {0};
		curseg = getnseg(i);
		get_true_segm_name(curseg, segname, 255);
		int offset = get_fileregion_offset(curseg->startEA);
		int nSize = curseg->endEA - curseg->startEA;
		int nSelectStat = CheckedListBox_GetCheckState(hList, i);
		n.altset(i, nSelectStat);
		if(offset > 0 && nSelectStat)
		{
			//msg("offset:%X  segname:%s EA:%08X, nSize: %X\n", offset, segname, curseg->startEA, nSize);
			unsigned char *lpMem = (unsigned char*)malloc(nSize + 1);
			memset(lpMem, 0, nSize + 1);
			//if(get_many_bytes(curseg->startEA, lpMem, nSize))
			if(segReadBuf(curseg->startEA, lpMem, nSize))
			{
				msg("Apply SegMenName: %s\n", segname);
				SegWriteFile(pvFile, lpMem, nSize, offset);
			}
			//msg("lpMem:%X\n", lpMem);
			free(lpMem);
		}

		//	msg("Name:%s, StartEA:%08X, Offset:%08X, EndEA:%08X\n", segname, curseg->startEA, offset, curseg->endEA);


	}
	CloseHandle(hMapping);
	//	msg("CloseHandle(hMapping)\n");
	if(0 == UnmapViewOfFile(pvFile) )
	{
		msg("文件同步失败! ErrorCode:%d\n", GetLastError());
	}
	else
	{
		msg("文件同步成功!\n");
		msg("=============================\n");
	}
	//	msg("UnmapViewOfFile(pvFile);\n");
	CloseHandle(hFile);
	
	return;
}