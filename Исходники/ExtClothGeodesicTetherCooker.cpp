///////////////////////////////////////////////////////////////////////////////
// compute intersection of a ray from a source vertex in direction toward parent
int PxClothGeodesicTetherCookerImpl::computeEdgeIntersection(PxU32 parent, PxU32 edge, float in_s, PathIntersection &path)
{
	int tid = (int)edge / 3;
	int eid = (int)edge % 3;

	PxU32 e0 = mIndices[PxU32(tid*3 + eid)];
	PxU32 e1 = mIndices[PxU32(tid*3 + (eid+1)%3)];

	PxVec3 v0 = mVertices[e0];
	PxVec3 v1 = mVertices[e1];

	PxVec3 v = v0 + in_s * (v1 - v0);
	PxVec3 g = mVertices[parent] - v;

	PxU32 triNbr = mTriNeighbors[edge];

	if (triNbr == PxU32(-1)) // boundary edge
	{
		float dir = g.dot(v1-v0);
		PxU32 vid = (dir > 0) ? e1 : e0;
		path = PathIntersection(true, vid, (mVertices[vid] - v).magnitude());
		return 1;
	}

	PxU32 i0 = mIndices[triNbr*3];
	PxU32 i1 = mIndices[triNbr*3+1];
	PxU32 i2 = mIndices[triNbr*3+2];

	// vertex is sorted s.t i0,i1 contains the edge point
	if ( checkEdge((int)i0, (int)i1, (int)e0, (int)e1)) {
		eid = 0;
	}
	else if ( checkEdge((int)i1, (int)i2, (int)e0, (int)e1)) {
		eid = 1;
		PxU32 tmp = i2;
		i2 = i0;
		i0 = i1;
		i1 = tmp;
	}
	else if ( checkEdge((int)i2, (int)i0, (int)e0, (int)e1)) 
	{
		eid = 2;
		PxU32 tmp = i0;
		i0 = i2;
		i2 = i1;
		i1 = tmp;
	}

	// we hit the parent
	if (i2 == parent)
	{
		path = PathIntersection(true, i2, (mVertices[i2] - v).magnitude());
		return 1;
	}

	PxVec3 p0 = mVertices[i0];
	PxVec3 p1 = mVertices[i1];
	PxVec3 p2 = mVertices[i2];

	// project gradient vector on the plane of the triangle
	PxVec3 n = ((p0 - p2).cross(p1 - p2)).getNormalized();
	g = (g - g.dot(n) * n).getNormalized();

	float s = 0.0f, t = 0.0f;
	const float eps = 1e-5;
	PxVec3 ip;

	// intersect against edge form p2 to p0
	if (intersectRayEdge(v, g, p2, p0, s, t) && ( s >= -eps) && ( s <= (1.0f+eps) ) && (t > -eps))
	{
		if ( ( s < eps) || (s > (1.0f-eps)))
		{
			path.vertOrTriangle = true;
			path.index = (s < eps) ? i2 : i0;
			path.distance = (mVertices[path.index] - v).magnitude();
		}
		else
		{
			ip = p2 + s * (p0 - p2);
			path = PathIntersection(false, triNbr*3 + (eid + 2) % 3, (ip - v).magnitude(), s);
			
		}

		return 1;
	}

	// intersect against edge form p1 to p2
	if (intersectRayEdge(v, g, p1, p2, s, t) && ( s >= -eps) && ( s <= (1.0f+eps) ) && (t > -eps))
	{
		if ( ( s < eps) || (s > (1.0f-eps)))
		{
			path.vertOrTriangle = true;
			path.index = (s < eps) ? i1 : i2;
			path.distance = (mVertices[path.index] - v).magnitude();
		}
		else
		{
			ip = p1 + s * (p2 - p1);
			path = PathIntersection(false, triNbr*3 + (eid + 1) % 3, (ip - v).magnitude(), s);
		}
		
		return 1;
	}

	// fallback to pick closer vertex when no edges intersect
	float dir = g.dot(v1-v0);
	path.vertOrTriangle = true;
	path.index = (dir > 0) ? e1 : e0;
	path.distance = (mVertices[path.index] - v).magnitude();

	return 1;
}