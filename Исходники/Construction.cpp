	Point3d Point3d::Transform(const Matrix& m) {
		// transform Point
		Point3d ret;
		m.Transform(&x, &ret.x);
//		ret.ok = true;
		return ret;
	}