OZCOLLIDE_API bool testIntersectionTriBox(const Vec3f *_triPts[3],
										 const Vec3f &_triNormal,
										 const Box &_box,
										 const Vec3f &_boxVel,
										 float &_distTravel,
										 Vec3f &_reaction)
{
	int i, j;
	float d0, d1;
	float t;

	Plane tri_plane;
	tri_plane.fromPointAndNormal(*_triPts[0], _triNormal);

	Vec3f n_boxvel = _boxVel;
	n_boxvel.normalize();

	if (_triNormal.dot(n_boxvel) > 0)
		return false;

	float minDist = FLT_MAX;
	int col = -1;

	// box vertices VS triangle
	for (i = 0; i < 8; i++) {
		Vec3f box_vertex = _box.getPoint(i);

		Vec3f box_vertex_normal = _box.getVertexNormal(i);
		if (box_vertex_normal.dot(n_boxvel) < -OZ_COS45)
			continue;

		float t;
		if (!tri_plane.intersectWithLine(box_vertex, box_vertex + n_boxvel, t) )
			continue;

		if (t >= minDist)
			continue;
		if (t < 0)
			continue;

		Vec3f inter;
		inter = box_vertex + n_boxvel * t;

		if (!isPointInsideTriangle(*_triPts[0], *_triPts[1], *_triPts[2], inter))
			continue;

		minDist = t;
		_reaction = _triNormal;
		col = 0;
	}

	// triangle vertices VS box faces
	for (i = 0; i < 3; i++) {
		float tnear, tfar;
		PLANE plane = intersectRayBox(*_triPts[i], -n_boxvel, _box, tnear, tfar);
		if (plane == -1)
			continue;

		if (tnear < 0)
			continue;

		if (tnear < minDist) {
			minDist = tnear;
			_reaction = -_box.getFaceNormal(plane);
			col = 1;
		}
	}

	// box edges VS triangle edges
	for (i = 0; i < 12; i++) {
		BoxEdge boxEdge = _box.getEdge(i);
		Plane boxEdgePlane;
		boxEdgePlane.fromPoints(boxEdge.p1, boxEdge.p0, boxEdge.p0 + _boxVel);

		Vec3f boxEdgeNormal = Vec3f(boxEdgePlane.a, boxEdgePlane.b, boxEdgePlane.c);

		Vec3f v0 = boxEdge.p1 - boxEdge.p0;

		for (j = 0; j < 3; j++) {
			const Vec3f *tpt0;
			const Vec3f *tpt1;
			tpt0 = _triPts[j];
			if (j < 2) tpt1 = _triPts[j + 1];
			else tpt1 = _triPts[0];

			d0 = boxEdgePlane.dist(*tpt0);
			d1 = boxEdgePlane.dist(*tpt1);
			if (d0 * d1 > 0)
				continue;

			if (!boxEdgePlane.intersectWithLine(*tpt0, *tpt1, t))
				continue;

			Vec3f v1 = *tpt1 - *tpt0;
			Vec3f ipt = *tpt0 + v1 * t;

			int a0 = 0, a1 = 1;
			float pl_x = fabsf(boxEdgePlane.a);
			float pl_y = fabsf(boxEdgePlane.b);
			float pl_z = fabsf(boxEdgePlane.c);
			if (pl_x > pl_y && pl_x > pl_z) {
				a0 = 1;
				a1 = 2;
			}
			else {
				if (pl_y > pl_z) {
					a0 = 0;
					a1 = 2;
				}
			}

			float dist = v0[a0] * (ipt[a1] - boxEdge.p0[a1]) - v0[a1] * (ipt[a0] - boxEdge.p0[a0]);
			float denom = v0[a1] * -n_boxvel[a0] - v0[a0] * -n_boxvel[a1];
			if (!denom)
				continue;
			dist /= denom;

			if (dist < 0)
				continue;

			ipt -= dist * n_boxvel;

			Vec3f r1 = boxEdge.p0 - ipt;
			Vec3f r2 = boxEdge.p1 - ipt;
			if (r1.dot(r2) > 0)
				continue;

			if (dist < minDist) {
				minDist = dist;
				_reaction = v0 | v1;
				_reaction.normalize();
				if (_reaction.dot(n_boxvel) > 0)
					_reaction = -_reaction;
				col = 2;
			}
		}
	}

	if (col == -1)
		return false;

	_distTravel = minDist;

	return true;
}