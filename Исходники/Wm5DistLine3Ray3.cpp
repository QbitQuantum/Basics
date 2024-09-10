Real DistLine3Ray3<Real>::GetSquared ()
{
	Vector3<Real> kDiff = mLine->Origin - mRay->Origin;
	Real a01 = -mLine->Direction.Dot(mRay->Direction);
	Real b0 = kDiff.Dot(mLine->Direction);
	Real c = kDiff.SquaredLength();
	Real det = Math<Real>::FAbs((Real)1 - a01*a01);
	Real b1, s0, s1, sqrDist;

	if (det >= Math<Real>::ZERO_TOLERANCE)
	{
		b1 = -kDiff.Dot(mRay->Direction);
		s1 = a01*b0 - b1;

		if (s1 >= (Real)0)
		{
			// Two interior points are closest, one on line and one on ray.
			Real invDet = ((Real)1)/det;
			s0 = (a01*b1 - b0)*invDet;
			s1 *= invDet;
			sqrDist = s0*(s0 + a01*s1 + ((Real)2)*b0) +
			          s1*(a01*s0 + s1 + ((Real)2)*b1) + c;
		}
		else
		{
			// Origin of ray and interior point of line are closest.
			s0 = -b0;
			s1 = (Real)0;
			sqrDist = b0*s0 + c;
		}
	}
	else
	{
		// Lines are parallel, closest pair with one point at ray origin.
		s0 = -b0;
		s1 = (Real)0;
		sqrDist = b0*s0 + c;
	}

	mClosestPoint0 = mLine->Origin + s0*mLine->Direction;
	mClosestPoint1 = mRay->Origin + s1*mRay->Direction;
	mLineParameter = s0;
	mRayParameter = s1;

	// Account for numerical round-off errors.
	if (sqrDist < (Real)0)
	{
		sqrDist = (Real)0;
	}
	return sqrDist;
}