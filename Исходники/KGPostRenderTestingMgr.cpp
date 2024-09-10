int KGPostRenderTestingMgr::MakeupEffectType(const TCHAR cszTypeName[], DWORD* dwTypeValue)
{
	int nRetCode = false;
	int nResult  = false;
	TCHAR szTypeName[MAX_PATH] = {0};

	_ASSERTE(cszTypeName);
	KG_PROCESS_ERROR(cszTypeName[0] != '\0');

	nRetCode = _tcsncpy_s(szTypeName, sizeof(szTypeName), cszTypeName, strlen(cszTypeName));
	KGLOG_PROCESS_ERROR(nRetCode == 0);

	nRetCode = _mbslwr_s((unsigned char *)szTypeName, sizeof(szTypeName));//筞
	KGLOG_PROCESS_ERROR(nRetCode == 0);
	
	if (_tcscmp(szTypeName, "no_effect") == 0)
	{
		(*dwTypeValue) = 0;
	}
	else if (_tcscmp(szTypeName, "hdr") == 0)
	{
		(*dwTypeValue) |= POST_EFFECT_HDR;
	}
	else if (_tcscmp(szTypeName, "bloom") == 0)
	{
		(*dwTypeValue) |= POST_EFFECT_BLOOM;
	}
	else if (_tcscmp(szTypeName, "shockwave") == 0)
	{
		(*dwTypeValue) |= POST_EFFECT_SOCKWARE;
	}
	else if (_tcscmp(szTypeName, "shadow") == 0)
	{
		(*dwTypeValue) |= POST_EFFECT_SHADOW;
	}
	else if (_tcscmp(szTypeName, "dof") == 0)
	{
		(*dwTypeValue) |= POST_EFFECT_DOF;
	}
	else if (_tcscmp(szTypeName, "godray") == 0)
	{
		(*dwTypeValue) |= POST_EFFECT_GODRAY;
	}
	else if (_tcscmp(szTypeName, "aoe") == 0)
	{
		(*dwTypeValue) |= POST_EFFECT_AOE;
	}
	else
	{
		_ASSERTE(false);
	}

	nResult = true;
Exit0:
	return nResult;
}