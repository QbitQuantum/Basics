void CSampleList::LoadSampleFiles( )
{
	TCHAR szCurrDir [ MAX_PATH ];
	GetCurrentDirectory ( MAX_PATH, szCurrDir );
	SetCurrentDirectory( theApp.m_szDirectory );
	SetCurrentDirectory( theApp.m_szLanguagePath );
	SetCurrentDirectory( _T("helpwizard\\samples") );
	
	CString	strPath, strPattern;
	CFile	ImgFile;	
		
	HANDLE					hFind = NULL;
	WIN32_FIND_DATA			FindFileData;
	CString					FileNames [ 256 ];
	int iIndex = 0;
	BOOL bRC = TRUE;

	//strPath = "Files\\languagebank\\english\\helpwizard\\samples\\";

	
	hFind = ::FindFirstFile( /*strPath + */_T("*.*"), &FindFileData );
	if ( hFind == INVALID_HANDLE_VALUE ) 
	{
		MessageBox( GetLanguageData( _T("Getting Started"), _T("NoSampleFolder") ) );
		return;
	}

	/////////////////
	this->DeleteAllItems ( );

	//m_Images.DeleteImageList ( );
	//m_Images.Create     ( 64, 64, ILC_COLOR32 | ILC_MASK, 1, 16 );

	m_Images.DeleteImageList ( );
	m_Images.Create     ( 64, 64, ILC_COLOR32 | ILC_MASK, 1, 16 );
	//m_Images.SetBkColor ( RGB ( 255, 255, 255 ) );

	this->SetImageList   ( &m_Images, LVSIL_NORMAL );
	this->SetItemCount   ( 64 );

	CBitmap bmp;
	bmp.LoadBitmap( IDB_SAMPLE_IMAGE );
	m_Images.Add( &bmp, (CBitmap*)NULL );
	/////////////////

	int iItemCount = 0;
	int iImageCount = 1;

	do
	{
		TCHAR lwFilename [ 260 ];
		_tcscpy_s( lwFilename, 260, FindFileData.cFileName );
		_tcstolower( lwFilename );

		if ( _tcscmp( FindFileData.cFileName, _T(".") ) && _tcscmp( FindFileData.cFileName, _T("..") ) 
				&& !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
		{
			TCHAR* szExt = _tcsrchr( lwFilename, _T('.') );
			if ( !szExt ) continue;

			if ( _tcscmp( szExt, _T(".fpm") ) == 0 )
			{
				TCHAR szFile [ 260 ];
				_tcsncpy_s( szFile, 260, lwFilename, (DWORD)( szExt - lwFilename ) );
				_tcscat_s( szFile, 260, _T(".bmp") );

				CImage image;
				if ( FAILED( image.Load( szFile ) ) )
				{
					//MessageBox( "Could not find video image" );
					InsertItem( iItemCount++, FindFileData.cFileName, 0 );
				}
				else
				{
					CWindowDC wndDC( this );
					CDC dc;
					dc.CreateCompatibleDC( &wndDC );

					CBitmap bmpCurrImage;
					bmpCurrImage.CreateBitmap( 64,64, 1, 32, NULL );
					CBitmap *oldBmp = dc.SelectObject( &bmpCurrImage );

					::SetStretchBltMode( image.GetDC(), HALFTONE );
					::SetBrushOrgEx( image.GetDC(), 0,0, NULL );
					image.StretchBlt( dc.GetSafeHdc( ), 0,0, 64,64 );
					dc.SelectObject( oldBmp );
					m_Images.Add( &bmpCurrImage, (CBitmap*)NULL );

					bmpCurrImage.DeleteObject();

					image.ReleaseDC();
					image.ReleaseDC();

					InsertItem( iItemCount++, FindFileData.cFileName, iImageCount++ );
				}
			}
		}
	} while ( ::FindNextFile(hFind, &FindFileData) );

	::FindClose ( hFind );

	if ( iItemCount == 0 )
	{
		InsertItem( 0, GetLanguageData( _T("Getting Started"), _T("NoSample") ), -1 );
	}

	SetCurrentDirectory( szCurrDir );
}