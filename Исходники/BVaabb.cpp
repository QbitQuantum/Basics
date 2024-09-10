Vec3 BVaabb::GetSurfaceFrom(const Vec3& src, Vec3& normal)
{
	Vec3 dir = mCenter - src;
	dir.Normalize();
	Ray3 ray(src, dir);
	Ray3::IResult ret = ray.Intersects(mAABB, normal);
	return dir * ret.second;
}