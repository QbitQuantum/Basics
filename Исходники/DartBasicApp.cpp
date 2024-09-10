void DartBasicApp::keyDown( KeyEvent event )
{
	if( event.getChar() == 'r' ) {
		CI_LOG_V( "reload." );
		loadScript();
	}
}