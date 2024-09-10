void box2d_basicApp::keyDown( KeyEvent event )
{
#if defined( CINDER_COCOA )
    bool isModDown = event.isMetaDown();
#else // windows
    bool isModDown = event.isControlDown();
#endif
    if (isModDown) {
		if( event.getChar() == 'n' ) {
			new_game();
        }
		return;
	}
    if (event.getCode() == KeyEvent::KEY_ESCAPE || event.getChar() == 'q') {
        // ask confirm
		quit();
		return;
	}
	if (stat_ != stat::normal) {
        if (stat_ == stat::over) {
            if (microsec_clock::local_time() - M.td_ > seconds(3)) {
                new_game();
            }
		} else if (stat_ == stat::pause) {
			if (event.getCode() == KeyEvent::KEY_SPACE) {
				pause();
			}
		}
		return;
    }
	if (event.getCode() == KeyEvent::KEY_SPACE) {
		pause();
		return;
	}
    if (event.getCode() == KeyEvent::KEY_UP) {
		M.rotate();
		play_sound( "rotate.wav" );
    } else if (event.getCode() == KeyEvent::KEY_LEFT) {
		M.Move(-1);
    } else if (event.getCode() == KeyEvent::KEY_RIGHT) {
		M.Move(1);
    } else if (event.getCode() == KeyEvent::KEY_DOWN) {
        move_down(1);
	}
}