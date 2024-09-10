float HitTriangle::HitTest(const Ball * pball, float dtime, CollisionEvent& coll)
{
	if (!m_fEnabled) return -1.0f;

    const float bnv = normal.Dot(pball->m_vel);     // speed in Normal-vector direction

	if (bnv >= C_CONTACTVEL)						// return if clearly ball is receding from object
		return -1.0f;

	// Point on the ball that will hit the polygon, if it hits at all
	const float bRadius = pball->m_radius;
    Vertex3Ds hitPos = pball->m_pos - bRadius * normal; // nearest point on ball ... projected radius along norm

    const float bnd = normal.Dot( hitPos - m_rgv[0] );  // distance from plane to ball

	float hittime;

	if (bnd < -pball->m_radius/**2.0f*/) //!! *2 necessary?
        return -1.0f;	// (ball normal distance) excessive pentratration of object skin ... no collision HACK

    bool isContact = false;

    if (bnd <= (float)PHYS_TOUCH)
    {
        if (fabsf(bnv) <= C_CONTACTVEL)
        {
            hittime = 0;
            isContact = true;
        }
        else if (bnd <= 0)
            hittime = 0;                            // zero time for rigid fast bodies
        else
            hittime = bnd / -bnv;
    }
    else if (fabsf(bnv) > C_LOWNORMVEL )			// not velocity low?
        hittime = bnd / -bnv;						// rate ok for safe divide 
    else
        return -1.0f;								// wait for touching

	if (infNaN(hittime) || hittime < 0 || hittime > dtime)
        return -1.0f;	// time is outside this frame ... no collision

    hitPos += hittime * pball->m_vel;	// advance hit point to contact

    // check if hitPos is within the triangle

    // Compute vectors
    const Vertex3Ds v0 = m_rgv[2] - m_rgv[0];
    const Vertex3Ds v1 = m_rgv[1] - m_rgv[0];
    const Vertex3Ds v2 = hitPos   - m_rgv[0];

    // Compute dot products
    const float dot00 = v0.Dot(v0);
    const float dot01 = v0.Dot(v1);
    const float dot02 = v0.Dot(v2);
    const float dot11 = v1.Dot(v1);
    const float dot12 = v1.Dot(v2);

    // Compute barycentric coordinates
    const float invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);
    const float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    const float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    // Check if point is in triangle
    const bool pointInTri = (u >= 0.f) && (v >= 0.f) && (u + v <= 1.f);

	if (pointInTri)
	{
		coll.hitnormal = normal;

		coll.hitdistance = bnd;				// 3dhit actual contact distance ... 
		//coll.hitRigid = true;				// collision type

        if (isContact)
        {
            coll.isContact = true;
            coll.hitvelocity.z = bnv;
        }

		return hittime;
	}
    else
        return -1.0f;
}