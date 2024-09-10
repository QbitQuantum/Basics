void DumbTank::Update(float deltaTime, SDL_Event e)
{
	//This is a dumb tank. Do NOT copy this approach.

	//Did we see a tank?
	if(mTanksICanSee.size() == 0)
	{
		ChangeState(TANKSTATE_IDLE);

		//If there are no visible tanks, then keep moving.

		//Check if we reached position before turning.
		if(mPosition.y < mPosition1.y && mHeading.y != -1.0f)
		{
			mHeading = Vector2D(0.0f, -1.0f);
			mRotationAngle = 180.0f;
			mVelocity = Vector2D();
			return;
		}
		else if(mPosition.y > mPosition2.y && mHeading.y != 1.0f)
		{
			mHeading = Vector2D(0.0f, 1.0f);
			mRotationAngle = 0.0f;
			mVelocity = Vector2D();
			return;
		}
		else
		{
			//Move if we are facing the correct direction.
			mCurrentSpeed -= kSpeedIncrement*deltaTime;
			if(mCurrentSpeed < -GetMaxSpeed())
				mCurrentSpeed = -GetMaxSpeed();
		}
	}
	else
	{
		//Rotate man to face enemy tank.
		Vector2D toTarget = mTanksICanSee[0]->GetCentralPosition()-GetCentralPosition();
		toTarget.Normalize();
		double dot = toTarget.Dot(mManFireDirection);
		if(dot < 0.95f)
			RotateManByRadian(kManTurnRate, -1, deltaTime);

		//Otherwise stop moving and fire at the visible tank.
		mVelocity = Vector2D();
		ChangeState(TANKSTATE_MANFIRE);
	}

	BaseTank::Update(deltaTime, e);
}