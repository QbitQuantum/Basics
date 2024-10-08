bool Circle::hits(Circle& A, Vec2& normal)
{
	Vec2 u = A.c - c;
	if( u.length() <= r + A.r )
	{
		u = u.normalize();
		normal = u;
		// Make sure circles never overlap--at most
		// they can be tangent.
		A.c = c + (normal * (r + A.r));

		return true;
	}
	return false;
}