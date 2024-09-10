float MapperOp::angle(const Vec2f& v1, const Vec2f& v2)
{
	return acos( v1.dot(v2) / (v1.length() * v2.length()) );
}