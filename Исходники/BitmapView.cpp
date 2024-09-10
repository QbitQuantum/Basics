int CBitmapView::LoadPicture(CString &filePath)
{
	CFile file;
	if( !file.Open( filePath, CFile::modeRead) )
		return -1;

	DWORD    m_nFileLen;
	m_nFileLen = file.GetLength();

	HGLOBAL hMem = ::GlobalAlloc( GMEM_MOVEABLE, m_nFileLen );
	LPVOID lpBuf = ::GlobalLock( hMem );
	if( file.Read( lpBuf, m_nFileLen ) != m_nFileLen )
	{
		file.Close();
		return -2;
	}
	file.Close();

	::GlobalUnlock( hMem );

	if ( CreateStreamOnHGlobal( hMem, TRUE, &pStream ) !=S_OK )     
		return -3;

	if ( OleLoadPicture( pStream, m_nFileLen, TRUE, IID_IPicture, ( LPVOID * )&pPicture ) !=S_OK )
		return -4;

	Invalidate();
	return 1;
}