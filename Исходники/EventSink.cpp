// This is called by IE to notify us of events
// Full documentation about all the events supported by DWebBrowserEvents2 can be found at
//  http://msdn.microsoft.com/en-us/library/aa768283(VS.85).aspx
STDMETHODIMP CEventSink::Invoke(DISPID dispIdMember,REFIID riid,LCID lcid,WORD wFlags,DISPPARAMS *pDispParams,VARIANT *pVarResult,EXCEPINFO *pExcepInfo,UINT *puArgErr)
{
	UNREFERENCED_PARAMETER(lcid);
	UNREFERENCED_PARAMETER(wFlags);
	UNREFERENCED_PARAMETER(pVarResult);
	UNREFERENCED_PARAMETER(pExcepInfo);
	UNREFERENCED_PARAMETER(puArgErr);
	VARIANT v[5]; // Used to hold converted event parameters before passing them onto the event handling method
	int n;
	bool b;
	PVOID pv;
	LONG lbound,ubound,sz;

	if(!IsEqualIID(riid,IID_NULL)) return DISP_E_UNKNOWNINTERFACE; // riid should always be IID_NULL
	// Initialize the variants
	for(n=0;n<5;n++) VariantInit(&v[n]);
	if(dispIdMember==DISPID_BEFORENAVIGATE2) { // Handle the BeforeNavigate2 event
		VariantChangeType(&v[0],&pDispParams->rgvarg[5],0,VT_BSTR); // url
		VariantChangeType(&v[1],&pDispParams->rgvarg[4],0,VT_I4); // Flags
		VariantChangeType(&v[2],&pDispParams->rgvarg[3],0,VT_BSTR); // TargetFrameName
		VariantChangeType(&v[3],&pDispParams->rgvarg[2],0,VT_UI1|VT_ARRAY); // PostData
		VariantChangeType(&v[4],&pDispParams->rgvarg[1],0,VT_BSTR); // Headers
		if(v[3].vt!=VT_EMPTY) {
			SafeArrayGetLBound(v[3].parray,0,&lbound);
			SafeArrayGetUBound(v[3].parray,0,&ubound);
			sz=ubound-lbound+1;
			SafeArrayAccessData(v[3].parray,&pv);
		} else {
			sz=0;
			pv=NULL;
		}
		b=Event_BeforeNavigate2((LPOLESTR)v[0].bstrVal,v[1].lVal,(LPOLESTR)v[2].bstrVal,(PUCHAR)pv,sz,(LPOLESTR)v[4].bstrVal,((*(pDispParams->rgvarg[0].pboolVal))!=VARIANT_FALSE));
		if(v[3].vt!=VT_EMPTY) SafeArrayUnaccessData(v[3].parray);
		if(b) *(pDispParams->rgvarg[0].pboolVal)=VARIANT_TRUE;
		else *(pDispParams->rgvarg[0].pboolVal)=VARIANT_FALSE;
	}
	// Free the variants
	for(n=0;n<5;n++) VariantClear(&v[n]);
	return S_OK;
}