	//-------------------------------------------------------------------------
	bool AppScreenBase::handleKeyPress( int keyCode )
	//-------------------------------------------------------------------------
	{
		if ( this != Screen::currentScreen )
		{
			if ( mKeyTimer != NULL )
			{
				Environment::getEnvironment( ).removeTimer( mKeyTimer );
				deleteobject( mKeyTimer );
			}
			return true;
		}

		if ( mSoftKeyBar->handleKeyPress( keyCode ) )
			return true;

		return false;
	}