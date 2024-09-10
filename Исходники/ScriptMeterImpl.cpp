BOOL CScriptMeterImpl::AddDefaultScriptItem()
{
	HRESULT hr;
	hr = scriptPtr->AddTypeLib(LIBID_COMMETERSLib, 1, 0, 0);

	if (!SUCCEEDED(hr))
		return false;

	BOOL ret = AddScriptItem(ACTIVESCRIPT_HOST_NAME, (IMeter*)this);
#ifdef CONNECTABLE
	IDispatch *pDispatch;
	scriptPtr->GetScriptDispatch(NULL, &pDispatch);
	pDispatch->Release();
	pUtils->put_Script(pDispatch);
	pUtils->put_ScriptHost(this);

	AddScriptItem(UTILS_NAME, pUtils, SCRIPTITEM_ISVISIBLE);
#endif

	IClientModel *_model = 0;
	get_Model(&_model);
	if (_model)
	{
		ret = AddScriptItem(MODEL_NAME, _model, SCRIPTITEM_ISVISIBLE | MY_SCRIPTITEM_WEAK);
		model->Release();
	}
	else
		AtlTrace("Model is not set in ScriptMeterImpl\n");

	return ret;
}