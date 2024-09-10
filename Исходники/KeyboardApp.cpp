void KeyboardApp::keyUp( KeyEvent event )
{
	switch(event.getChar())
	{
	case 'w':
		KEY_W =false;
		break;
	case 's':
		KEY_S = false;
		break;
	case 'a':
		KEY_A = false;
		break;
	case 'd':
		KEY_D = false;
		break;
	}
	switch(event.getCode())
	{
	case KeyEvent::KEY_UP:
		KEY_UP = false;
	case 276:
		KEY_LEFT = false;
		break;
	case KeyEvent::KEY_RIGHT:
		KEY_RIGHT = false;
		break;
	case KeyEvent::KEY_SPACE:
		KEY_SPACE = false;
		break;
	}
}