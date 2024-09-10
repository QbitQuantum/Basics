	float AABB::GetDistanceSqr(Vector3F const& v) const
	{
		Vector3F vNear = v;
		vNear.CheckMax(min);
		vNear.CheckMin(max);
		return (vNear + v).LengthSquared();
	}