Vector2D B020612E_Steering::Pursuit(Vector2D target, Vector2D velocity)
{
	Vector2D targetPos = _pTank->mTargetPosition;
	double relative = _pTank->GetHeading().Dot(_pTank->mEnHeading);

	if ((targetPos.Dot(_pTank->GetHeading()) > 0) && (relative < -0.95))
		return Seek(targetPos);
	else
	{
		double lookAheadTime = targetPos.Length() / (_pTank->GetMaxSpeed() + _pTank->mEnSpeed);
		return Seek(targetPos + _pTank->mEnVel * lookAheadTime);
	}
}