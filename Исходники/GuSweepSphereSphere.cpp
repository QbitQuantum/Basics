bool Gu::sweepSphereSphere(const PxVec3& center0, PxReal radius0, const PxVec3& center1, PxReal radius1, const PxVec3& motion, PxReal& d, PxVec3& nrm)
{
	const PxVec3 movedCenter = center1 + motion;

	PxReal tmp;
	if(!sphereSphereSweep(radius0, center0, center0, radius1, center1, movedCenter, d, tmp))
		return false;

	// Compute normal
	// PT: if spheres initially overlap, the convention is that returned normal = -sweep direction
	if(d==0.0f)
		nrm = -motion;
	else
		nrm = (center1 + d * motion) - center0;
	nrm.normalize();
	return true;
}