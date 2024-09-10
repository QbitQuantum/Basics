LRESULT Win32DDFullScreen::wndProc( HWND hwnd,UINT msg,WPARAM wp,LPARAM lp,WNDPROC proc ){
	switch( msg ){
	case WM_PAINT:
		if( _excl!=this ){

		}else if( IsIconic(_hwnd.hwnd()) ){

		}else if( !primarySurface() ){

			//restore primary surface
			if( !_graphics->restore() ){
				//Argh! Don't work if an 'owned' window is active!!!!!
				break;
			}

			//create clipper
			if( _flags & BBScreen::SCREEN_GUICOMPATIBLE ){
				if( _clipper ){ _clipper->Release();_clipper=0; }
				if( win32DD.directDraw()->CreateClipper(0,&_clipper,0)<0 ){
					bbError( "Failed to create DD clipper" );
				}
				_clipper->SetHWnd( 0,_hwnd.hwnd() );
			}

			//fix gamma
//			updateGamma( false );

		}else if( _flags & BBScreen::SCREEN_GUICOMPATIBLE ){

			flip(false);
		}
		ValidateRect(hwnd,0);
		return 0;
	case WM_ERASEBKGND:
		return 1;
	}
	return Win32DDScreen::wndProc( hwnd,msg,wp,lp,proc );
}