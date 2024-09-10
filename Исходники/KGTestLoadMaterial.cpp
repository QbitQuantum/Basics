int KGTestLoadMaterial::CheckFilter(const char cszMtlFile[], const char cszTexFile[])
{
	int nRetCode = false;
	int nResult  = false;
	char szMtlName[MAX_PATH] = {0};
	char szTexFile[MAX_PATH] = {0};
	char* pszResult = NULL;

	_ASSERTE(cszMtlFile);
	_ASSERTE(cszTexFile);

	//过滤材质文件F1，F2，M2相关的贴图加载错误
	nRetCode = _splitpath_s(cszMtlFile, NULL, 0, NULL, 0, szMtlName, sizeof(szMtlName), NULL, 0);
	KG_PROCESS_ERROR(nRetCode == 0);

	nRetCode = _strlwr_s(szMtlName, sizeof(szMtlName));
	KG_PROCESS_ERROR(nRetCode == 0);

	pszResult = strstr(szMtlName, "f1");
	KG_PROCESS_ERROR(pszResult == NULL);

	pszResult = strstr(szMtlName, "f2");
	KG_PROCESS_ERROR(pszResult == NULL);

	pszResult = strstr(szMtlName, "m2");
	KG_PROCESS_ERROR(pszResult == NULL);

	//过滤光照图相关的贴图加载错误
	
	nRetCode = strncpy_s(szTexFile, sizeof(szTexFile), cszTexFile, strlen(cszTexFile));
	KG_PROCESS_ERROR(nRetCode == 0);
	pszResult = strstr(szTexFile, "光照图");
	KG_PROCESS_ERROR(pszResult == NULL);

	nResult = true;
Exit0:
	if (!nResult)
	{
		m_vecFilterMtl.push_back(cszMtlFile);
	}
	return nResult;	
}