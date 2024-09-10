void SetCertDirDlg::OnBnClickedButton1()
{
	LPMALLOC pMalloc;
    
    if( SUCCEEDED( SHGetMalloc( &pMalloc ) ) ) 
    {
        TCHAR szTitle[] = _T("Choose Directory for storing certificates.");
        BROWSEINFO bi;
        ZeroMemory( &bi, sizeof( bi ) );
        bi.hwndOwner = NULL;
        bi.pszDisplayName = NULL;
        bi.lpszTitle = szTitle;
        bi.pidlRoot = NULL;
		bi.ulFlags = BIF_RETURNONLYFSDIRS;
        
        LPITEMIDLIST pidl = SHBrowseForFolder( &bi );
        if( pidl ) 
        {
            TCHAR szDir[MAX_PATH];
            if( SHGetPathFromIDList( pidl, szDir ) ) 
            {
				m_CertificatePath.SetWindowText(szDir);
				m_CertificatePath.SetFocus();
            }
            pMalloc->Free(pidl); 
            pMalloc->Release();
        }
    }
}