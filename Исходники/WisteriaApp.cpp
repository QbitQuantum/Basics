void WisteriaApp::keyDown( KeyEvent event )
{
	switch( event.getChar() ) {
		case 'p':
			writeImage( getHomeDirectory() + "wisteriaShot.png", copyWindowSurface() );
		break;
	}
}