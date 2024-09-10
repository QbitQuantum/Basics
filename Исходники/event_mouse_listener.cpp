const NLMISC::CMatrix& CEvent3dMouseListener::getViewMatrix ()
{
	// Mode first person ?
	if (_MouseMode==firstPerson)
	{
		// CVector
		CVector dir (0,0,0);
		bool find=false;

		// Key pushed ?
		if (_AsyncListener.isKeyDown (KeyUP))
		{
			dir+=CVector (0, 1, 0);
			find=true;
		}
		if (_AsyncListener.isKeyDown (KeyDOWN))
		{
			dir+=CVector (0, -1, 0);
			find=true;
		}
		if (_AsyncListener.isKeyDown (KeyRIGHT))
		{
			dir+=CVector (1, 0, 0);
			find=true;
		}
		if (_AsyncListener.isKeyDown (KeyLEFT))
		{
			dir+=CVector (-1, 0, 0);
			find=true;
		}
		if (_AsyncListener.isKeyDown (KeyNEXT))
		{
			dir+=CVector (0, 0, -1);
			find=true;
		}
		if (_AsyncListener.isKeyDown (KeyPRIOR))
		{
			dir+=CVector (0, 0, 1);
			find=true;
		}

		// key found ?
		if (find)
		{
			// Time elapsed
			uint32 milli=(uint32)(CTime::getLocalTime ()-_LastTime);

			// Speed
			float dPos=_Speed*(float)milli/1000.f;

			// Good direction
			dir.normalize ();
			dir*=dPos;

			// Orientation
			dir=_Matrix.mulVector (dir);

			// New position
			_Matrix.setPos (_Matrix.getPos ()+dir);
		}
	}

	// Last time
	_LastTime=CTime::getLocalTime ();


	// Return the matrix
	return _Matrix;
}