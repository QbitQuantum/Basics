//=========================================================
// Tracking Hornet hit something
//=========================================================
void CHornet :: TrackTouch ( CBaseEntity *pOther )
{
	if ( pOther->edict() == pev->owner || pOther->pev->modelindex == pev->modelindex )
	{// bumped into the guy that shot it.
		pev->solid = SOLID_NOT;
		return;
	}

	if ( IRelationship( pOther ) <= R_NO )
	{
		// hit something we don't want to hurt, so turn around.
		Vector vecVelocity = GetAbsVelocity();

		vecVelocity = vecVelocity.Normalize();

		vecVelocity.x *= -1;
		vecVelocity.y *= -1;

		SetAbsVelocity( vecVelocity );

		SetAbsOrigin( GetAbsOrigin() + GetAbsVelocity() * 4 ); // bounce the hornet off a bit.
		SetAbsVelocity( GetAbsVelocity() * m_flFlySpeed );

		return;
	}

	DieTouch( pOther );
}