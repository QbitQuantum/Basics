    bool SDAPI SDSetProcessAttr(SDHANDLE handle, const SProcessAttr &pAttr)
    {
#if (defined(WIN32) || defined(WIN64))
		if (pAttr.secInfo.bSet)
		{
			PROCESS_INFORMATION & pInfo = s_processIndexer.Get((uint32)handle); 
			uint32 ret = SetSecurityInfo(pInfo.hProcess,
				pAttr.secInfo.objectType,
				pAttr.secInfo.securityInfo,
				pAttr.secInfo.psidOwner,
				pAttr.secInfo.psidGroup,
				pAttr.secInfo.pDacl,
				pAttr.secInfo.pSacl
				);
			if (ret != ERROR_SUCCESS)
			{
				return false; 
			}
		}
#else 
#endif // 
        return false;
    }