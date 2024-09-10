void CPropCannon::LaunchProjectile( void )
{
	//ADRIANTODO: Come back to this once we get the right model and remove all the fix ups caused by temp content.

	Vector vTipPos, vTipForward, vTipRight, vUp;

	GetAttachment( "cable_tip", vTipPos, &vTipForward, &vTipRight, &vUp );

	bool bCollided = false;
	bool bInSky = false;
	float gravity = -gpGlobals->frametime * 600;
	Vector vOrigin = vTipPos;
	Vector vVelocity = vTipRight * 2500;

	float flDistance = 0.0f;

	int iFailSafe = 0;
	
	while ( bCollided == false && iFailSafe < 100000 )
	{
		Vector vOldOrigin = vOrigin;
		vOrigin = vOrigin + vVelocity * gpGlobals->frametime;

		flDistance += (vOrigin - vOldOrigin).Length();

		if ( g_cannon_debug.GetBool() == true )
		{
			NDebugOverlay::Line( vOldOrigin, vOrigin, 0, 255, 0, true, 5 );
		}

		trace_t pm;		
		UTIL_TraceLine( vOldOrigin, vOrigin, MASK_SOLID, this, COLLISION_GROUP_NONE, &pm );

		if ( pm.surface.flags & SURF_SKY || pm.allsolid == true ) 
		{
			bInSky = true;
			iFailSafe++;
		}
		else
		{
			bInSky = false;
		}

		iFailSafe++;

		if ( pm.fraction != 1.0f && bInSky == false )
		{
			bCollided = true;
			vOrigin = pm.endpos;

			if ( g_cannon_debug.GetBool() == true )
			{
				NDebugOverlay::Box( vOrigin, Vector( 256, 256, 256 ), Vector( -256, -256, -256 ), 255, 0, 0, 0, 5 );
			}
		}
		else
		{
			vVelocity[2] += gravity;
		}
	}
	
	float flTravelTime = flDistance / vVelocity.Length();

	if ( flTravelTime > g_cannon_max_traveltime.GetFloat() )
	{
		flTravelTime = g_cannon_max_traveltime.GetFloat();

		if ( bCollided == false )
		{
			vOrigin = vec3_origin; 
		}
	}

	m_flFlyTime = gpGlobals->curtime + flTravelTime;
	m_vCrashPoint = vOrigin;

	m_flNextAttackTime = gpGlobals->curtime + g_cannon_reloadtime.GetFloat();
	
	EmitSound( "HeadcrabCanister.LaunchSound" );

	UTIL_ScreenShake( GetDriver()->GetAbsOrigin(), 50.0, 150.0, 1.0, 750, SHAKE_START, true );
}