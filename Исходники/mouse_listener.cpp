void C3dMouseListener::update()
{
	// CVector
	CVector dir (0,0,0);
	bool find=false;

	// -- -- what does the mouse listener have to do with the keyboard?!

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

	// Character state setup
	if (Self != NULL)
	{
		// modify the orientation depending on the straff
		// The straff is determined by the keys that are down simultaneously
		if (_AsyncListener.isKeyDown (KeyUP))
		{
			if (_AsyncListener.isKeyDown (KeyLEFT))
			{
				Self->AuxiliaryAngle = (float)Pi/4.0f;
			}
			else if (_AsyncListener.isKeyDown (KeyRIGHT))
			{
				Self->AuxiliaryAngle = -(float)Pi/4.0f;
			}
			else
			{
				Self->AuxiliaryAngle = 0;
			}
			_IsWalking = true;
		}
		else if (_AsyncListener.isKeyDown (KeyDOWN))
		{
			if (_AsyncListener.isKeyDown (KeyLEFT))
			{
				Self->AuxiliaryAngle = (float)Pi-(float)Pi/4.0f;
			}
			else if (_AsyncListener.isKeyDown (KeyRIGHT))
			{
				Self->AuxiliaryAngle = -(float)Pi+(float)Pi/4.0f;
			}
			else
			{
				Self->AuxiliaryAngle = (float)Pi;
			}
			_IsWalking = true;
		}
		else if (_AsyncListener.isKeyDown (KeyLEFT))
		{
			Self->AuxiliaryAngle = (float)Pi/2.0f;
			_IsWalking = true;
		}
		else if (_AsyncListener.isKeyDown (KeyRIGHT))
		{
			Self->AuxiliaryAngle = -(float)Pi/2.0f;
			_IsWalking = true;
		}
		else
		{
			_IsWalking = false;
		}

		if (isAiming())
			Self->AuxiliaryAngle = 0.0f;

		Self->IsAiming = isAiming();
		Self->IsWalking = isWalking();
	}


	// if is aiming
	if (_AimingState)
	{
		find = false;
		TTime	newTime = CTime::getLocalTime();
		float	delta = (float)(newTime-_AimingStartTime)/1000.0f;
		_AimingDamage = _AimingSpeed*delta;
		_AimingDamage = std::min(_AimingDamage, _AimingMax);

		// if we have to update the aiming position
		if (newTime - _AimingLastUpdateTime > _AimingRefreshRate)
		{
			// update the last target
			_AimingLastUpdateTime = newTime;
			// set up the aiming position
			_AimingPosition = MouseListener->getPosition()+CVector(0.0f, 0.0f, 2.0f);
			// compute the target
			_AimedTarget = getTarget(_AimingPosition,
									 MouseListener->getViewDirection(),
									 100);
		}

		if (Self != NULL && !_AimingInstance.empty())
		{
			_AimingInstance.lookAt(MouseListener->getAimedTarget(), Camera.getMatrix().getPos());
			float	scale = MouseListener->getDamage();
			_AimingInstance.setScale(scale, scale, scale);
			_AimingInstance.show();
		}
	}
	else
	{
		if (Self != NULL && !_AimingInstance.empty())
			_AimingInstance.hide();
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

	// Last time
	_LastTime=CTime::getLocalTime ();

}