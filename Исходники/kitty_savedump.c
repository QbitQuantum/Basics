void PrintWindowSettings( FILE * fp ) {
	int ret ;
	RECT r ;
	char buffer[MAX_VALUE_NAME] ;
	
	GetOSInfo( buffer ) ;
	fprintf( fp, "OSVersion=%s\n", buffer ) ;
	
	ret = GetWindowText( MainHwnd, buffer, MAX_VALUE_NAME ) ; buffer[ret]='\0';
	ret = GetWindowTextLength( MainHwnd ) ;
	fprintf( fp, "Title (length)=%s (%d)\n", buffer, ret ) ;
	if( GetWindowRect( MainHwnd, &r ) ) {
		fprintf( fp, "WindowRect.left=%ld\n", r.left ) ;
		fprintf( fp, "WindowRect.right=%ld\n", r.right ) ;
		fprintf( fp, "WindowRect.top=%ld\n", r.top ) ;
		fprintf( fp, "WindowRect.bottom=%ld\n", r.bottom ) ;
		}
	if( GetClientRect( MainHwnd, &r ) ) {
		fprintf( fp, "ClientRect.left=%ld\n", r.left ) ;
		fprintf( fp, "ClientRect.right=%ld\n", r.right ) ;
		fprintf( fp, "ClientRect.top=%ld\n", r.top ) ;
		fprintf( fp, "ClientRect.bottom=%ld\n", r.bottom ) ;
		}
	
	ret = GetWindowModuleFileName( MainHwnd, buffer, MAX_VALUE_NAME ) ; buffer[ret]='\0';
	fprintf( fp, "WindowModuleFileName=%s\n", buffer ) ;
	
	WINDOWINFO wi ;
	wi.cbSize = sizeof( WINDOWINFO ) ;
	if( GetWindowInfo( MainHwnd, &wi ) ) {
		fprintf( fp, "WindowInfo.cbSize=%lu\n", wi.cbSize ) ;
		fprintf( fp, "WindowInfo.rcWindow.left=%ld\n", wi.rcWindow.left ) ;
		fprintf( fp, "WindowInfo.rcWindow.right=%ld\n", wi.rcWindow.right ) ;
		fprintf( fp, "WindowInfo.rcWindow.top=%ld\n", wi.rcWindow.top ) ;
		fprintf( fp, "WindowInfo.rcWindow.bottom=%ld\n", wi.rcWindow.bottom ) ;
		fprintf( fp, "WindowInfo.rcClient.left=%ld\n", wi.rcWindow.left ) ;
		fprintf( fp, "WindowInfo.rcClient.right=%ld\n", wi.rcWindow.right ) ;
		fprintf( fp, "WindowInfo.rcClient.top=%ld\n", wi.rcWindow.top ) ;
		fprintf( fp, "WindowInfo.rcClient.bottom=%ld\n", wi.rcWindow.bottom ) ;
		fprintf( fp, "WindowInfo.dwStyle=%lu\n", wi.dwStyle ) ;
		fprintf( fp, "WindowInfo.dwExStyle=%lu\n", wi.dwExStyle ) ;
		fprintf( fp, "WindowInfo.dwWindowStatus=%lu\n", wi.dwWindowStatus ) ;
		fprintf( fp, "WindowInfo.cxWindowBorders=%u\n", wi.cxWindowBorders ) ;
		fprintf( fp, "WindowInfo.cyWindowBorders=%u\n", wi.cyWindowBorders ) ;
		fprintf( fp, "WindowInfo.wCreatorVersion=%d\n", wi.wCreatorVersion ) ;
		}
	
	WINDOWPLACEMENT wp;
	wp.length=sizeof(WINDOWPLACEMENT) ;
	if( GetWindowPlacement( MainHwnd, &wp ) ) {
		fprintf( fp, "WindowPlacement.length=%u\n", wp.length ) ;
		fprintf( fp, "WindowPlacement.flags=%u\n", wp.flags ) ;
		fprintf( fp, "WindowPlacement.showCmd=%u\n", wp.showCmd ) ;
		fprintf( fp, "WindowPlacement.ptMinPosition.x=%ld\n", wp.ptMinPosition.x ) ;
		fprintf( fp, "WindowPlacement.ptMinPosition.y=%ld\n", wp.ptMinPosition.y ) ;
		fprintf( fp, "WindowPlacement.ptMaxPosition.x=%ld\n", wp.ptMaxPosition.x ) ;
		fprintf( fp, "WindowPlacement.ptMaxPosition.y=%ld\n", wp.ptMaxPosition.y ) ;
		fprintf( fp, "WindowPlacement.rcNormalPosition.left=%ld\n", wp.rcNormalPosition.left ) ;
		fprintf( fp, "WindowPlacement.rcNormalPosition.right=%ld\n", wp.rcNormalPosition.right ) ;
		fprintf( fp, "WindowPlacement.rcNormalPosition.top=%ld\n", wp.rcNormalPosition.top ) ;
		fprintf( fp, "WindowPlacement.rcNormalPosition.bottom=%ld\n", wp.rcNormalPosition.bottom ) ;
		}
	
	fprintf( fp, "IsIconic=%d\n", IsIconic( MainHwnd ) ) ;
	fprintf( fp, "IsWindow=%d\n", IsWindow( MainHwnd ) ) ;
	fprintf( fp, "IsWindowUnicode=%d\n", IsWindowUnicode( MainHwnd ) ) ;
	fprintf( fp, "IsWindowVisible=%d\n", IsWindowVisible( MainHwnd ) ) ;
	fprintf( fp, "IsZoomed=%d\n", IsZoomed( MainHwnd ) ) ;
	}