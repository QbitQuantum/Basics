//----------------------------------------------------------------------------
void InterpCurveSpeedController::_Update (double applicationTime)
{
	InterpCurveFloat3Controller::_Update(applicationTime);

	if (0.0f >= GetPlayedTimeMinusDelay())
		return;

	const AVector &curValue = GetCurValueRelatived();
	float elapsedTime = (float)GetElapsedTime();

	AVector dis = curValue * elapsedTime;
	float disLength = dis.Normalize();

	float allLengthTemp = mAllLength;
	allLengthTemp += disLength;

	if (mMaxLength >= 0.0f)
	{
		if (allLengthTemp >= mMaxLength)
		{
			disLength = mMaxLength - mAllLength;
			mAllLength = mMaxLength;
			Stop();
		}
		else
		{
			mAllLength = allLengthTemp;
		}
	
		Movable* movable = StaticCast<Movable>(mObject);
		if (movable)
		{
			APoint curPos = movable->LocalTransform.GetTranslate() + dis * disLength;
			movable->LocalTransform.SetTranslate(curPos);
		}
	}
	else
	{
		Movable* movable = StaticCast<Movable>(mObject);
		if (movable)
		{
			APoint curPos = movable->LocalTransform.GetTranslate() + dis * disLength;
			movable->LocalTransform.SetTranslate(curPos);
		}
	}
}