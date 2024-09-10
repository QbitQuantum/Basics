void BulletSpheresApp::keyDown( KeyEvent event )
{
	switch( event.getChar() ){
		case 'f': setFullScreen( ! isFullScreen() );	break;
		case 'd': mContext->toggleDebugDraw();			break;
		default : break;
	}
}