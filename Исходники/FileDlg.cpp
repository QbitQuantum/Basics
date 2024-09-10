// 初始化文件树和列表
void HsLoadFileTreeList(CFileDlg *cFleDlg)
{

	WCHAR* pDrive = NULL;

	HTREEITEM hRoot;     // 树的根节点的句柄   
	HTREEITEM hDriverItem; // 可表示任一磁盘节点的句柄   
	HTREEITEM hFolderItem;  // 可表示任一目录节点的句柄

	HIMAGELIST hImageListLarge = NULL;
	HIMAGELIST hImageListSmall = NULL;
	Shell_GetImageLists(&hImageListLarge, &hImageListSmall);
	ListView_SetImageList(cFleDlg->m_fileList.m_hWnd, hImageListLarge, LVSIL_NORMAL);
	ListView_SetImageList(cFleDlg->m_fileList.m_hWnd, hImageListSmall, LVSIL_SMALL);


	HsInitDriveList(&cFleDlg->m_fileList);


	cFleDlg->m_fileList.DeleteAllItems();
	cFleDlg->m_dirTree.DeleteAllItems();


	LPITEMIDLIST ppidl = {0};
	SHGetSpecialFolderLocation(NULL,CSIDL_DRIVES,&ppidl);
	//SHGetPathFromIDList(ppidl,TempPath);

	SHFILEINFO	sfi;

	SHGetFileInfoW
		(
		(LPCWSTR)ppidl,
		0, 
		&sfi,
		sizeof(SHFILEINFO), 
		SHGFI_SYSICONINDEX | SHGFI_PIDL 
		);

	hRoot = cFleDlg->m_dirTree.InsertItem(_T("计算机"),sfi.iIcon,sfi.iIcon,0,0);

	GetLogicalDriveStrings(sizeof(DriveString), DriveString);


	pDrive = DriveString;

	CString DriveName;

	WCHAR	FileSystem[MAX_PATH];
	unsigned __int64	HDAmount = 0;
	unsigned __int64	HDFreeSpace = 0;
	unsigned long		AmntMB = 0; // 总大小
	unsigned long		FreeMB = 0; // 剩余空间


	cFleDlg->m_dirTree.Expand(hRoot,TVE_EXPAND);

	for (int i = 0; *pDrive != '\0'; i++, pDrive += lstrlen(pDrive) + 1)
	{
		

		// 得到磁盘相关信息
		memset(FileSystem, 0, sizeof(FileSystem));
		// 得到文件系统信息及大小
		GetVolumeInformation(pDrive, NULL, 0, NULL, NULL, NULL, FileSystem, MAX_PATH);

		int	nFileSystemLen = lstrlen(FileSystem) + 1;
		if (GetDiskFreeSpaceEx(pDrive, (PULARGE_INTEGER)&HDFreeSpace, (PULARGE_INTEGER)&HDAmount, NULL))
		{	
			AmntMB = (ULONG)(HDAmount / 1024 / 1024);
			FreeMB = (ULONG)(HDFreeSpace / 1024 / 1024);
		}
		else
		{
			AmntMB = 0;
			FreeMB = 0;
		}

		//获得磁盘类别
		SHFILEINFO	sfi;
		SHGetFileInfo(pDrive, FILE_ATTRIBUTE_NORMAL, &sfi,sizeof(SHFILEINFO), SHGFI_TYPENAME | SHGFI_USEFILEATTRIBUTES);

		DriveName = sfi.szTypeName;

		DriveName += L" (";
		DriveName += pDrive;

		DriveName.Delete(DriveName.GetLength()-1);

		DriveName += L")";

		

		int icon = GetIconIndex(pDrive,GetFileAttributes(pDrive));

		int	nItem = cFleDlg->m_fileList.InsertItem(i, DriveName, icon);		//插入列表框
		cFleDlg->m_fileList.SetItemData(nItem, (DWORD_PTR)pDrive);

		hDriverItem = cFleDlg->m_dirTree.InsertItem(DriveName,icon,icon,hRoot,0);	//插入树形列表
		cFleDlg->m_dirTree.SetItemData(hDriverItem, (DWORD_PTR)pDrive);

		cFleDlg->m_dirTree.Expand(hRoot,TVE_EXPAND);

		cFleDlg->m_fileList.SetItemText(nItem, 1, sfi.szTypeName);	//插入磁盘类别

		CString	str;
		str.Format(L"%10.1f GB", (float)AmntMB / 1024);
		cFleDlg->m_fileList.SetItemText(nItem, 2, str);
		str.Format(L"%10.1f GB", (float)FreeMB / 1024);
		cFleDlg->m_fileList.SetItemText(nItem, 3, str);
	}
	// 重置本地当前路径

	cFleDlg->m_filePath.ResetContent();




	cFleDlg->m_filePath.SetWindowTextW(L"计算机");

}