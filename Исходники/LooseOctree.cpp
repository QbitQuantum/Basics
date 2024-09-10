	//---------------------------------------------------------------------
	bool LooseOctreeZone::isFitInChildZone(const Util::AABBPtr & aabb)
	{
		XMVECTOR halfSideSize = XMVectorReplicate((LOOSE_K * WORLD_SIZE / (2 << mDepth)) * 0.5f);

		XMVECTOR nodeSize = aabb->getSize();

		/// "&& true" to kill the warning C4800: 'BOOL' : forcing value to bool 'true' or 'false' (performance warning).
		return XMVector3LessOrEqual(nodeSize, halfSideSize) && true;
	}