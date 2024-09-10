void AnglesFromTo(Vector &from, Vector &to, Vector &angles)
{
	Vector dir = to - from;

	// Store then zero height
	float dz = dir.z;
	
	dir.z = 0;

	// Need this for later
	float length = dir.Length();

	dir = dir.Normalize();

	// This is our forward angle
	Vector vForward(1.0f, 0.0f, 0.0f);

	float dot_product = (dir.x * vForward.x) + (dir.y * vForward.y) + (dir.z * vForward.z);

	float angle = acos(dot_product) * 180.0f / (float)M_PI;

	if (dir.y < 0)
		angle = 360.0f - angle;

	// This is our pitchup/down
	if (length == 0)
		length = 0.01f;

	float pitch = atan(dz / length) * 180.0f / (float)M_PI;

	angles.x = angle;
	angles.y = -pitch;
}