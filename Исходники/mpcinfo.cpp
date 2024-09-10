static bool GetFilterGraph(IFilterGraph** ppFG)
{
	if(!ppFG) return(false);

    CComPtr<IRunningObjectTable> pROT;
    if(FAILED(GetRunningObjectTable(0, &pROT)))
		return 1;

	CComPtr<IEnumMoniker> pEM;
	if(FAILED(pROT->EnumRunning(&pEM)))
		return 1;

	CComPtr<IBindCtx> pBindCtx;
	CreateBindCtx(0, &pBindCtx);

	for(CComPtr<IMoniker> pMoniker; S_OK == pEM->Next(1, &pMoniker, NULL); pMoniker = NULL)
	{
		LPOLESTR pDispName = NULL;
		if(FAILED(pMoniker->GetDisplayName(pBindCtx, NULL, &pDispName)))
			continue;

		CStringW strw(pDispName);
		
		CComPtr<IMalloc> pMalloc;
		if(FAILED(CoGetMalloc(1, &pMalloc)))
			continue;
		pMalloc->Free(pDispName);

		if(strw.Find(L"(MPC)") < 0)
			continue;

		CComPtr<IUnknown> pUnk;
		if(S_OK != pROT->GetObject(pMoniker, &pUnk))
			continue;

		CComQIPtr<IFilterGraph> pFG = pUnk;
		if(!pFG)
			continue;

		*ppFG = pFG.Detach();

		break;
	}

	return(!!*ppFG);
}