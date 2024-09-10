STDMETHODIMP CZ80Assembler::AddDefine(BSTR bstrName, VARIANT varValue)
{
	if (V_VT(&varValue) == VT_EMPTY || V_VT(&varValue) == VT_ERROR)
	{
		V_VT(&varValue) = VT_UI4;
		V_UI4(&varValue) = 1;
	}

	VARIANT varDefine;
	VariantInit(&varDefine);
	V_VT(&varDefine) = VT_BSTR;
	V_BSTR(&varDefine) = SysAllocString(L"");
	HRESULT hr = VariantChangeType(&varDefine, &varValue, 0, VT_BSTR);
	if (FAILED(hr))
	{
		return hr;
	}

	CW2A szName(bstrName);

	bool fRedefined = false;
	define_t *define = add_define(strdup(szName), &fRedefined);

	if (define != NULL)
	{
		CW2A szContents(V_BSTR(&varDefine));
		define->contents = strdup(szContents);
		return S_OK;
	}
	else
	{
		return E_FAIL;
	}
}