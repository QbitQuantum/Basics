void CMediaWnd::OnDropFiles(HDROP hDropInfo)
{
	if ( hDropInfo != NULL )
	{
		CStringList oFileList;
		TCHAR szFileName[MAX_PATH + 1];
		UINT nFiles = DragQueryFile( hDropInfo, (UINT)-1, NULL, 0 );
		for( UINT nNames = 0; nNames < nFiles; nNames++ )
		{
			ZeroMemory( szFileName, MAX_PATH + 1 );
			DragQueryFile( hDropInfo, nNames, (LPTSTR)szFileName, MAX_PATH + 1 );
	        oFileList.AddTail( szFileName ); 
		}
		CPoint oPoint;
		POINT pt;
		DragQueryPoint( hDropInfo, &pt );
		oPoint.SetPoint( pt.x, pt.y );

		OnDropFiles( oFileList, oPoint, TRUE );
	}
}