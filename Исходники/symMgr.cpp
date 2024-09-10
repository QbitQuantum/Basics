ULONG	getNtBase()
{
	DWORD	dwsize;
	DWORD	dwSizeReturn;
	PUCHAR	pBuffer	=	NULL;
	
	PSYSTEM_MODULE_INFORMATION	pSmi=NULL;
	PSYSTEM_MODULE	psm=NULL;
	NTSTATUS	ntStatus=STATUS_UNSUCCESSFUL;
	ntStatus = NtQuerySystemInformation(SystemModuleInformation, pSmi, 0, &dwSizeReturn);
	
	if (ntStatus!=STATUS_INFO_LENGTH_MISMATCH)
	{
		
		MessageBoxA(NULL,"fuck1",NULL,NULL);
		return 0;
	}
	dwsize	=	dwSizeReturn*2;
	pSmi	=	(PSYSTEM_MODULE_INFORMATION)new char[dwsize];
	if (pSmi==NULL)
	{
		MessageBoxA(NULL,"fuck2",NULL,NULL);
		return 0;
	}
	
	ntStatus = NtQuerySystemInformation(SystemModuleInformation, pSmi,dwsize, &dwSizeReturn);
	
	if (ntStatus!=STATUS_SUCCESS)
	{
		MessageBoxA(NULL,"fuck3",NULL,NULL);
		return 0;
	}

	DWORD	dwcount	=	pSmi->uCount;
	psm	=	pSmi->aSM;
	DWORD	ntbase	=	psm->Base;
	strcpy(osname, psm->ImageName);
	delete pSmi;
	
	return ntbase;
}