	mat4 T(GLfloat tx, GLfloat ty, GLfloat tz)
	{
		mat4 m;
		m = IdentityMatrix();
		if (transposed)
		{
			m.m[12] = tx;
			m.m[13] = ty;
			m.m[14] = tz;
		}
		else
		{
			m.m[3] = tx;
			m.m[7] = ty;
			m.m[11] = tz;
		}
		return m;
	}