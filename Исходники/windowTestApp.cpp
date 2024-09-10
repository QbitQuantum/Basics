void WindowTestApp::keyDown( KeyEvent event )
{
	if( event.getChar() == 'f' )
		setFullScreen( ! isFullScreen() );
	else if( event.getChar() == 't' )
		setAlwaysOnTop( ! isAlwaysOnTop() );
	else if( event.getChar() == 'b' )
		setBorderless( ! isBorderless() );
	else if( event.getCode() == KeyEvent::KEY_LEFT )
		setWindowPos( getWindowPos() + Vec2i( -1, 0 ) );
	else if( event.getCode() == KeyEvent::KEY_RIGHT )
		setWindowPos( getWindowPos() + Vec2i( 1, 0 ) );
	else if( event.getCode() == KeyEvent::KEY_UP )
		setWindowPos( getWindowPos() + Vec2i( 0, -1 ) );
	else if( event.getCode() == KeyEvent::KEY_DOWN )
		setWindowPos( getWindowPos() + Vec2i( 0, 1 ) );
}