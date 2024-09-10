void CBrowseForFolder::GetPidl(CString name, LPITEMIDLIST pidl)
{
	LPSHELLFOLDER pshf;
	ULONG chEaten;
	
#ifdef _UNICODE
	OLECHAR* oleRoot = name.GetBuffer(name.GetLength());
#else
	OLECHAR oleRoot[MAX_PATH];
	// convert path to Unicode string
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, name, -1,
		oleRoot, MAX_PATH);
#endif	
	if (SUCCEEDED(SHGetDesktopFolder(&pshf)))
	{
		// get pidl
		pshf->ParseDisplayName(hWndOwner, NULL, oleRoot, &chEaten, 
			&pidl, NULL);
	}
	else return;
	pshf->Release();
}