/// <summary>
/// Loads and invokes the managed portion of the proxy.
/// </summary>
/// <param name="pInitMethod">Managed initialize method to be invoked.</param>
/// <param name="hSession">Handle to the installer session,
/// used for logging errors and to be passed on to the managed initialize method.</param>
/// <param name="szClassName">Name of the UI class to be loaded.
/// This must be of the form: AssemblyName!Namespace.Class</param>
/// <param name="pdwInternalUILevel">MSI install UI level passed to and returned from
/// the managed initialize method.</param>
/// <param name="puiResult">Return value of the invoked initialize method.</param>
/// <returns>True if the managed proxy was invoked successfully, or an
/// error code if there was some error. Note the initialize method itself may
/// return an error via puiResult while this method still returns true
/// since the invocation was successful.</returns>
bool InvokeInitializeMethod(_MethodInfo* pInitMethod, MSIHANDLE hSession, const wchar_t* szClassName, LPDWORD pdwInternalUILevel, UINT* puiResult)
{
	VARIANT vResult;
	VariantInit(&vResult);

	VARIANT vNull;
	vNull.vt = VT_EMPTY;

	SAFEARRAY* saArgs = SafeArrayCreateVector(VT_VARIANT, 0, 3);
	VARIANT vSessionHandle;
	vSessionHandle.vt = VT_I4;
	vSessionHandle.lVal = (LONG) hSession;
	LONG index = 0;
	HRESULT hr = SafeArrayPutElement(saArgs, &index, &vSessionHandle);
	if (FAILED(hr)) goto LExit;
	VARIANT vEntryPoint;
	vEntryPoint.vt = VT_BSTR;
	vEntryPoint.bstrVal = SysAllocString(szClassName);
	if (vEntryPoint.bstrVal == NULL)
	{
		hr = E_OUTOFMEMORY;
		goto LExit;
	}
	index = 1;
	hr = SafeArrayPutElement(saArgs, &index, &vEntryPoint);
	if (FAILED(hr)) goto LExit;
	VARIANT vUILevel;
	vUILevel.vt = VT_I4;
	vUILevel.ulVal = *pdwInternalUILevel;
	index = 2;
	hr = SafeArrayPutElement(saArgs, &index, &vUILevel);
	if (FAILED(hr)) goto LExit;
	
	hr = pInitMethod->Invoke_3(vNull, saArgs, &vResult);
	
LExit:
	SafeArrayDestroy(saArgs);
	if (SUCCEEDED(hr))
	{
		*puiResult = (UINT) vResult.lVal;
		if ((*puiResult & 0xFFFF) == 0)
		{
			// Due to interop limitations, the successful resulting UILevel is returned
			// as the high-word of the return value instead of via a ref parameter.
			*pdwInternalUILevel = *puiResult >> 16;
			*puiResult = 0;
		}
		return true;
	}