_Check_return_ HRESULT
DsWrapTypedData(
	_In_ DbgScriptHostContext* hostCtxt,
	_In_z_ const char* name,
	_In_ const DEBUG_TYPED_DATA* typedData,
	_Out_ DbgScriptTypedObject* typObj)
{
	HRESULT hr = StringCchCopyA(STRING_AND_CCH(typObj->Name), name);
	assert(SUCCEEDED(hr));

	typObj->TypedData = *typedData;
	typObj->TypedDataValid = true;

	hr = fillTypeAndModuleName(
		hostCtxt,
		typObj->TypedData.TypeId,
		typObj->TypedData.ModBase,
		typObj);
	if (FAILED(hr))
	{
		goto exit;
	}
exit:
	return hr;
}