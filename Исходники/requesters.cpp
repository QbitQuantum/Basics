bbString bbRequesters::RequestDir( bbString title,bbString dir ){

	CoInitialize( 0 );
	
	dir=dir.replace( "/","\\" );

	LPMALLOC shm;
	BROWSEINFOW bi={0};
	
	WCHAR buf[MAX_PATH],*p;
	GetFullPathNameW( dir.toWString(),MAX_PATH,buf,&p );
	
	bi.hwndOwner=GetActiveWindow();
	bi.lpszTitle=tmpWString( title );
	bi.ulFlags=BIF_RETURNONLYFSDIRS|BIF_NEWDIALOGSTYLE;
	bi.lpfn=BrowseForFolderCallbackW;
	bi.lParam=(LPARAM)buf;
	
	beginPanel();

	bbString str;
	
	if( ITEMIDLIST *idlist=SHBrowseForFolderW( &bi ) ){
		SHGetPathFromIDListW( idlist,buf );
		str=bbString( buf );
		//SHFree( idlist );	//?!?
	}
	
	endPanel();
	
	free( (void*)bi.lpszTitle );

	str=str.replace( "\\","/" );
	if( !str.endsWith( "/" ) ) str+="/";

	return str;
}