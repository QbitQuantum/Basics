STDMETHODIMP CShareOverlay::IsMemberOf( LPCWSTR pwszPath, DWORD dwAttrib )
{
	// must use IShellFolder::GetAttributesOf to get the correct attributes instead of SHGetFileInfo or IShellFolder::ParseDisplayName
	// SHGetFileInfo gives the wrong result for some system folders like %userprofile%\Desktop (on Windows7 and Vista)
	// IShellFolder::ParseDisplayName returns the wrong attributes for the contents of the Recycle Bin (on Windows7 only)
	PIDLIST_ABSOLUTE pidl=NULL;
	HRESULT res=S_FALSE;
	if (pwszPath && m_pDesktop)
	{
		if (SUCCEEDED(m_pDesktop->ParseDisplayName(NULL,NULL,(LPWSTR)pwszPath,NULL,(PIDLIST_RELATIVE*)&pidl,NULL)))
		{
			CComPtr<IShellFolder> pFolder;
			PCUITEMID_CHILD child;
			if (SUCCEEDED(SHBindToParent(pidl,IID_IShellFolder,(void**)&pFolder,&child)))
			{
				ULONG attrib=SFGAO_SHARE;
				if (SUCCEEDED(pFolder->GetAttributesOf(1,&child,&attrib)) && (attrib&SFGAO_SHARE))
					res=S_OK;
			}
			ILFree(pidl);
		}
	}
	return res;
}