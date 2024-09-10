	// ---------------------------------------------------------------------------------
	bool ConvexPolygon::isHitBy(const Ray& ray) const {
		// Create a RayStart->Edge defined plane. 
		// If the intersection of the ray to the polygon's plane is inside for all the planes, it is inside the poly
		// By inside, I mean the point is on positive side of the plane
		std::pair<bool, Real> intersection = ray.intersects(mPlane);
		
		if (!intersection.first) 
			return false;
		
		// intersection point
		Vector3 ip     = ray.getPoint(intersection.second);
		Vector3 origin = ray.getOrigin();
				
		unsigned int pointcount = mPoints.size();
		for (unsigned int idx = 0; idx < pointcount; idx++) {
			int iv2 = (idx + 1) % pointcount;
			
			Vector3 v1 = mPoints[idx];
			Vector3 v2 = mPoints[iv2];
			
			Plane frp(origin, v1, v2);
			
			// test whether the intersection is inside
			if (frp.getSide(ip) != Plane::POSITIVE_SIDE)
				return false;
		}
		
		return true;
	}