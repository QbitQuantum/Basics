static inline bool tryAxis(const ShapeBox &boxA, const Transform &boxATransform, 
	const ShapeBox &boxB, const Transform &boxBTransform, Vec3 axis, 
	const Vec3 &separation, unsigned int index, Scalar &smallestPenetration, unsigned int &smallestCase)
{
	// Omit almost parallel axes and normalize
	if (axis.dot(axis) < 0.0001) return true;
	axis.normalize();

	Scalar penetration = penetrationOnAxis(boxA, boxATransform, boxB, boxBTransform, axis, separation);

	if (penetration < 0) return false;

	if(penetration < smallestPenetration)
	{
		smallestPenetration = penetration;
		smallestCase = index;
	}

	return true;
}