	// This function reprojects the rotation of device north onto the camera axis.
	static RealT normalized_bearing(RealT bearing, const Vec3 & device_north, const Vec3 & gravity, const Vec3 & camera_axis)
	{
		//return bearing;
		
		Vec3 f = gravity.normalize();
		Vec3 down(0, 0, -1); // When the camera is pointing down, what is the device axis of the camera?

		float sz = acos(down.dot(f));
	
		Quat q = IDENTITY;
	
		if (sz > 0.05) {
			Vec3 s = cross_product(down, f);

			q *= (Quat)rotate(radians(sz), s);
		} else {
			return bearing;
		}

		q *= (Quat)rotate<Z>(degrees(bearing));
		
		// q is a coordinate frame which rotates from device coordinate space to world coordinate space such that +Y points north. We need to find the bearing of the camera axis relative to north.
		
		// Let's rotate the device camera axis into this coordinate frame:
		Vec3 global_camera_axis = q.conjugate() * camera_axis;
		
		// global_camera_axis is now in a coordinate frame where +Y is north, +X is east, -Z is down, and so on. We compute the bearing by projecting global_camera_axis onto the plane XY and looking at the rotation from +Y (north):
		
		global_camera_axis[Z] = 0;
		global_camera_axis = global_camera_axis.normalize();
		
		Quat r = rotate(Vec3{0, 1, 0}, global_camera_axis, Vec3{0, 0, 1});
		
		//log_debug("global_camera_axis", global_camera_axis, "r", r, "bearing", (r.angle() * r.axis().dot({0, 0, 1})) * R2D);
		
		return (r.angle() * r.axis().dot({0, 0, -1})) * R2D;
	}