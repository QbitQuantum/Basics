Vector2D S013010C_Aaron_Smith_Steering::Pursuing()
{
	
	Vector2D enemyTankPos = mTank->GetTarget();

	double relativeHeading = mTank->GetHeading().Dot(mTank->GetEnemyHeading());

	if (enemyTankPos.Dot(mTank->GetHeading()) > 0 &&
		(relativeHeading < -0.95))
		return Seek(enemyTankPos);
	else
	{
		//not ahead of player so need to predict enemy position
		
		double lookAheadTime = enemyTankPos.Length() / (mTank->GetMaxSpeed() + mTank->GetEnemySpeed());
		return Seek(enemyTankPos + mTank->GetEnemyVelocity() * lookAheadTime);
	}

}