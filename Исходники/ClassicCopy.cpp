void CClassicCopyFile::GetFileInfo( IAccessible *pAcc, bool bSrc )
{
	long count;
	pAcc->get_accChildCount(&count);
	CComVariant children[20];
	AccessibleChildren(pAcc,0,count,children,&count);

	wchar_t fname[_MAX_PATH]=L"";
	wchar_t dir[_MAX_PATH]=L"";
	CString size;
	CString date;

	// get the file name, directory, size and date
	for (int i=0;i<count;i++)
	{
		CComBSTR name;
		if (children[i].vt==VT_DISPATCH)
		{
			CComQIPtr<IAccessible> pChild=children[i].pdispVal;
			if (pChild)
				pChild->get_accName(CComVariant(CHILDID_SELF),&name);
		}
		else
		{
			pAcc->get_accName(children[i],&name);
		}
		switch (i)
		{
			case 2: if (wcslen(name)<_countof(fname)) wcscpy_s(fname,name); break;
			case 3: if (wcslen(name)<_countof(dir)) wcscpy_s(dir,name); break;
			case 4: size=name; break;
			case 5: date=name; break;
		}
	}

	if (bSrc)
	{
		m_FileName=fname;
		m_SrcSize=size;
		m_SrcTime=date;
	}
	else
	{
		m_DstSize=size;
		m_DstTime=date;
	}

	if (!fname[0] || !dir[0]) return;

	wchar_t fname2[_MAX_PATH];
	memcpy(fname2,fname,sizeof(fname2));
	*PathFindExtension(fname2)=0;

	int len1=Strlen(fname2);
	// the directory text is something like "filename (directory)". we need to parse out the real directory name
	int len2=Strlen(dir);
	if (dir[0]==0x202A) len1++; // for RTL languages the first character is some RTL marker. needs to be skipped
	if (len1+1>=len2 || dir[len1]!=L' ' || dir[len1+1]!=L'(' || dir[len2-1]!=L')') return;
	dir[len2-1]=0;

	// construct the full file name
	wchar_t path[_MAX_PATH];
	_wmakepath_s(path,NULL,dir+len1+2,fname,NULL);

	if (!bSrc)
	{
		DWORD attrib=GetFileAttributes(path);
		if (attrib!=INVALID_FILE_ATTRIBUTES)
		{
			if (attrib&FILE_ATTRIBUTE_READONLY) m_bReadOnly=true;
			if (attrib&FILE_ATTRIBUTE_SYSTEM) m_bSystem=true;
		}
	}

	// get file icon
	HICON hIcon=NULL;
	PIDLIST_ABSOLUTE pidl=NULL;
	if (SUCCEEDED(SHParseDisplayName(path,NULL,&pidl,0,NULL)) && pidl)
	{
		int iconSize=GetSystemMetrics(SM_CXICON);
		HBITMAP hBitmap=NULL;
		CComPtr<IShellItemImageFactory> pFactory;
		if (SUCCEEDED(SHCreateItemFromIDList(pidl,IID_IShellItemImageFactory,(void**)&pFactory)) && pFactory)
		{
			SIZE size={iconSize,iconSize};
			if (FAILED(pFactory->GetImage(size,SIIGBF_ICONONLY,&hBitmap)))
				hBitmap=NULL;
		}

		ILFree(pidl);
		if (hBitmap)
		{
			HBITMAP hMonoBitmap=CreateBitmap(iconSize,iconSize,1,1,NULL);
			ICONINFO info={TRUE,0,0,hMonoBitmap,hBitmap};
			hIcon=CreateIconIndirect(&info);
			DeleteObject(hMonoBitmap);
			DeleteObject(hBitmap);
		}
	}
	if (!hIcon) return;

	if (bSrc)
		m_SrcIcon=hIcon;
	else
		m_DstIcon=hIcon;
}