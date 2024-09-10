error_status_t nvdaInProcUtils_getActiveObject(handle_t bindingHandle, const wchar_t* progid, IUnknown** ppUnknown) {
	if(!progid) {
		LOG_DEBUGWARNING(L"NULL progid");
		return E_FAIL;
	}
	IID clsid;
	HRESULT res=CLSIDFromString(progid,&clsid);
	if(res!=NOERROR) {
		LOG_DEBUGWARNING(L"CLSIDFromString for "<<progid<<L" returned "<<res);
		return res;
	}
	return GetActiveObject(clsid,NULL,ppUnknown);
}