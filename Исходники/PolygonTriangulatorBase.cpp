// -------------------------------------------------------------------------------------
void PolygonTriangulator::importPoints(const PxVec3 *points, int numPoints, const int *indices, PxVec3 *planeNormal, bool &isConvex)
{
	// find projection 3d -> 2d;
	PxVec3 n;

	isConvex = true;

	if (planeNormal) 
		n = *planeNormal;
	else {
		PX_ASSERT(numPoints >= 3);
		n = PxVec3(0.0f, 0.0f, 0.0f);

		for (int i = 1; i < numPoints-1; i++) {
			int i0 = 0;
			int i1 = i;
			int i2 = i+1;
			if (indices) {
				i0 = indices[i0];
				i1 = indices[i1];
				i2 = indices[i2];
			}
			const PxVec3 &p0 = points[i0];
			const PxVec3 &p1 = points[i1];
			const PxVec3 &p2 = points[i2];
			PxVec3 ni = (p1-p0).cross(p2-p0);
			if (i > 1 && ni.dot(n) < 0.0f)
				isConvex = false;
			n += ni;
		}
	}

	n.normalize();
	PxVec3 t0,t1;

	if (fabs(n.x) < fabs(n.y) && fabs(n.x) < fabs(n.z))
		t0 = PxVec3(1.0f, 0.0f, 0.0f);
	else if (fabs(n.y) < fabs(n.z))
		t0 = PxVec3(0.0f, 1.0f, 0.0f);
	else
		t0 = PxVec3(0.0f, 0.0f, 1.0f);
	t1 = n.cross(t0);
	t1.normalize();
	t0 = t1.cross(n);
	
	mPoints.resize((uint32_t)numPoints);
	if (indices == NULL) {
		for (uint32_t i = 0; i < (uint32_t)numPoints; i++) 
			mPoints[i] = PxVec3(points[i].dot(t0), points[i].dot(t1), 0.0f);
	}
	else {
		for (uint32_t i = 0; i < (uint32_t)numPoints; i++) {
			const PxVec3 &p = points[(uint32_t)indices[i]];
			mPoints[i] = PxVec3(p.dot(t0), p.dot(t1), 0.0f);
		}
	}
}