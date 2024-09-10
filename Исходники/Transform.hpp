	inline Vector3 transform(const Transform& transform, const Vector3& point)
	{
		return (conjugate(transform.orientation) * (transform.position - point)) / transform.scale;
	}