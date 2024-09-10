CGeoSquareProjectile::CGeoSquareProjectile(const float3& p1,const float3& p2,const float3& v1,const float3& v2,float w1,float w2)
: CProjectile((p1+p2)*0.5f,ZeroVector,0, false),
	p1(p1),
	p2(p2),
	v1(v1),
	v2(v2),
	w1(w1),
	w2(w2),
	r(0.5f),
	g(1.0f),
	b(0.5f),
	a(0.5f)
{
	checkCol=false;
	alwaysVisible=true;
	SetRadius(p1.distance(p2)*0.55f);
}