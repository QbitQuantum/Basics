// in case either MyCoCreateInstanceEx is directly instead of from MyCoCreateInstance, or MyCoCreateInstanceEx is called from MyCoCreateInstance but MyCoCreateInstance failed to get hooked
HOOKFUNC HRESULT STDAPICALLTYPE MyCoCreateInstanceEx(REFCLSID Clsid, LPUNKNOWN punkOuter, DWORD dwClsCtx, struct _COSERVERINFO* pServerInfo, DWORD dwCount, struct tagMULTI_QI* pResults)
{
	debuglog(LCF_MODULE, __FUNCTION__ "(clsid=0x%X, dwCount=%d) called.\n", Clsid.Data1, dwCount);

	// check for creating custom objects that skip COM
//	DEFINE_LOCAL_GUID(IID_IUnknown,0x00000000,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);
	for(DWORD i = 0; i < dwCount; i++)
	{
		if(TrySoundCoCreateInstance(*pResults[i].pIID, (LPVOID*)&pResults[i].pItf))
		{
			pResults[i].hr = S_OK;
			HRESULT rv = S_OK;
			bool anyok = false;
			for(DWORD j = 0; j < dwCount; j++)
			{
				if(i != j)
				{
					pResults[j].hr = pResults[i].pItf->QueryInterface(*pResults[j].pIID, (LPVOID*)pResults[j].pItf);
					if(FAILED(pResults[j].hr))
						rv = pResults[j].hr;
					else
						anyok = true;
				}
			}
			if(anyok && FAILED(rv))
				rv = CO_S_NOTALLINTERFACES;
			return rv;
		}
	}

	// regular creation
	HRESULT rv = CoCreateInstanceEx(Clsid, punkOuter, dwClsCtx, pServerInfo, dwCount, pResults);
	for(DWORD i = 0; i < dwCount; i++)
		if(SUCCEEDED(pResults[i].hr))
			HookCOMInterface(*pResults[i].pIID, (LPVOID*)&pResults[i].pItf);
	return rv;
}