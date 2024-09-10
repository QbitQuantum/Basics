BBString *bbSystemRequestDir( BBString *text,BBString *dir ){

	BBString *str=&bbEmptyString;

	if( _usew ){
		LPMALLOC shm;
		ITEMIDLIST *idlist;
		BROWSEINFOW bi={0};
		wchar_t buf[MAX_PATH],*p;

		GetFullPathNameW( bbTmpWString(dir),MAX_PATH,buf,&p );
		
		bi.hwndOwner=GetActiveWindow();
		bi.lpszTitle=bbTmpWString( text );
		bi.ulFlags=BIF_RETURNONLYFSDIRS|BIF_NEWDIALOGSTYLE;
		bi.lpfn=BrowseForFolderCallbackW;
		bi.lParam=(LPARAM)buf;
		
		beginPanel();
		idlist=SHBrowseForFolderW(&bi);
		endPanel();
		
		if( idlist ){
			SHGetPathFromIDListW( idlist,buf );
			str=bbStringFromWString( buf );
			//SHFree( idlist );	//?!?	
		}
	} else {
		LPMALLOC shm;
		ITEMIDLIST *idlist;
		BROWSEINFOA bi={0};
		char buf[MAX_PATH],*p;
		
		GetFullPathNameA( bbTmpCString(dir),MAX_PATH,buf,&p );

		bi.hwndOwner=GetActiveWindow();
		bi.lpszTitle=bbTmpCString( text );
		bi.ulFlags=BIF_RETURNONLYFSDIRS|BIF_NEWDIALOGSTYLE;
		bi.lpfn=BrowseForFolderCallbackA;
		bi.lParam=(LPARAM)buf;
		
		beginPanel();
		idlist=SHBrowseForFolderA(&bi);
		endPanel();
		
		if( idlist ){
			SHGetPathFromIDListA( idlist,buf );
			str=bbStringFromCString( buf );
			//SHFree( idlist );	//?!?	
		}
	}
	return str;
}