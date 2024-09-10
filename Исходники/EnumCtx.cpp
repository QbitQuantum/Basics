tERROR EnumContext::SetInfectedObjectName(hSTRING hStrInfectedObject)
{
	tERROR error = errOK;
	hash_t	CRC64;
	tDWORD dSize;

	if (!hStrInfectedObject)
		return errOK;
	m_dwFlags |= CURE_ACTION_ACTIVE;
	m_wFileNames = hStrInfectedObject;
	error=hStrInfectedObject->Length(&dSize);
	dSize++;
	if (PR_SUCC(error) && !m_sFullFilePathName.reserve_len(dSize/*+1*/)) 
		error = errNOT_ENOUGH_MEMORY;
	if(PR_SUCC(error))
		error=hStrInfectedObject->ExportToBuff(&dSize,cSTRING_WHOLE,m_sFullFilePathName,dSize*2,cCP_UNICODE,cSTRING_Z); 
	if(PR_SUCC(error))
		_wcslwr(m_sFullFilePathName);
	if (PR_SUCC(error))
		dSize=wcslen(m_sFullFilePathName);
	if (PR_SUCC(error))
		error = Hash_Calc_Quick(&CRC64, m_sFullFilePathName, dSize);
	if (PR_SUCC(error))
	{
		cAutoNativeCS _lock(&m_pStartUpEnum->m_sCommonCriticalSection);
		if (m_pStartUpEnum->m_bHashKnownFilesExist)
		{
			bool bFullScan=cFALSE;
			if (errHASH_FOUND != _Hash_Find(m_pStartUpEnum->m_pHashKnownFiles,CRC64.h1,CRC64.h2,&bFullScan))
			{
				PR_TRACE((m_pStartUpEnum,prtNOTIFY,"startupenum2\t<CleanUp> <%S> is not found in m_pHashKnownFiles ",(wchar_t*)m_sFullFilePathName));
				return error=errNOT_FOUND;
			}
			if (bFullScan)
				m_pStartUpEnum->m_bHashKnownFilesExist=0;
		}
	}
	PR_TRACE((m_pStartUpEnum,prtNOTIFY,"startupenum2\t<CleanUp> started for <%S> file",(wchar_t*)m_sFullFilePathName));
	wchar_t* ptr;
	if(ptr=wcsrchr(m_sFullFilePathName,'\\'))
	{
		m_sShortInfectedName = ptr+1;
		if(ptr=wcschr(m_sShortInfectedName, '.'))
			*ptr=0;
		if(ptr=wcschr(m_sShortInfectedName, '~'))
			*ptr=0;
	}

	m_pStartUpEnum->heapAlloc((tPTR*)&pFileToDel,sizeof(UNLOAD_PROFILE_NAMES));
	if (pFileToDel)
	{
		pFileToDel->Count=0;
		pFileToDel->cProfileName[0]=0;
	}
//	_Hash_Done(*m_pStartUpEnum,m_pHashInput);
	_Hash_Done(*m_pStartUpEnum,m_pHashParse);
//	m_pHashInput = NULL;
	m_pHashParse = NULL;
	return error;
}