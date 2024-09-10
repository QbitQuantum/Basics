float HitCircle::HitTestBasicRadius(const Ball * pball, float dtime, CollisionEvent& coll,
									bool direction, bool lateral, bool rigid)
{
	if (!m_fEnabled || pball->m_frozen) return -1.0f;	

    Vertex3Ds c(center.x, center.y, 0.0f);
    Vertex3Ds dist = pball->m_pos - c;    // relative ball position
    Vertex3Ds dv = pball->m_vel;

	float targetRadius;
	bool capsule3D;
	
	if (!lateral && pball->m_pos.z > zhigh)
	{
		capsule3D = true;										// handle ball over target? 
		//const float hcap = radius*(float)(1.0/5.0);			// cap height to hit-circle radius ratio
		//targetRadius = radius*radius/(hcap*2.0f) + hcap*0.5f;	// c = (r^2+h^2)/(2*h)
		targetRadius = radius*(float)(13.0/5.0);				// optimized version of above code
		//c.z = zhigh - (targetRadius - hcap);					// b = c - h
		c.z = zhigh - radius*(float)(12.0/5.0);					// optimized version of above code
		dist.z = pball->m_pos.z - c.z;							// ball rolling point - capsule center height 			
	}
	else
	{
		capsule3D = false;
		targetRadius = radius;
		if (lateral)
			targetRadius += pball->m_radius;
		dist.z = dv.z = 0.0f;
	}
	
	const float bcddsq = dist.LengthSquared();	// ball center to circle center distance ... squared
	const float bcdd = sqrtf(bcddsq);			// distance center to center
	if (bcdd <= 1.0e-6f)
        return -1.0f;                           // no hit on exact center

	const float b = dist.Dot(dv);
	const float bnv = b/bcdd;					// ball normal velocity

	if (direction && bnv > C_LOWNORMVEL)
        return -1.0f;                           // clearly receding from radius

	const float bnd = bcdd - targetRadius;		// ball normal distance to 

	const float a = dv.LengthSquared();

	float hittime = 0;
	bool fUnhit = false;
    bool isContact = false;
	// Kicker is special.. handle ball stalled on kicker, commonly hit while receding, knocking back into kicker pocket
	if (m_ObjType == eKicker && bnd <= 0 && bnd >= -radius && a < C_CONTACTVEL*C_CONTACTVEL )	
    {
		if (pball->m_vpVolObjs) pball->m_vpVolObjs->RemoveElement(m_pObj);	// cause capture
    }

	if (rigid && bnd < (float)PHYS_TOUCH)		// positive: contact possible in future ... Negative: objects in contact now
    {
		if (bnd < -pball->m_radius/**2.0f*/) //!! *2 necessary?
            return -1.0f;
        else if (fabsf(bnv) <= C_CONTACTVEL)
        {
            isContact = true;
            hittime = 0;
        }
        else
			hittime = std::max(0.0f, -bnd / bnv);   // estimate based on distance and speed along distance
    }
	else if (m_ObjType >= eTrigger // triggers & kickers
		     && pball->m_vpVolObjs && ((bnd < 0.f) == (pball->m_vpVolObjs->IndexOf(m_pObj) < 0)))
    { // here if ... ball inside and no hit set .... or ... ball outside and hit set

		if (fabsf(bnd-radius) < 0.05f)	 // if ball appears in center of trigger, then assumed it was gen'ed there
		{
			if (pball->m_vpVolObjs)
                pball->m_vpVolObjs->AddElement(m_pObj);	//special case for trigger overlaying a kicker
		}												// this will add the ball to the trigger space without a Hit
		else
		{
			hittime = 0;
			fUnhit = (bnd > 0.f);	// ball on outside is UnHit, otherwise it's a Hit
		}
    }
	else
    {
		if((!rigid && bnd * bnv > 0.f) ||	// (outside and receding) or (inside and approaching)
		   (a < 1.0e-8f)) return -1.0f;	    // no hit ... ball not moving relative to object

        float time1, time2;
        if (!SolveQuadraticEq(a, 2.0f*b, bcddsq - targetRadius*targetRadius, time1, time2))
            return -1.0f;
		
		fUnhit = (time1*time2 < 0.f);
		hittime = fUnhit ? max(time1,time2) : min(time1,time2); // ball is inside the circle
    }
	
    if (infNaN(hittime) || hittime < 0.f || hittime > dtime)
        return -1.0f; // contact out of physics frame
	const float hitz = pball->m_pos.z - pball->m_radius + pball->m_vel.z * hittime; // rolling point

	if(((hitz + pball->m_radius *1.5f) < zlow) ||
	   (!capsule3D && (hitz + pball->m_radius*0.5f) > zhigh) ||
	   (capsule3D && (pball->m_pos.z + pball->m_vel.z * hittime) < zhigh)) return -1.0f;
		
	const float hitx = pball->m_pos.x + pball->m_vel.x*hittime;
	const float hity = pball->m_pos.y + pball->m_vel.y*hittime;

	const float sqrlen = (hitx - c.x)*(hitx - c.x) + (hity - c.y)*(hity - c.y);

	if (sqrlen > 1.0e-8f) // over center???
	{ // no
		const float inv_len = 1.0f/sqrtf(sqrlen);
		coll.hitnormal.x = (hitx - c.x)*inv_len;
		coll.hitnormal.y = (hity - c.y)*inv_len;
        coll.hitnormal.z = 0.0f;
	}
	else 
	{ // yes, over center
		coll.hitnormal.x = 0.0f; // make up a value, any direction is ok
		coll.hitnormal.y = 1.0f;
        coll.hitnormal.z = 0.0f;
	}
	
	if (!rigid)											// non rigid body collision? return direction
		coll.hitvelocity.x = fUnhit ? 1.0f : 0.0f;		// UnHit signal	is receding from target

    coll.isContact = isContact;
    if (isContact)
        coll.hitvelocity.z = bnv;

	coll.hitdistance = bnd;				//actual contact distance ... 
	//coll.hitRigid = rigid;			// collision type

	return hittime;
}