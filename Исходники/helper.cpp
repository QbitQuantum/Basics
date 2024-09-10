	const mat4 FreeCamera(vec3 eye, vec3 dir, vec3 up)
	{
		// Builds a look-at style view matrix.
		// This is essentially the same matrix used by gluLookAt().
		vec3 target = eye + dir;
		vec3 zAxis = eye - target;
		zAxis.Normalize();

		vec3 xAxis = up.Cross(zAxis);
		xAxis.Normalize();

		vec3 yAxis = zAxis.Cross(xAxis);
		yAxis.Normalize();

		mat4 res;
		float* m = &res[0];

		m[0*4 + 0] = xAxis[0];
		m[1*4 + 0] = xAxis[1];
		m[2*4 + 0] = xAxis[2];
		m[3*4 + 0] = -xAxis.Dot(eye);

		m[0*4 + 1] = yAxis[0];
		m[1*4 + 1] = yAxis[1];
		m[2*4 + 1] = yAxis[2];
		m[3*4 + 1] = -yAxis.Dot(eye);

		m[0*4 + 2] = zAxis[0];
		m[1*4 + 2] = zAxis[1];
		m[2*4 + 2] = zAxis[2];
		m[3*4 + 2] = -zAxis.Dot(eye);

		m[0*4 + 3] = 0.0f;
		m[1*4 + 3] = 0.0f;
		m[2*4 + 3] = 0.0f;
		m[3*4 + 3] = 1.0f;
		return res;
	}