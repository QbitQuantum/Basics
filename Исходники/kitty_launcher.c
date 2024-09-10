// Procedure de creation de menu à partir d'une clé de registre
HMENU InitLauncherMenu( char * Key ) {
	HMENU menu ;
	menu = CreatePopupMenu() ;
	char KeyName[1024] ;
	int nbitem = 0,i ;
	
	DeleteObject( bmpCheck ) ; bmpCheck = GetMyCheckBitmaps( 1 ) ;
	DeleteObject( bmpUnCheck ) ; bmpUnCheck = GetMyCheckBitmaps( 2 ) ;
	
	if( (IniFileFlag == SAVEMODE_REG)||(IniFileFlag == SAVEMODE_FILE) ) {
		sprintf( KeyName, "%s\\%s", TEXT(PUTTY_REG_POS), Key ) ;
		ReadSpecialMenu( menu, KeyName, &nbitem, 0 ) ;
		}
	else if( IniFileFlag == SAVEMODE_DIR ) {
		ReadSpecialMenu( menu, Key, &nbitem, 0 ) ;
		}

	if( GetMenuItemCount( menu ) > 0 )
		AppendMenu( menu, MF_SEPARATOR, 0, 0 ) ;

	// Creation du menu bouton gauche
	DestroyMenu( HideMenu ) ;
	HideMenu = CreatePopupMenu() ;
	if( !IsUnique ) {
		AppendMenu( HideMenu, MF_ENABLED, IDM_LAUNCHER+3, "&Hide all" ) ;
		AppendMenu( HideMenu, MF_ENABLED, IDM_LAUNCHER+4, "&Unhide all" ) ;
		//AppendMenu( HideMenu, MF_ENABLED, IDM_LAUNCHER+5, "&Refresh list" ) ;
		AppendMenu( HideMenu, MF_ENABLED, IDM_LAUNCHER+6, "&Window unique" ) ;
		CheckMenuItem( HideMenu, IDM_LAUNCHER+6, MF_BYCOMMAND | MF_UNCHECKED) ;
		}	
	else {
		AppendMenu( HideMenu, MF_ENABLED, IDM_LAUNCHER+6, "&Window unique" ) ;
		CheckMenuItem( HideMenu, IDM_LAUNCHER+6, MF_BYCOMMAND | MF_CHECKED) ;
		}
	//AppendMenu( HideMenu, MF_ENABLED, IDM_GONEXT, "&Next" ) ;
	//AppendMenu( HideMenu, MF_ENABLED, IDM_GOPREVIOUS, "&Previous" ) ;
	if( RefreshWinList( MainHwnd ) > 0 ) {
		AppendMenu( HideMenu, MF_SEPARATOR, 0, 0 ) ;
		for( i=0 ; i<NbWin ; i++ ) {
			AppendMenu( HideMenu, MF_ENABLED, IDM_GOHIDE+i, TabWin[i].name ) ;
			SetMenuItemBitmaps ( HideMenu, IDM_GOHIDE+i, MF_BYCOMMAND, bmpUnCheck, bmpCheck ) ;
			if( IsWindowVisible( TabWin[i].hwnd ) ) 
				CheckMenuItem( HideMenu, IDM_GOHIDE+i, MF_BYCOMMAND | MF_CHECKED) ;
			else 
				CheckMenuItem( HideMenu, IDM_GOHIDE+i, MF_BYCOMMAND | MF_UNCHECKED) ;
			}
		}
	AppendMenu( HideMenu, MF_SEPARATOR, 0, 0 ) ;
	AppendMenu( HideMenu, MF_ENABLED, IDM_ABOUT, "&About" ) ;
	AppendMenu( HideMenu, MF_ENABLED, IDM_QUIT, "&Quit" ) ;

	
	AppendMenu( menu, MF_POPUP, (UINT_PTR)HideMenu, "&Opened sessions" ) ;
	AppendMenu( menu, MF_SEPARATOR, 0, 0 ) ;
	
	AppendMenu( menu, MF_ENABLED, IDM_LAUNCHER+7, "&Refresh" ) ;
	AppendMenu( menu, MF_ENABLED, IDM_LAUNCHER+1, "&Configuration" ) ;
	AppendMenu( menu, MF_ENABLED, IDM_LAUNCHER+2, "&TTY-ed" ) ;
	AppendMenu( menu, MF_SEPARATOR, 0, 0 ) ;
	AppendMenu( menu, MF_ENABLED, IDM_ABOUT, "&About" ) ;
	AppendMenu( menu, MF_ENABLED, IDM_QUIT, "&Quit" ) ;

	return menu ;
	}