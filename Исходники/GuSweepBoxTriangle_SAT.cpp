static PX_FORCE_INLINE int testSeparationAxes(	const PxTriangle& tri, const PxVec3& extents,
												const PxVec3& normal, const PxVec3& dir, const PxVec3& oneOverDir, float tmax, float& tcoll)
{
#ifdef _XBOX
	float bValidMTD = 1.0f;
#else
	bool bValidMTD = true;
#endif
	tcoll = tmax;
	float tfirst = -FLT_MAX;
	float tlast  = FLT_MAX;

	// Triangle normal
#ifdef _XBOX
	if(testAxis(tri, extents, dir, normal, bValidMTD, tfirst, tlast)==0.0f)
#else
	if(!testAxis(tri, extents, dir, normal, bValidMTD, tfirst, tlast))
#endif
		return 0;

	// Box normals
#ifdef _XBOX
	if(testAxisXYZ(tri, extents, dir, oneOverDir.x, bValidMTD, tfirst, tlast, 0)==0.0f)
		return 0;
	if(testAxisXYZ(tri, extents, dir, oneOverDir.y, bValidMTD, tfirst, tlast, 1)==0.0f)
		return 0;
	if(testAxisXYZ(tri, extents, dir, oneOverDir.z, bValidMTD, tfirst, tlast, 2)==0.0f)
		return 0;
#else
	if(!testAxisXYZ(tri, extents, dir, oneOverDir.x, bValidMTD, tfirst, tlast, 0))
		return 0;
	if(!testAxisXYZ(tri, extents, dir, oneOverDir.y, bValidMTD, tfirst, tlast, 1))
		return 0;
	if(!testAxisXYZ(tri, extents, dir, oneOverDir.z, bValidMTD, tfirst, tlast, 2))
		return 0;
#endif
	// Edges
	for(PxU32 i=0; i<3; i++)
	{
		int ip1 = int(i+1);
		if(i>=2)	ip1 = 0;
		const PxVec3 TriEdge = tri.verts[ip1] - tri.verts[i];

#ifdef _XBOX
		{
			const PxVec3 Sep = Ps::cross100(TriEdge);
			if((Sep.dot(Sep))>=1.0E-6f && testAxis(tri, extents, dir, Sep, bValidMTD, tfirst, tlast)==0.0f)
				return 0;
		}
		{
			const PxVec3 Sep = Ps::cross010(TriEdge);
			if((Sep.dot(Sep))>=1.0E-6f && testAxis(tri, extents, dir, Sep, bValidMTD, tfirst, tlast)==0.0f)
				return 0;
		}
		{
			const PxVec3 Sep = Ps::cross001(TriEdge);
			if((Sep.dot(Sep))>=1.0E-6f && testAxis(tri, extents, dir, Sep, bValidMTD, tfirst, tlast)==0.0f)
				return 0;
		}
#else
		{
			const PxVec3 Sep = Ps::cross100(TriEdge);
			if((Sep.dot(Sep))>=1.0E-6f && !testAxis(tri, extents, dir, Sep, bValidMTD, tfirst, tlast))
				return 0;
		}
		{
			const PxVec3 Sep = Ps::cross010(TriEdge);
			if((Sep.dot(Sep))>=1.0E-6f && !testAxis(tri, extents, dir, Sep, bValidMTD, tfirst, tlast))
				return 0;
		}
		{
			const PxVec3 Sep = Ps::cross001(TriEdge);
			if((Sep.dot(Sep))>=1.0E-6f && !testAxis(tri, extents, dir, Sep, bValidMTD, tfirst, tlast))
				return 0;
		}
#endif
	}

	if(tfirst > tmax || tlast < 0.0f)	return 0;
	if(tfirst <= 0.0f)
	{
#ifdef _XBOX
		if(bValidMTD==0.0f)	return 0;
#else
		if(!bValidMTD)	return 0;
#endif
		tcoll = 0.0f;
	}
	else tcoll = tfirst;

	return 1;
}