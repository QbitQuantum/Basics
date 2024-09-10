//----------------------------------------------------------------------------
bool Bound::TestIntersection (const APoint& origin, const AVector& direction,
							  float tmin, float tmax) const
{
	if (GetRadius() == 0.0f)
	{
		return false;
	}

	AVector diff;
	float a0, a1, discr;

	if (tmin == -Mathf::MAX_REAL)
	{
		assertion(tmax == Mathf::MAX_REAL,
			"tmax must be infinity for a line.\n");

		// Test for sphere-line intersection.
		diff = origin - mCenter;
		a0 = diff.Dot(diff) - mRadius*mRadius;
		a1 = direction.Dot(diff);
		discr = a1*a1 - a0;
		return discr >= 0.0f;
	}

	if (tmax == Mathf::MAX_REAL)
	{
		assertion(tmin == 0.0f, "tmin must be zero for a ray.\n");

		// Test for sphere-ray intersection.
		AVector diff = origin - mCenter;
		a0 = diff.Dot(diff) - mRadius*mRadius;
		if (a0 <= 0.0f)
		{
			// The ray origin is inside the sphere.
			return true;
		}
		// else: The ray origin is outside the sphere.

		a1 = direction.Dot(diff);
		if (a1 >= 0.0f)
		{
			// The ray forms an acute angle with diff, and so the ray is
			// directed from the sphere.  Thus, the ray origin is outside
			// the sphere, and points P+t*D for t >= 0 are even farther
			// away from the sphere.
			return false;
		}

		discr = a1*a1 - a0;
		return discr >= 0.0f;
	}

	assertion(tmax > tmin, "tmin < tmax is required for a segment.\n");

	// Test for sphere-segment intersection.
	float segExtent = 0.5f*(tmin + tmax);
	APoint segOrigin = origin + segExtent*direction;

	diff = segOrigin - mCenter;
	a0 = diff.Dot(diff) - mRadius*mRadius;
	a1 = direction.Dot(diff);
	discr = a1*a1 - a0;
	if (discr < 0.0f)
	{
		return false;
	}

	float tmp0 = segExtent*segExtent + a0;
	float tmp1 = 2.0f*a1*segExtent;
	float qm = tmp0 - tmp1;
	float qp = tmp0 + tmp1;
	if (qm*qp <= 0.0f)
	{
		return true;
	}

	return qm > 0.0f && Mathf::FAbs(a1) < segExtent;
}