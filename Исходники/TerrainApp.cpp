void TerrainApp::keyDown( KeyEvent event )
{
	switch ( event.getChar() ) {
		case ' ':	mRoom.togglePower();
					mSpringCam.setPreset( 1 );	break;
		case 'f':	mRd.mParamF += 0.001f;		break;
		case 'F':	mRd.mParamF -= 0.001f;		break;
		case 'k':	mRd.mParamK += 0.001f;		break;
		case 'K':	mRd.mParamK -= 0.001f;		break;
		case 'n':	mRd.mParamN += 0.005f;		break;
		case 'N':	mRd.mParamN -= 0.005f;		break;
		case 'w':	mRd.mParamWind += 0.05f;	break;
		case 'W':	mRd.mParamWind -= 0.05f;	break;
		case '.':	mTerrainScale.x += 0.1f;	break;
		case ',':	mTerrainScale.x -= 0.1f;	break;
		case '1':	mRd.setMode(1);				break;
		case '2':	mRd.setMode(2);				break;
		case '3':	mRd.setMode(3);				break;
		case 'c':	mSpringCam.setPreset( 0 );	break;
		case 'C':	mSpringCam.setPreset( 2 );	break;
		default:								break;
	}
	
	switch( event.getCode() ){
		case KeyEvent::KEY_UP:		mMouseRightPos = Vec2f( 222.0f, 205.0f ) + getWindowCenter();	break;
		case KeyEvent::KEY_LEFT:	mMouseRightPos = Vec2f(-128.0f,-178.0f ) + getWindowCenter();	break;
		case KeyEvent::KEY_RIGHT:	mMouseRightPos = Vec2f(-256.0f, 122.0f ) + getWindowCenter();	break;
		case KeyEvent::KEY_DOWN:	mMouseRightPos = Vec2f(   0.0f,   0.0f ) + getWindowCenter();	break;
		default: break;
	}
	
	std::cout << "F: " << mRd.mParamF << " K: " << mRd.mParamK << std::endl;
}