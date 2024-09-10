Vector Triangle::getNormalAtPoint(Vector& p) {
	Vector v = (p3-p1).cross(p2-p1);
	v.normalize();
	return v;
} 