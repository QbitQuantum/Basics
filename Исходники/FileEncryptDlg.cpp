void CFileEncryptDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);
	CString FileInfo;
	TCHAR *pName;
	WIN32_FIND_DATA FindFileData;
	SYSTEMTIME mysystime;
	FILETIME loctime;
	if (DropCount <= 1)
	{
		HANDLE hFile;
		int NameSize = DragQueryFile(hDropInfo, 0, NULL, 0);
		pName = new TCHAR[NameSize + 1];
		DragQueryFile(hDropInfo, 0, pName, NameSize+1);
		hFile = FindFirstFile(pName, &FindFileData);
		FindClose(hFile);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			FileInfo = _T("是不是把硬盘\\U盘\\CD驱动器拖拽进来啦，这样是不行滴!");
			SetButtonFalse();
		}		
		else if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0x10)
		{
			FileInfo = _T("不能对文件夹进行操作!");
			SetButtonFalse();
		}
		else if (FindFileData.nFileSizeLow == 0 && FindFileData.nFileSizeHigh == 0)
		{
			FileInfo = _T("文件大小为0字节，无需操作!");
			SetButtonFalse();
		}
		else
		{
			// 文件名称
			str_FileName = pName;
			FileInfo += str_FileName;
			FileInfo += _T("\r\n");
			CString str_data;
			// 文件大小
			// llFileSize = (FindFileData.nFileSizeHigh << 32) + FindFileData.nFileSizeLow; // 行为未定义，但是运行正常，会首先转换为LONGLONG，然后左移
			llFileSize = FindFileData.nFileSizeHigh;
			llFileSize <<= 32;
			llFileSize += FindFileData.nFileSizeLow;
			str_data.Format(_T("文件大小：%I64d字节\r\n"), llFileSize);
			FileInfo += str_data;
			// 文件创建时间
			// 转化为本地时间，否则会有8小时误差
			FileTimeToLocalFileTime(&FindFileData.ftLastWriteTime, &loctime);
			FileTimeToSystemTime(&loctime, &mysystime);
			str_data.Format(_T("最后修改时间：%d年%d月%d日 %d:%02d:%02d"), mysystime.wYear, mysystime.wMonth, 
				mysystime.wDay, mysystime.wHour, mysystime.wMinute, mysystime.wSecond);
			FileInfo += str_data;
			GetDlgItem(IDC_ENCRYPT)->EnableWindow(TRUE);
			GetDlgItem(IDC_DECRYPT)->EnableWindow(TRUE);
		}
 		delete[] pName;
		pName = NULL;
		DragFinish(hDropInfo);
	}
	else
	{
		FileInfo = _T("本程序只支持单个文件拖拽加密!");
	}	
	SetDlgItemText(IDC_FILE_INFORMATION, FileInfo);
	
	CDialogEx::OnDropFiles(hDropInfo);
}