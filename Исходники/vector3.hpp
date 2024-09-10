inline Vector3 pointOnHemisphere(const Vector3& n, float theta, float phi)
{
	Vector3 ref = (fabs(n.x) < 0.5f) ?
		Vector3(1.0f, 0.0f, 0.0f) : Vector3(0.0f, 1.0f, 0.0f);

	Vector3 u = n.cross(ref).normalize();
	Vector3 v = u.cross(n);

	return
		u * sinf(theta) * cosf(phi) +
		v * sinf(theta) * sinf(phi) +
		n * cosf(theta);
}