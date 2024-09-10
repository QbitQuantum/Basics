int CALLBACK CShellBrowser::SortByName(int InternalIndex1,int InternalIndex2) const
{
	if(m_bVirtualFolder)
	{
		TCHAR FullFileName1[MAX_PATH];
		LPITEMIDLIST pidlComplete1 = ILCombine(m_pidlDirectory,m_pExtraItemInfo[InternalIndex1].pridl);
		GetDisplayName(pidlComplete1,FullFileName1,SHGDN_FORPARSING);
		CoTaskMemFree(pidlComplete1);

		TCHAR FullFileName2[MAX_PATH];
		LPITEMIDLIST pidlComplete2 = ILCombine(m_pidlDirectory,m_pExtraItemInfo[InternalIndex2].pridl);
		GetDisplayName(pidlComplete2,FullFileName2,SHGDN_FORPARSING);
		CoTaskMemFree(pidlComplete2);

		BOOL IsRoot1 = PathIsRoot(FullFileName1);
		BOOL IsRoot2 = PathIsRoot(FullFileName2);

		if(IsRoot1 && !IsRoot2)
		{
			return -1;
		}
		else if(!IsRoot1 && IsRoot2)
		{
			return 1;
		}
		else if(IsRoot1 && IsRoot2)
		{
			/* If the items been compared are both drives,
			sort by drive letter, rather than display name. */
			return StrCmpLogicalW(FullFileName1,FullFileName2);
		}
	}

	std::wstring Name1 = GetNameColumnText(InternalIndex1);
	std::wstring Name2 = GetNameColumnText(InternalIndex2);

	return StrCmpLogicalW(Name1.c_str(),Name2.c_str());
}