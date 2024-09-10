//----------------------------------------------------------------------------
bool PushTransformController::Update(double applicationTime, 
	double elapsedTime1)
{
	if (!Controller::Update(applicationTime, elapsedTime1))
		return false;

	if (mVelocity == AVector::ZERO)
		return true;

	float elapsedTime = (float)elapsedTime1;

	AVector velocityDis = mVelocity*elapsedTime;
	AVector movedDis;

	if (IsXY())
	{
		movedDis.X() = velocityDis.X();
		movedDis.Y() = velocityDis.Y();
	}
	else
	{
		movedDis.X() = velocityDis.X();
		movedDis.Z() = velocityDis.Z();
	}

	OnMoving(movedDis);
	
	// 减小速度
	AVector vecTemp = mVelocity;
	float vecLength = vecTemp.Normalize();
	vecLength -= mFriction * elapsedTime;
	if (vecLength <= 0.0f)
	{
		SetVelocity(AVector::ZERO);
	}
	else
	{
		SetVelocity(vecTemp * vecLength);
	}

	return true;
}