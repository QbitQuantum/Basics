inline float AngleBetweenVectors( const Vec3 &v1,const Vec3 &v2 )
{
	float a = acos_tpl(v1.Dot(v2));
	Vec3 r = v1.Cross(v2);
	if (r.z < 0)
		a = -a;
	return a;
}