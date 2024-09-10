void CSnapperOptions::OnBnClickedBrowseNotebook()
{
	BROWSEINFO sBi = { 0 };
	/*
    sBi.lpszTitle = TEXT("Select Notebook(s)");
	sBi.hwndOwner = m_hWndTop;
	sBi.iImage = 
	*/
    LPITEMIDLIST pIdl = SHBrowseForFolder ( &sBi );
    if ( pIdl != NULL )
    {
        // get the name of the folder
        TCHAR pszNotebookPath[MAX_PATH];
        if ( SHGetPathFromIDList ( pIdl, pszNotebookPath ) )
        {
			m_strNotebookPath = pszNotebookPath;
			m_bUpdateHotlists = TRUE;
			UpdateData(FALSE);
        }

        // free memory 
        IMalloc * piMalloc = NULL;
        if ( SUCCEEDED( SHGetMalloc ( &piMalloc )) )
        {
            piMalloc->Free ( pIdl );
            piMalloc->Release ( );
        }

    }
	
}