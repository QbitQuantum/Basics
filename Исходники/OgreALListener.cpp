	void Listener::updateListener()
	{
		update();
		if(mParentNode)
		{
			mPosition = mLastParentPosition;
			mDirection = mLastParentOrientation.zAxis();
			mUp = mLastParentOrientation.yAxis();
		}
		alListener3f(AL_POSITION, mPosition.x, mPosition.y, mPosition.z);
		CheckError(alGetError(), "Failed to set Position");

		mOrientation[0]= -mDirection.x; // Forward.x
		mOrientation[1]= -mDirection.y; // Forward.y
		mOrientation[2]= -mDirection.z; // Forward.z

		mOrientation[3]= mUp.x; // Up.x
		mOrientation[4]= mUp.y; // Up.y
		mOrientation[5]= mUp.z; // Up.z

		alListenerfv(AL_ORIENTATION, mOrientation);
		CheckError(alGetError(), "Failed to set Orientation");
	}