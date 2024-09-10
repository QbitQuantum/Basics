MATH_IGNORE_UNUSED_VARS_WARNING

RANDOMIZED_TEST(AABBPBVolumeIntersect)
{
	vec pt = vec::RandomBox(rng, POINT_VEC_SCALAR(-SCALE), POINT_VEC_SCALAR(SCALE));
	Frustum b = RandomFrustumContainingPoint(pt);
	AABB a = RandomAABBContainingPoint(pt, 10.f);
	assert(a.Intersects(b));
	assert(b.Intersects(a));

	bool contained = b.Contains(a);

	vec centerPoint = b.CenterPoint();
	assert(b.Contains(b.CenterPoint()));

	PBVolume<6> pbVolume = ToPBVolume(b);
	assert(pbVolume.Contains(b.CenterPoint()));
	CullTestResult r = pbVolume.InsideOrIntersects(a);
	assert(r == TestInside || r == TestNotContained);
	if (contained)
		assert(r == TestInside);
}