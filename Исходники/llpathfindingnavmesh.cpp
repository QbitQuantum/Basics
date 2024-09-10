bool LLPathfindingNavMesh::hasNavMeshVersion(const LLPathfindingNavMeshStatus &pNavMeshStatus) const
{
	return ((mNavMeshStatus.getVersion() == pNavMeshStatus.getVersion()) &&
		((mNavMeshRequestStatus == kNavMeshRequestStarted) || (mNavMeshRequestStatus == kNavMeshRequestCompleted) ||
		((mNavMeshRequestStatus == kNavMeshRequestChecking) && !mNavMeshData.empty())));
}