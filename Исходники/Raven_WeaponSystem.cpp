//-------------------------- PredictFuturePositionOfTarget --------------------
//
//  predicts where the target will be located in the time it takes for a
//  projectile to reach it. This uses a similar logic to the Pursuit steering
//  behavior.
//-----------------------------------------------------------------------------
Vector2D Raven_WeaponSystem::PredictFuturePositionOfTarget()const
{
	double MaxSpeed = GetCurrentWeapon()->GetMaxProjectileSpeed();

	//if the target is ahead and facing the agent shoot at its current pos
	Vector2D ToEnemy = m_pOwner->GetTargetBot()->Pos() - m_pOwner->Pos();

	//the lookahead time is proportional to the distance between the enemy
	//and the pursuer; and is inversely proportional to the sum of the
	//agent's velocities
	double LookAheadTime = ToEnemy.Length() /
		(MaxSpeed + m_pOwner->GetTargetBot()->MaxSpeed());

	//return the predicted future position of the enemy
	return m_pOwner->GetTargetBot()->Pos() +
		m_pOwner->GetTargetBot()->Velocity() * LookAheadTime;
}