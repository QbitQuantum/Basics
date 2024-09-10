bool Gu::intersectPlaneBox(const PxPlane& plane, const Gu::Box& box)
{
	PxVec3 pts[8];
	box.computeBoxPoints(pts);

	for(PxU32 i=0;i<8;i++)
	{
		if(plane.distance(pts[i]) <= 0.0f)	// PT: objects are defined as closed, so we return 'true' in case of equality
			return true;
	}
	return false;
}