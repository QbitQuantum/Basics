		bool IntersectTwoAabbs(const SAxisAlignedBox& aabb1, const SAxisAlignedBox& aabb2)
		{
			XMVECTOR CenterA = XMLoadFloat3(&aabb1.Center);
			XMVECTOR ExtentsA = XMLoadFloat3(&aabb1.Extents);

			XMVECTOR CenterB = XMLoadFloat3(&aabb2.Center);
			XMVECTOR ExtentsB = XMLoadFloat3(&aabb2.Extents);

			XMVECTOR MinA = CenterA - ExtentsA;
			XMVECTOR MaxA = CenterA + ExtentsA;

			XMVECTOR MinB = CenterB - ExtentsB;
			XMVECTOR MaxB = CenterB + ExtentsB;

			// for each i in (x, y, z) if a_min(i) > b_max(i) or b_min(i) > a_max(i) then return FALSE
			XMVECTOR Disjoint = XMVectorOrInt(XMVectorGreater(MinA, MaxB), XMVectorGreater(MinB, MaxA));

			return !XMVector3AnyTrue(Disjoint);
		}