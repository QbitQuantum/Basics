bool KX_RayCast::RayTest(PHY_IPhysicsEnvironment* physics_environment, const MT_Point3& _frompoint, const MT_Point3& topoint, KX_RayCast& callback)
{
	if(physics_environment==NULL) return false; /* prevents crashing in some cases */
	
	// Loops over all physics objects between frompoint and topoint,
	// calling callback.RayHit for each one.
	//
	// callback.RayHit should return true to stop looking, or false to continue.
	//
	// returns true if an object was found, false if not.
	
	MT_Point3 frompoint(_frompoint);
	const MT_Vector3 todir( (topoint - frompoint).safe_normalized() );
	MT_Point3 prevpoint(_frompoint+todir*(-1.f));
	
	PHY_IPhysicsController* hit_controller;

	while((hit_controller = physics_environment->rayTest(callback,
			frompoint.x(),frompoint.y(),frompoint.z(),
			topoint.x(),topoint.y(),topoint.z())) != NULL) 
	{
		KX_ClientObjectInfo* info = static_cast<KX_ClientObjectInfo*>(hit_controller->getNewClientInfo());
		
		if (!info)
		{
			printf("no info!\n");
			MT_assert(info && "Physics controller with no client object info");
			break;
		}
		
		// The biggest danger to endless loop, prevent this by checking that the
		// hit point always progresses along the ray direction..
		prevpoint -= callback.m_hitPoint;
		if (prevpoint.length2() < MT_EPSILON)
			break;

		if (callback.RayHit(info))
			// caller may decide to stop the loop and still cancel the hit
			return callback.m_hitFound;

		// Skip past the object and keep tracing.
		// Note that retrieving in a single shot multiple hit points would be possible 
		// but it would require some change in Bullet.
		prevpoint = callback.m_hitPoint;
		/* We add 0.001 of fudge, so that if the margin && radius == 0., we don't endless loop. */
		MT_Scalar marg = 0.001 + hit_controller->GetMargin();
		marg *= 2.f;
		/* Calculate the other side of this object */
		MT_Scalar h = MT_abs(todir.dot(callback.m_hitNormal));
		if (h <= 0.01)
			// the normal is almost orthogonal to the ray direction, cannot compute the other side
			break;
		marg /= h; 
		frompoint = callback.m_hitPoint + marg * todir;
		// verify that we are not passed the to point
		if ((topoint - frompoint).dot(todir) < 0.f)
			break;
	}
	return false;
}