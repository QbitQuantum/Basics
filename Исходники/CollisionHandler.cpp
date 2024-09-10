bool CCollisionHandler::Intersect(const CollisionVolume* v, const CMatrix44f& m, const float3& p0, const float3& p1, CollisionQuery* q)
{
	numContTests += 1;

	CMatrix44f mInv = m.Invert();
	const float3 pi0 = mInv.Mul(p0);
	const float3 pi1 = mInv.Mul(p1);
	bool intersect = false;

	// minimum and maximum (x, y, z) coordinates of transformed ray
	const float rminx = std::min(pi0.x, pi1.x), rminy = std::min(pi0.y, pi1.y), rminz = std::min(pi0.z, pi1.z);
	const float rmaxx = std::max(pi0.x, pi1.x), rmaxy = std::max(pi0.y, pi1.y), rmaxz = std::max(pi0.z, pi1.z);

	// minimum and maximum (x, y, z) coordinates of (bounding box around) volume
	const float vminx = -v->GetHScales().x, vminy = -v->GetHScales().y, vminz = -v->GetHScales().z;
	const float vmaxx =  v->GetHScales().x, vmaxy =  v->GetHScales().y, vmaxz =  v->GetHScales().z;

	// check if ray segment misses (bounding box around) volume
	// (if so, then no further intersection tests are necessary)
	if (rmaxx < vminx || rminx > vmaxx) { return false; }
	if (rmaxy < vminy || rminy > vmaxy) { return false; }
	if (rmaxz < vminz || rminz > vmaxz) { return false; }

	switch (v->GetVolumeType()) {
		case CollisionVolume::COLVOL_TYPE_SPHERE: {
			// sphere is special case of ellipsoid, reuse code
			intersect = CCollisionHandler::IntersectEllipsoid(v, pi0, pi1, q);
		} break;
		case CollisionVolume::COLVOL_TYPE_CYLINDER: {
			intersect = CCollisionHandler::IntersectCylinder(v, pi0, pi1, q);
		} break;
		case CollisionVolume::COLVOL_TYPE_BOX: {
			// also covers footprints, but without taking the blocking-map into account
			// TODO: this would require stepping ray across non-blocking yardmap squares?
			//
			// intersect = CCollisionHandler::IntersectFootPrint(v, pi0, pi1, q);
			intersect = CCollisionHandler::IntersectBox(v, pi0, pi1, q);
		} break;
	}

	if (q != NULL) {
		// transform intersection points (iff not a special
		// case, otherwise calling code should not use them)
		if (q->b0 == CQ_POINT_ON_RAY) { q->p0 = m.Mul(q->p0); }
		if (q->b1 == CQ_POINT_ON_RAY) { q->p1 = m.Mul(q->p1); }
	}

	return intersect;
}