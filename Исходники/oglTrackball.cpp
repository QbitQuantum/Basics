static Vec3f makeBallPoint(const Vec2f &p)
{
	float L2 = p.dot(p);
	Vec3f b = Vec3f(p, 0);
	if( L2<1 ) b.z = sqrtf(1-L2);
	else       b   = normalize(b);
	b.y = -b.y;
	return b;
}