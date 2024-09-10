int CTreeHandler::Dbg_DumpTree()
{
	HANDLE hfile;
	int ret = 0;
	CTreeElem* rootelem = 0;
	int errcnt = 0;

	hfile = CreateFile( (LPCTSTR)"dbgdump.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,
		FILE_FLAG_SEQUENTIAL_SCAN, NULL );
	if( hfile == INVALID_HANDLE_VALUE ){
		return 1;
	}

	
	rootelem = (*this)( 0 );

	if( rootelem ){
		rootelem->Dbg_DumpReq( hfile, errcnt );
		_ASSERT( !errcnt );
		if( errcnt ){
			DbgOut( "CTreeHandler : Dbg_DumpTree : Dbg_DumpReq error !!!\n" );
			return 1;
		}
	}else{
		DbgOut( "CTreeHandler : Dbg_DumpTree : rootelem error !!!\n" );
		return 1;
	}
	

	FlushFileBuffers( hfile );
	CloseHandle( hfile );
	
	DbgOut( "CTreeHandler : DumpTree : CloseHandle\n" );

	return ret;

}