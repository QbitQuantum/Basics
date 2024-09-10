Vector CNPC_Ichthyosaur::DoProbe( const Vector &probe )
{
	trace_t	tr;
	float	fraction = 1.0f;
	bool	collided = false;
	Vector	normal	 = Vector( 0, 0, -1 );

	float	waterLevel = UTIL_WaterLevel( GetAbsOrigin(), GetAbsOrigin().z, GetAbsOrigin().z+150 );

	waterLevel -= GetAbsOrigin().z;
	waterLevel /= 150;

	if ( waterLevel < 1.0f )
	{
		collided = true;
		fraction = waterLevel;
	}

	AI_TraceHull( GetAbsOrigin(), probe, GetHullMins(), GetHullMaxs(), MASK_NPCSOLID, this, COLLISION_GROUP_NONE, &tr );
	
	if ( ( collided == false ) || ( tr.fraction < fraction ) )
	{
		fraction	= tr.fraction;
		normal		= tr.plane.normal;
	}

	if ( ( fraction < 1.0f ) && ( GetEnemy() == NULL || tr.u.ent != GetEnemy()->pev ) )
	{
#if FEELER_COLLISION_VISUALIZE
		NDebugOverlay::Line( GetLocalOrigin(), probe, 255, 0, 0, false, 0.1f );
#endif
		
		Vector	probeDir = probe - GetLocalOrigin();

		Vector	normalToProbeAndWallNormal = probeDir.Cross( normal );
		Vector	steeringVector = normalToProbeAndWallNormal.Cross( probeDir );

		Vector	velDir = GetAbsVelocity();
		VectorNormalize( velDir );

		float	steeringForce = m_flGroundSpeed * ( 1.0f - fraction ) * normal.Dot( velDir );

		if ( steeringForce < 0.0f )
		{
			steeringForce = -steeringForce;
		}

		velDir = steeringVector;
		VectorNormalize( velDir );

		steeringVector = steeringForce * velDir;
		
		return steeringVector;
	}

#if FEELER_COLLISION_VISUALIZE
	NDebugOverlay::Line( GetLocalOrigin(), probe, 0, 255, 0, false, 0.1f );
#endif

	return Vector( 0.0f, 0.0f, 0.0f );
}