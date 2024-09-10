	void CameraFlyer::update()
	{
		bool goingForward = gVirtualInput().isButtonHeld(mMoveForward);
		bool goingBack = gVirtualInput().isButtonHeld(mMoveBack);
		bool goingLeft = gVirtualInput().isButtonHeld(mMoveLeft);
		bool goingRight = gVirtualInput().isButtonHeld(mMoveRight);
		bool fastMove = gVirtualInput().isButtonHeld(mFastMove);
		bool camRotating = gVirtualInput().isButtonHeld(mRotateCam);

		if (camRotating != mLastButtonState)
		{
			if (camRotating)
				Cursor::instance().hide();
			else
				Cursor::instance().show();

			mLastButtonState = camRotating;
		}

		float frameDelta = gTime().getFrameDelta();
		if (camRotating)
		{
			mYaw += Degree(gVirtualInput().getAxisValue(mHorizontalAxis) * ROTATION_SPEED * frameDelta);
			mPitch += Degree(gVirtualInput().getAxisValue(mVerticalAxis) * ROTATION_SPEED * frameDelta);

			mYaw = wrapAngle(mYaw);
			mPitch = wrapAngle(mPitch);

			Quaternion yRot;
			yRot.fromAxisAngle(Vector3::UNIT_Y, Radian(mYaw));

			Quaternion xRot;
			xRot.fromAxisAngle(Vector3::UNIT_X, Radian(mPitch));

			Quaternion camRot = yRot * xRot;
			camRot.normalize();

			SO()->setRotation(camRot);
		}

		Vector3 direction = Vector3::ZERO;
		if (goingForward) direction += SO()->getForward();
		if (goingBack) direction -= SO()->getForward();
		if (goingRight) direction += SO()->getRight();
		if (goingLeft) direction -= SO()->getRight();

		if (direction.squaredLength() != 0)
		{
			direction.normalize();

			float multiplier = 1.0f;
			if (fastMove)
				multiplier = FAST_MODE_MULTIPLIER;

			mCurrentSpeed = Math::clamp(mCurrentSpeed + ACCELERATION * frameDelta, START_SPEED, TOP_SPEED);
			mCurrentSpeed *= multiplier;
		}
		else
		{
			mCurrentSpeed = 0.0f;
		}

		float tooSmall = std::numeric_limits<float>::epsilon();
		if (mCurrentSpeed > tooSmall)
		{
			Vector3 velocity = direction * mCurrentSpeed;
			SO()->move(velocity * frameDelta);
		}
	}