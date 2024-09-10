void  CFb2EpubConverterPaths::ReadTargets(LPTSTR strINILocation)
{
	ReleaseTargets();

	WCHAR temp[PATH_SIZE+1];
	::ZeroMemory(temp,sizeof(WCHAR)*PATH_SIZE);
	UINT count = ::GetPrivateProfileInt(TARGETS_SECTION,L"TargetsCount",0,strINILocation);	
	if ( count <= 0 )
	{
		return;
	}
	target* pTempTargets = new target[count];
	::ZeroMemory(pTempTargets,count*sizeof(target));
	WCHAR section[1024];
	for (UINT i=1; i <= count; i ++ )
	{
		::ZeroMemory(section,sizeof(WCHAR)*1024);
		wsprintf(section,L"Target%d",i);
		::ZeroMemory(temp,sizeof(WCHAR)*PATH_SIZE);
		target tempTarget;
		bool bAdd = (::GetPrivateProfileInt(section,L"ShowInShell",1,strINILocation) == 1);
		if ( bAdd )
		{
			DWORD dwRes = ::GetPrivateProfileString(section,L"TargetPath",NULL,temp,1024,strINILocation);
			if (dwRes != 0) 
			{
				tempTarget.path = _wcsdup(temp);
				::ZeroMemory(temp,sizeof(WCHAR)*PATH_SIZE);
				DWORD dwRes = ::GetPrivateProfileString(section,L"TargetName",NULL,temp,1024,strINILocation);
				if (dwRes == 0) 
				{
					tempTarget.name = L"";
				}
				else
				{
					 tempTarget.name = _wcsdup(temp);
				}
				pTempTargets[m_uiTargetsCount++] = tempTarget;
			}
		}
	}
	if ( m_uiTargetsCount > 0 ) // if at least one target detected
	{
		m_pTargetsArray	=	new target[m_uiTargetsCount];
		for(UINT32 i=0; i < m_uiTargetsCount; i++ )
		{
			m_pTargetsArray[i] = pTempTargets[i];
		}
	}
	::ZeroMemory(pTempTargets,count*sizeof(target));
	delete []pTempTargets;
}