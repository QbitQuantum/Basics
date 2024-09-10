/*
=====================
idAI::PredictTrajectory

  returns true if there is a collision free trajectory for the clip model
  aimDir is set to the ideal aim direction in order to hit the target
=====================
*/
bool idAI::PredictTrajectory( const idVec3 &firePos, const idVec3 &target, float projectileSpeed, const idVec3 &projGravity, const idClipModel *clip, int clipmask, float max_height, const idEntity *ignore, const idEntity *targetEntity, int drawtime, idVec3 &aimDir ) {
	int n, i, j;
	float zVel, a, t, pitch, s, c;
	trace_t trace;
	ballistics_t ballistics[2];
	idVec3 dir[2];
	idVec3 velocity;
	idVec3 lastPos, pos;

	assert( targetEntity );

	// check if the projectile starts inside the target
	if ( targetEntity->GetPhysics()->GetAbsBounds().IntersectsBounds( clip->GetBounds().Translate( firePos ) ) ) {
		aimDir = target - firePos;
		aimDir.Normalize();
		return true;
	}

	// if no velocity or the projectile is not affected by gravity
	if ( projectileSpeed <= 0.0f || projGravity == vec3_origin ) {

		aimDir = target - firePos;
		aimDir.Normalize();

		gameLocal.clip.Translation( trace, firePos, target, clip, mat3_identity, clipmask, ignore );

		if ( drawtime ) {
			gameRenderWorld->DebugLine( colorRed, firePos, target, drawtime );
			idBounds bnds( trace.endpos );
			bnds.ExpandSelf( 1.0f );
			gameRenderWorld->DebugBounds( ( trace.fraction >= 1.0f || ( gameLocal.GetTraceEntity( trace ) == targetEntity ) ) ? colorGreen : colorYellow, bnds, vec3_zero, drawtime );
		}

		return ( trace.fraction >= 1.0f || ( gameLocal.GetTraceEntity( trace ) == targetEntity ) );
	}

	n = Ballistics( firePos, target, projectileSpeed, projGravity[2], ballistics );
	if ( n == 0 ) {
		// there is no valid trajectory
		aimDir = target - firePos;
		aimDir.Normalize();
		return false;
	}

	// make sure the first angle is the smallest
	if ( n == 2 ) {
		if ( ballistics[1].angle < ballistics[0].angle ) {
			a = ballistics[0].angle; ballistics[0].angle = ballistics[1].angle; ballistics[1].angle = a;
			t = ballistics[0].time; ballistics[0].time = ballistics[1].time; ballistics[1].time = t;
		}
	}

	// test if there is a collision free trajectory
	for ( i = 0; i < n; i++ ) {
		pitch = DEG2RAD( ballistics[i].angle );
		idMath::SinCos( pitch, s, c );
		dir[i] = target - firePos;
		dir[i].z = 0.0f;
		dir[i] *= c * idMath::InvSqrt( dir[i].LengthSqr() );
		dir[i].z = s;

		zVel = projectileSpeed * dir[i].z;

		if ( ai_debugTrajectory.GetBool() ) {
			t = ballistics[i].time / 100.0f;
			velocity = dir[i] * projectileSpeed;
			lastPos = firePos;
			pos = firePos;
			for ( j = 1; j < 100; j++ ) {
				pos += velocity * t;
				velocity += projGravity * t;
				gameRenderWorld->DebugLine( colorCyan, lastPos, pos );
				lastPos = pos;
			}
		}

		if ( TestTrajectory( firePos, target, zVel, projGravity[2], ballistics[i].time, firePos.z + max_height, clip, clipmask, ignore, targetEntity, drawtime ) ) {
			aimDir = dir[i];
			return true;
		}
	}

	aimDir = dir[0];

	// there is no collision free trajectory
	return false;
}