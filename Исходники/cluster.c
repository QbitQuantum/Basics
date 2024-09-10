int						getGroupState(cluster_t *pcluster, HCLUSTER hClust, LPWSTR groupName)
{
	HGROUP 				hGroup;
	CLUSTER_GROUP_STATE	groupState;
	TCHAR				lpszNodeName[BUFFER_SIZE];
	DWORD				cchNodeName;
	cluster_group_t		*group;
	
	if ((hGroup = OpenClusterGroup(hClust, groupName)) == NULL)
	{
		warnError(L"Error 0x%x executing OpenCluster entry point.", GetLastError());
		return I_FALSE;
	}
	cchNodeName = BUFFER_SIZE;
	if ((groupState = GetClusterGroupState(hGroup, lpszNodeName, &cchNodeName)) == ClusterGroupStateUnknown)
	{
		warnError(L"Error 0x%x executing OpenCluster entry point.", GetLastError());
		LocalFree(lpszNodeName);
		CloseClusterGroup(hGroup);
		return I_FALSE;
	}
	PDEBUG(L"Getting Group \"%s\"", groupName);
	group = initClusterGroup(groupName, groupState);
	wcsncpy(group->nodeName, lpszNodeName, BUFFER_SIZE - 1);
	if (loadNodeName(group->savedNodeName, groupName))
		group->hasSavedNode = I_TRUE;
	if (group->hasSavedNode == I_TRUE && wcscmp(group->nodeName, group->savedNodeName) != 0)
	{
		group->bbState = USE_YELLOW;
		createNodeChangedFile(group);
		group->nodeHasChanged = I_TRUE;
	}
	if (isNodeChangedFileExists(group))
	{
		group->nodeHasChanged = I_TRUE;
		group->bbState = USE_YELLOW;
	}
	if (group->bbState == USE_YELLOW)
		pcluster->finalState = USE_YELLOW;
	saveNodeName(lpszNodeName, groupName);
	CloseClusterGroup(hGroup);
	pcluster->groups[pcluster->countGroup] = group;
	pcluster->countGroup++;
	return I_TRUE;
}