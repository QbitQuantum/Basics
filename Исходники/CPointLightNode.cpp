	bool CPointLightNode::intersectRay(const math::SRay& ray, f32* pDist) const
	{
		XMVECTOR origin = XMLoadFloat3(&ray.Origin);
		origin = XMVectorSetW(origin, 1.0f);
		XMVECTOR direction = XMLoadFloat3(&ray.Direction);
		direction = XMVectorSetW(direction, 0);

		return intersectRay(origin, direction, pDist);
	}