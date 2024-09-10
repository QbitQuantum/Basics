int CSettingsParser::ParseTreeRec( const wchar_t *str, std::vector<TreeItem> &items, CString *names, int level )
{
	size_t start=items.size();
	while (*str)
	{
		wchar_t token[256];
		str=GetToken(str,token,_countof(token),L", \t");
		if (token[0])
		{
			// 
			bool bFound=false;
			for (int i=0;i<level;i++)
				if (_wcsicmp(token,names[i])==0)
				{
					bFound=true;
					break;
				}
				if (!bFound)
				{
					TreeItem item={token,-1};
					items.push_back(item);
				}
		}
	}
	size_t end=items.size();
	if (start==end) return -1;

	TreeItem item={L"",-1};
	items.push_back(item);

	if (level<MAX_TREE_LEVEL-1)
	{
		for (size_t i=start;i<end;i++)
		{
			wchar_t buf[266];
			Sprintf(buf,_countof(buf),L"%s.Items",items[i].name);
			const wchar_t *str2=FindSetting(buf);
			if (str2)
			{
				names[level]=items[i].name;
				// these two statements must be on separate lines. otherwise items[i] is evaluated before ParseTreeRec, but
				// the items vector can be reallocated inside ParseTreeRec, causing the address to be invalidated -> crash!
				int idx=ParseTreeRec(str2,items,names,level+1);
				items[i].children=idx;
			}
		}
	}
	return (int)start;
}