ccGLMatrix ccGLMatrix::FromToRotation(const CCVector3& from, const CCVector3& to)
{
	float e = from.dot(to);
	float f = (e < 0 ? -e : e);
	ccGLMatrix result;
	float* mat = result.data();

	if (f > 1.0-ZERO_TOLERANCE)     //"from" and "to"-vector almost parallel
	{
		CCVector3 x;       // vector most nearly orthogonal to "from"
		x.x = (from.x > 0 ? from.x : -from.x);
		x.y = (from.y > 0 ? from.y : -from.y);
		x.z = (from.z > 0 ? from.z : -from.z);

		if (x.x < x.y)
		{
			if (x.x < x.z)
			{
				x.x = 1.0f; x.y = x.z = 0;
			}
			else
			{
				x.z = 1.0f; x.x = x.y = 0;
			}
		}
		else
		{
			if (x.y < x.z)
			{
				x.y = 1.0f; x.x = x.z = 0;
			}
			else
			{
				x.z = 1.0f; x.x = x.y = 0;
			}
		}

		CCVector3 u(x.x-from.x, x.y-from.y, x.z-from.z);
		CCVector3 v(x.x-to.x, x.y-to.y, x.z-to.z);

		float c1 = 2.0f / u.dot(u);
		float c2 = 2.0f / v.dot(v);
		float c3 = c1 * c2  * u.dot(v);

		for (unsigned i = 0; i < 3; i++)
		{
			for (unsigned j = 0; j < 3; j++)
			{
				mat[i*4+j]=  c3 * v.u[i] * u.u[j]
						   - c2 * v.u[i] * v.u[j]
						   - c1 * u.u[i] * u.u[j];
			}
			mat[i*4+i] += 1.0f;
		}
	}
	else  // the most common case, unless "from"="to", or "from"=-"to"
	{
		//hand optimized version (9 mults less)
		CCVector3 v = from.cross(to);
		float h = 1.0f/(1.0f + e);
		float hvx = h * v.x;
		float hvz = h * v.z;
		float hvxy = hvx * v.y;
		float hvxz = hvx * v.z;
		float hvyz = hvz * v.y;

		mat[0] = e + hvx * v.x;
		mat[1] = hvxy - v.z;
		mat[2] = hvxz + v.y;

		mat[4] = hvxy + v.z;
		mat[5] = e + h * v.y * v.y;
		mat[6] = hvyz - v.x;

		mat[8] = hvxz - v.y;
		mat[9] = hvyz + v.x;
		mat[10] = e + hvz * v.z;
	}

	return result;
}