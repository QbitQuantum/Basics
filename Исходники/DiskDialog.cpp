LRESULT DiskDialog::chooseDir(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	BROWSEINFO bi = { 0 };
    bi.lpszTitle = "Directory to Monitor...";
	bi.hwndOwner = m_hWnd;
    LPITEMIDLIST pidl = SHBrowseForFolder ( &bi );
    if ( pidl != 0 )
    {
        // get the name of the folder
        TCHAR path[MAX_PATH];
        SHGetPathFromIDList ( pidl, path );
		SetDlgItemText(IDC_DIRECTORY, path);
		pMeter->put_Path(_bstr_t(path));

        // free memory used
        IMalloc * imalloc = 0;
        if ( SUCCEEDED( SHGetMalloc ( &imalloc )) )
        {
            imalloc->Free ( pidl );
            imalloc->Release ( );
        }

		return S_OK;
	}

	return S_OK;
}