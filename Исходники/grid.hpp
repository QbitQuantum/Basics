	Vec4f PlaneEquation(void) const
	{
		return Vec4f(Normal(), -Dot(Normal(), _point));
	}