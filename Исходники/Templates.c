static void CALLCONV FillTreeCtrl(HWND hTreeCtrl, LPCWSTR szPath, HTREEITEM hRoot)
{
	SIZE_T i, nPathLen = lstrlenW(szPath);
	WIN32_FIND_DATAW fd;
	HANDLE hFind;
	LPWSTR szMask = PLUGIN_ALLOC(MAX_PATH*sizeof(WCHAR));
	if(!szMask) return;
	lstrcpyW(szMask,szPath);
	lstrcatW(szMask,L"\\");
	lstrcatW(szMask,TEMPLATES_MASK);
	hFind = FindFirstFileW(szMask,&fd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		LPWSTR szItem = PLUGIN_ALLOC(MAX_PATH*sizeof(szItem));
		LPCWSTR p = szPath;
		UINT_PTR tail = 0;
		SHFILEINFOW sfi,sfis;
		while(*p){ szItem[tail] = *p++;tail++;};
		szItem[tail]=L'\\';tail++;
		do
		{
			if(fd.cFileName[0] != L'.')
			{
				i=0;
				while(fd.cFileName[i]) {szItem[tail+i]=fd.cFileName[i];i++;}
				szItem[tail+i]=0;
				SHGetFileInfoW(szItem,0,&sfi,sizeof(sfi),SHGFI_SYSICONINDEX|SHGFI_SMALLICON|SHGFI_OPENICON);
				SHGetFileInfoW(szItem,0,&sfis,sizeof(sfis),SHGFI_SYSICONINDEX|SHGFI_SMALLICON|SHGFI_OPENICON);
				if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					TVINSERTSTRUCTW tvi;
					HTREEITEM hNode=NULL;
					WCHAR szChild[MAX_PATH],szLabel[MAX_PATH];
					p = fd.cFileName;
					tvi.hParent = hRoot;
					tvi.hInsertAfter = TVI_LAST;
					szLabel[0]=L'[';
					i=0;
					while(*p) {szLabel[1+i]=*p++;i++;}
					szLabel[1+i]=L']';
					szLabel[1+i+1]=0;
					tvi.item.pszText = szLabel;
					tvi.item.cchTextMax = MAX_PATH;
					tvi.item.lParam = TVNT_DIR;
					tvi.item.iImage = sfi.iIcon;
					tvi.item.iSelectedImage = sfis.iIcon;
					tvi.item.mask = TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
					hNode = TreeView_InsertItem(hTreeCtrl,&tvi);
					//! Что-бы не "оптимизировало" в вызов memcpy пришлось установить опцию
					//! компилятора "Inline Function Expansion" в /Ob1
					//! На значение по-умолчанию "Default" в Win32 всё нормально, в x64 - вылазит memcpy
					xmemcpy(szChild,szPath,nPathLen*sizeof(WCHAR));
					i = nPathLen;
					szChild[i]=L'\\'; i++;
					p = fd.cFileName;
					while(*p) {szChild[i]=*p++;i++;}
					szChild[i]=0;
					FillTreeCtrl(hTreeCtrl,szChild,hNode);
					TreeView_SortChildren(hTreeCtrl,hNode,FALSE);
					TreeView_Expand(hTreeCtrl,hNode,TVE_EXPAND);
				}
				else
				{
					TVINSERTSTRUCTW tvi;
					tvi.hParent = hRoot;
					tvi.hInsertAfter = TVI_LAST;
					tvi.item.pszText = fd.cFileName;
					tvi.item.cchTextMax = MAX_PATH;
					tvi.item.lParam = TVNT_FILE;
					tvi.item.iImage = sfi.iIcon;
					tvi.item.iSelectedImage = sfis.iIcon;
					tvi.item.mask = TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
					TreeView_InsertItem(hTreeCtrl,&tvi);
				}
			}
		}
		while(FindNextFileW(hFind, &fd));
		FindClose(hFind);
		PLUGIN_FREE(szItem);
	}
	PLUGIN_FREE(szMask);
}