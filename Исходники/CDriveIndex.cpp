void CDriveIndex::FindInJournal(wstring &strQuery, const WCHAR* &szQueryLower, DWORDLONG QueryFilter, DWORDLONG QueryLength, wstring * strQueryPath, vector<T> &rgJournalIndex, vector<SearchResultFile> &rgsrfResults, unsigned int iOffset, BOOL bEnhancedSearch, int maxResults, int &nResults)
{
	for(unsigned int j = 0; j != rgJournalIndex.size(); j++)
	{
		IndexedFile* i = (IndexedFile*)&rgJournalIndex[j];
		DWORDLONG Length = (i->Filter & 0xE000000000000000ui64) >> 61ui64; //Bits 61-63 for storing lengths up to 8
		DWORDLONG Filter = i->Filter & 0x1FFFFFFFFFFFFFFFui64; //All but the last 3 bits
		if((Filter & QueryFilter) == QueryFilter && QueryLength <= Length)
		{
			USNEntry file = FRNToName(i->Index);
			float MatchQuality;
			if(bEnhancedSearch)
				MatchQuality = FuzzySearch(file.Name, strQuery);
			else
			{
				wstring szLower(file.Name);
				for(unsigned int j = 0; j != szLower.length(); j++)
					szLower[j] = tolower(szLower[j]);
				MatchQuality = szLower.find(strQuery) != -1;
			}

			if(MatchQuality > 0.6f)
			{
				nResults++;
				if(maxResults != -1 && nResults > maxResults)
				{
					nResults = -1;
					break;
				}
				SearchResultFile srf;
				srf.Filename = file.Name;
				srf.Path.reserve(MAX_PATH);
				Get(i->Index, &srf.Path);
				BOOL bFound = true;
				if(strQueryPath != NULL)
				{
					wstring strPathLower(srf.Path);
					for(unsigned int j = 0; j != strPathLower.length(); j++)
						strPathLower[j] = tolower(strPathLower[j]);
					bFound = strPathLower.find(*strQueryPath) != -1;
				}
				if(bFound)
				{
					//split path
					WCHAR szDrive[_MAX_DRIVE];
					WCHAR szPath[_MAX_PATH];
					WCHAR szName[_MAX_FNAME];
					WCHAR szExt[_MAX_EXT];
					_wsplitpath(srf.Path.c_str(), szDrive, szPath, szName, szExt);
					srf.Path = wstring(szDrive) + wstring(szPath);
					srf.Filter = i->Filter;
					srf.MatchQuality = MatchQuality;
					rgsrfResults.insert(rgsrfResults.end(), srf);
				}
			}
		}
	}
}