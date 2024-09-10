BOOL CDownloadDlg::OnInitDialog()
{
	CSkinDialog::OnInitDialog();

	SkinMe( NULL, IDR_DOWNLOADSFRAME );

	if ( OpenClipboard() )
	{
		if ( HGLOBAL hData = GetClipboardData( CF_UNICODETEXT ) )
		{
			size_t nData = GlobalSize( hData );
			LPVOID pData = GlobalLock( hData );

			LPTSTR pszData = m_sURL.GetBuffer( (int)( nData + 1 ) / 2 + 1 );
			CopyMemory( pszData, pData, nData );
			pszData[ ( nData + 1 ) / 2 ] = 0;
			m_sURL.ReleaseBuffer();
			GlobalUnlock( hData );
		}

		CloseClipboard();
	}

	m_sURL.Trim( _T(" \t\r\n") );

	CShareazaURL pURL;
	if ( !pURL.Parse( m_sURL, m_pURLs ) )
		m_sURL.Empty();

	UpdateData( FALSE );
	OnChangeURL();

	return TRUE;
}