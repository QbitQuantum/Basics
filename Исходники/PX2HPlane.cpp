//----------------------------------------------------------------------------
HPlane::HPlane (const APoint& p0, const APoint& p1, const APoint& p2)
{
	AVector edge1 = p1 - p0;
	AVector edge2 = p2 - p0;
	AVector normal = edge1.UnitCross(edge2);
	mTuple[0] = normal[0];
	mTuple[1] = normal[1];
	mTuple[2] = normal[2];
	mTuple[3] = -p0.Dot(normal);
}