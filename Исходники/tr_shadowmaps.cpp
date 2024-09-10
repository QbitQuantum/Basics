/*
===================
Cull

cull points against given shadow frustum.
Return true of all points are outside the frustum.
===================
*/
bool shadowMapFrustum_t::Cull( const idVec3 points[8] ) const {

	bool outsidePlane[6];

	for (int i = 0; i < numPlanes; i++) {

		bool pointsCulled[8] = { true };
		const idPlane plane = planes[i];

		for (int j = 0; j < 8; j++) {
			const float distance = plane.Distance( points[j] );
			pointsCulled[j] = distance < 0;
		}

		outsidePlane[i] = true;
		for (int j = 0; j < 8; j++) {
			if (!pointsCulled[j]) {
				outsidePlane[i] = false;
			}
		}
	}

	for (int i = 0; i < numPlanes; i++) {
		if (outsidePlane[i])
			return true;
	}

	return false;
}