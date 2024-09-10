Hako::Math::Matrix4 Hako::Math::Matrix4::make_lookat(const Vector3 eye, const Vector3 target, const Vector3 up)
{
	Vector3 zaxis = (eye - target).get_normalized();
	Vector3 xaxis = up.cross(zaxis).get_normalized();
	Vector3 yaxis = zaxis.cross(xaxis);

	const float cells[4][4] = {
		{ xaxis.x, yaxis.x, zaxis.x, 0 },
		{ xaxis.y, yaxis.y, zaxis.y, 0 },
		{ xaxis.z, yaxis.z, zaxis.z, 0 },
		{ -xaxis.dot(eye), -yaxis.dot(eye), -zaxis.dot(eye), 1 }
	};

	return Matrix4::make_array(cells);
}