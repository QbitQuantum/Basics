LRESULT AppImplMswScreenSaver::eventHandler( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message ) {
		case WM_TIMER:
			mApp->getRenderer()->startDraw();
			mApp->privateUpdate__();
			mApp->privateDraw__();
			mApp->getRenderer()->finishDraw();
			return 0;
		break;
		case WM_DESTROY:
			mApp->getRenderer()->kill();
			::KillTimer( mWnd, TIMER_ID );
			::ReleaseDC( mWnd, mDC );
			return 0;
		break;
		default:
			return DefScreenSaverProc( hWnd, message, wParam, lParam );		
	}
}