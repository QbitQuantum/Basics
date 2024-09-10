void LLPathfindingNavMeshZone::NavMeshLocation::handleNavMesh(LLPathfindingNavMesh::ENavMeshRequestStatus pNavMeshRequestStatus, const LLPathfindingNavMeshStatus &pNavMeshStatus, const LLSD::Binary &pNavMeshData)
{
	llassert(mRegionUUID == pNavMeshStatus.getRegionUUID());

	if ((pNavMeshRequestStatus == LLPathfindingNavMesh::kNavMeshRequestCompleted) &&
		(!mHasNavMesh || (mNavMeshVersion != pNavMeshStatus.getVersion())))
	{
		llassert(!pNavMeshData.empty());
		mHasNavMesh = true;
		mNavMeshVersion = pNavMeshStatus.getVersion();
		llassert(LLPathingLib::getInstance() != NULL);
		if (LLPathingLib::getInstance() != NULL)
		{
			LLPathingLib::getInstance()->extractNavMeshSrcFromLLSD(pNavMeshData, mDirection);
		}
	}

	mRequestStatus = pNavMeshRequestStatus;
	mNavMeshStatus = pNavMeshStatus.getStatus();
	mLocationCallback();
}