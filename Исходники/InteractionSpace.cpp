Vector3f normal(Vector3f a, Vector3f b, Vector3f c) {
	Vector3f x = a-b;
	Vector3f y = c-b;
	Vector3f n = x.cross(y);
	n.normalize();
	return n;
}