Matrix4x4& Matrix4x4::SelfShadow(const Point& light)
{
	Point Light = light;
	Light.Normalize();

	Zero();
	m[0][0] = Light.x * 0.5f;
	m[0][1] = Light.y * 0.5f;
	m[0][2] = Light.z * 0.5f;
	m[0][3] = 0.5f;
	m[3][3] = 1.0f;
	return *this;
}