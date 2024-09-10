void LLPathfindingManager::sendRequestGetNavMeshForRegion(LLPathfindingNavMeshPtr navMeshPtr, LLViewerRegion *pRegion, const LLPathfindingNavMeshStatus &pNavMeshStatus)
{
	if ((pRegion == NULL) || !pRegion->isAlive())
	{
		navMeshPtr->handleNavMeshNotEnabled();
	}
	else
	{
		std::string navMeshURL = getRetrieveNavMeshURLForRegion(pRegion);

		if (navMeshURL.empty())
		{
			navMeshPtr->handleNavMeshNotEnabled();
		}
		else
		{
			navMeshPtr->handleNavMeshStart(pNavMeshStatus);
			LLHTTPClient::ResponderPtr responder = new NavMeshResponder(navMeshURL, pNavMeshStatus.getVersion(), navMeshPtr);

			LLSD postData;
			LLHTTPClient::post(navMeshURL, postData, responder);
		}
	}
}