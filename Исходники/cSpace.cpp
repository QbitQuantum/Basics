// dir = 1 for CCW search or clockwise around obstacle
// dir = -1 for CW search or counter clockwise around obstacle
bool cSpace::movePointAroundCSpace(btVector3& pt, btVector3 startVect, float stpMag, int dir)
{
	float angle=0;
	float zHeight = pt.z();
	pt.setZ(0);
	btVector3 nudge = stpMag * startVect.normalize();
	btVector3 npt = pt + nudge;
	
	while(isPointInsideCSpace(npt))							// check if the point is inside of the object
	{
		npt = pt + nudge.rotate(btVector3(0,0,1),angle);	// calculate a new point a radius of vector nudge away at angle
		angle += (dir * 0.1);								// in radians
		
		if(fabs(angle) > TWOPI)								// if the search has gone a full rotation
			return false;									// and there is no path outside a C-Space return false, stuck
	}
	
	pt = npt;
	pt.setZ(zHeight);
	return true;
}