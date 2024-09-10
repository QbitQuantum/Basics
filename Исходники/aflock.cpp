//=========================================================
// Searches for boids that are too close and pushes them away
//=========================================================
void CFlockingFlyer :: SpreadFlock( )
{
	Vector		vecDir;
	float		flSpeed;// holds vector magnitude while we fiddle with the direction
	
	CFlockingFlyer *pList = m_pSquadLeader;
	while ( pList )
	{
		if ( pList != this && ( pev->origin - pList->pev->origin ).Length() <= AFLOCK_TOO_CLOSE )
		{
			// push the other away
			vecDir = ( pList->pev->origin - pev->origin );
			vecDir = vecDir.Normalize();

			// store the magnitude of the other boid's velocity, and normalize it so we
			// can average in a course that points away from the leader.
			flSpeed = pList->pev->velocity.Length();
			pList->pev->velocity = pList->pev->velocity.Normalize();
			pList->pev->velocity = ( pList->pev->velocity + vecDir ) * 0.5;
			pList->pev->velocity = pList->pev->velocity * flSpeed;
		}

		pList = pList->m_pSquadNext;
	}
}