// PT: modified version calls the previous function, but moves the ray origin closer to the sphere. The test accuracy is
// greatly improved as a result. This is an idea proposed on the GD-Algorithms list by Eddie Edwards.
// See: http://www.codercorner.com/blog/?p=321
bool Gu::intersectRaySphere(const PxVec3& origin, const PxVec3& dir, PxReal length, const PxVec3& center, PxReal radius, PxReal& dist, PxVec3* hit_pos)
{
	const PxVec3 x = origin - center;
	PxReal l = PxSqrt(x.dot(x)) - radius - 10.0f;

//	if(l<0.0f)
//		l=0.0f;
	l = physx::intrinsics::selectMax(l, 0.0f);

	bool status = intersectRaySphereBasic(origin + l*dir, dir, length - l, center, radius, dist, hit_pos);
	if(status)
	{
//		dist += l/length;
		dist += l;
	}
	return status;
}