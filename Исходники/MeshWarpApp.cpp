	void keyUp( KeyEvent event )
	{
		if (event.getChar() == 'd') {
			mIsShowCtrlMesh = (!mIsShowCtrlMesh);
		}

		if (event.getCode() == KeyEvent::KEY_F1) { mScale = 1.0; }
	}