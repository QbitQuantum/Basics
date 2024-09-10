int CRdbIniFile::WriteRdbIniFile( WINPOS* srcwinpos )
{
	m_mode = XMLIO_WRITE;

	MoveMemory( m_winpos, srcwinpos, sizeof( WINPOS ) * WINPOS_MAX );

	WCHAR strpath[MAX_PATH];
	swprintf_s( strpath, MAX_PATH, L"%sOpenRDB.ini", g_mediadir );

	m_hfile = CreateFile( strpath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,
		FILE_FLAG_SEQUENTIAL_SCAN, NULL );
	if( m_hfile == INVALID_HANDLE_VALUE ){
		DbgOut( L"RdbIniFile : WriteRdbIniFile : file open error !!!\n" );
		_ASSERT( 0 );
		return 1;
	}

	CallF( Write2File( "<?xml version=\"1.0\" encoding=\"Shift_JIS\"?>\r\n<RDBINI>\r\n" ), return 1 );  

	int kind;
	for( kind = WINPOS_3D; kind < WINPOS_MAX; kind++ ){
		CallF( Write2File( "  %s\r\n", &(s_wpstart[kind][0]) ), return 1 );

		WINPOS* curwp = m_winpos + kind;
		WINPOS* defwp = m_defaultwp + kind;

		char wline[ 256 ];

		int tmpval;
		if( (curwp->posx >= 0) && (curwp->posx <= 5000) ){
			tmpval = curwp->posx;
		}else{
			tmpval = defwp->posx;
		}
		sprintf_s( wline, 256, "    <posx>%d</posx>\r\n", tmpval );
		CallF( Write2File( wline ), return 1 );

		if( (curwp->posy >= 0) && (curwp->posy <= 5000) ){
			tmpval = curwp->posy;
		}else{
			tmpval = defwp->posy;
		}
		sprintf_s( wline, 256, "    <posy>%d</posy>\r\n", tmpval );
		CallF( Write2File( wline ), return 1 );

		if( (curwp->width >= 100) && (curwp->width <= 2500) ){
			tmpval = curwp->width;
		}else{
			tmpval = defwp->width;
		}
		sprintf_s( wline, 256, "    <width>%d</width>\r\n", tmpval );
		CallF( Write2File( wline ), return 1 );

		if( (curwp->height >= 50) && (curwp->height <= 2500) ){
			tmpval = curwp->height;
		}else{
			tmpval = defwp->height;
		}
		sprintf_s( wline, 256, "    <height>%d</height>\r\n", tmpval );
		CallF( Write2File( wline ), return 1 );

		if( kind != WINPOS_3D ){
			if( (curwp->minwidth >= 90) && (curwp->width <= 1000) ){
				tmpval = curwp->minwidth;
			}else{
				tmpval = defwp->minwidth;
			}
			sprintf_s( wline, 256, "    <minwidth>%d</minwidth>\r\n", tmpval );
			CallF( Write2File( wline ), return 1 );

			if( (curwp->height >= 50) && (curwp->height <= 1000) ){
				tmpval = curwp->minheight;
			}else{
				tmpval = defwp->minheight;
			}
			sprintf_s( wline, 256, "    <minheight>%d</minheight>\r\n", tmpval );
			CallF( Write2File( wline ), return 1 );


			if( (curwp->dispflag == 0) || (curwp->dispflag == 1) ){
				tmpval = curwp->dispflag;
			}else{
				tmpval = 1;
			}
			sprintf_s( wline, 256, "    <dispflag>%d</dispflag>\r\n", tmpval );
			CallF( Write2File( wline ), return 1 );
		}

		CallF( Write2File( "  %s\r\n", &(s_wpend[kind][0]) ), return 1 );
	}

	CallF( Write2File( "</RDBINI>\r\n" ), return 1 );

	return 0;
}