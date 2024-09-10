	float Distance(const XMVECTOR& v1, const XMVECTOR& v2)
	{
		XMVECTOR& vectorSub = XMVectorSubtract(v1, v2);
		XMVECTOR& length = XMVector3Length(vectorSub);

		float Distance = 0.0f;
		XMStoreFloat(&Distance, length);
		return Distance;
	}