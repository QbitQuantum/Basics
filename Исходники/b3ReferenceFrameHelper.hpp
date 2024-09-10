	static btTransform getTransformWorldToLocal(const btTransform& localObjectCenterOfMassTransform, const btTransform& transform)
	{
		return localObjectCenterOfMassTransform.inverse() * transform;  // transforms the axis from the local frame into the world frame
	}