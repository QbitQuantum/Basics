std::function<bool(HitableRef, HitableRef)> BVHNode::comparator(size_t aAxis) const
{
	auto boxCompare = [=](const HitableRef &lhs, const HitableRef &rhs) -> bool
	{
		AABB boxLeft;
		AABB boxRight;
		if (!lhs->boundingBox(0.0f, 0.0f, boxLeft) || !rhs->boundingBox(0.0f, 0.0f, boxRight))
		{
			std::cerr << "No bounding box in BVH node constructor." << std::endl;
		}
		return boxLeft.min()[aAxis] < boxRight.min()[aAxis];
	};

	return boxCompare;
}