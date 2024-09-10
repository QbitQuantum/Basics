	void Sphere::merge(const Vector3& point)
	{
		float dist = point.distance(mCenter);
		mRadius = std::max(mRadius, dist);
	}