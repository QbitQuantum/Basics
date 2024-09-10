vector3f to3d(const vector2f &pts) {
	vector3f pts3d(pts.size());
	for(int i =0 ; i < pts.size(); i++ ) {
		Vector2f pt = pts[i];
		pts3d[i] = Vector3f(pt.x(), pt.y(), 0);
	}

	return pts3d;
}