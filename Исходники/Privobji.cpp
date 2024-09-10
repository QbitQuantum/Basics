STDMETHODIMP
CObjSecurity::GetInheritSource(SECURITY_INFORMATION psi, PACL pAcl, PINHERITED_FROM *ppInheritArray)
{
	DWORD dwErr = 0;
	size_t i = 0, dwSize = 0;
	PINHERITED_FROM InheritResult = NULL;

	if (mpsz_KeyForInherit == NULL)
	{
		LPCTSTR pszUnknown = _T("<unknown>");
		dwSize = lstrlen(pszUnknown) + 1;
		InheritResult = (PINHERITED_FROM)LocalAlloc(LPTR, 
			(1 + pAcl->AceCount) * sizeof(INHERITED_FROM) + dwSize * sizeof(TCHAR));
		TCHAR* DataPtr = (TCHAR*)(((LPBYTE)InheritResult) + (pAcl->AceCount * sizeof(INHERITED_FROM)));
		lstrcpy(DataPtr, pszUnknown);
		for(i = 0 ; i < pAcl->AceCount ; i++)
		{
			InheritResult[i].GenerationGap = 1;
			InheritResult[i].AncestorName = DataPtr;
		}
	}
	else
	{
		PINHERITED_FROM InheritTmp = (PINHERITED_FROM)LocalAlloc(LPTR, (1 + pAcl->AceCount) * sizeof(INHERITED_FROM));

		BOOL Container = TRUE;

		dwErr = GetInheritanceSource(mpsz_KeyForInherit, SE_REGISTRY_KEY, psi,
			Container, NULL, 0, pAcl, NULL, &ObjMap, InheritTmp);

		if (dwErr == 0)
		{
			for(i = 0 ; i < pAcl->AceCount ; i++)
			{
				LPCTSTR pszAncName = InheritTmp[i].AncestorName ? InheritTmp[i].AncestorName : _T("<not inherited>");
				dwSize += 1 + lstrlen(pszAncName);
			}

			InheritResult = (PINHERITED_FROM)LocalAlloc(LPTR, 
				(1 + pAcl->AceCount) * sizeof(INHERITED_FROM) + dwSize * sizeof(TCHAR));

			TCHAR* DataPtr = (TCHAR*)(((LPBYTE)InheritResult) + (pAcl->AceCount * sizeof(INHERITED_FROM)));

			for(i = 0 ; i < pAcl->AceCount ; i++)
			{
				LPCTSTR pszAncName = InheritTmp[i].AncestorName ? InheritTmp[i].AncestorName : _T("<not inherited>");
				lstrcpy(DataPtr, pszAncName);
				
				InheritResult[i].GenerationGap = InheritTmp[i].GenerationGap;
				InheritResult[i].AncestorName = DataPtr;

				DataPtr += lstrlen(DataPtr)+1;
			}

			FreeInheritedFromArray(InheritTmp, pAcl->AceCount, NULL);
		}
		LocalFree(InheritTmp); InheritTmp = NULL;
	}

	*ppInheritArray = InheritResult;
	return HRESULT_FROM_WIN32(dwErr);
}