std::vector<Group*> UserUtilities::GetGroupList()
{
	std::vector<Group*> lstGroups;
	LOCALGROUP_INFO_1* grpInfo = NULL;
	LOCALGROUP_INFO_1* tempgrpInfo;
	DWORD entriesRead = 0;
	DWORD totalEntries = 0;
	DWORD resume = 0;

	int res = NetLocalGroupEnum(NULL, 1, (LPBYTE*)&grpInfo, -1, &entriesRead, &totalEntries, &resume);
	if(entriesRead > 0)
	{
		tempgrpInfo = grpInfo;
		for(int i = 0;i < entriesRead;i++)
		{
			Group* grp = new Group();
			grp->m_StrGroupName = tempgrpInfo->lgrpi1_name;
			grp->m_StrDescription = tempgrpInfo->lgrpi1_comment;
			lstGroups.push_back(grp);
			
			tempgrpInfo++;
		}
	}

	if(grpInfo)
	{
		NetApiBufferFree(grpInfo);
		grpInfo = NULL;
	}

	return lstGroups;
}