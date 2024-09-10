std::string stringifyVarDesc(VARDESC* varDesc, ITypeInfo* pti) 
{
	CComPtr<ITypeInfo> pTypeInfo(pti);
	std::ostringstream oss;
	if(varDesc->varkind == VAR_CONST) 
		oss<< "const ";

	oss<< stringifyTypeDesc(&varDesc->elemdescVar.tdesc, pTypeInfo);
	CComBSTR bstrName;
	HRESULT hr(pTypeInfo->GetDocumentation(varDesc->memid, &bstrName, 0, 0, 0));
	if(hr) 
		return "UnknownName";

	char ansiName[MAX_PATH];
	WideCharToMultiByte(CP_ACP, 0, bstrName, bstrName.Length() + 1, ansiName, MAX_PATH, 0, 0);

	oss<< ' '<< ansiName;
	if(varDesc->varkind != VAR_CONST) 
		return oss.str();

	oss<< " = ";
	CComVariant variant;
	hr = VariantChangeType(&variant, varDesc->lpvarValue, 0, VT_BSTR);
	if(hr) 
		oss<< "???";
	else 
	{
		WideCharToMultiByte(CP_ACP, 0, variant.bstrVal, SysStringLen(variant.bstrVal) + 1, ansiName, MAX_PATH, 0, 0);
		oss<< ansiName;
	}

	return oss.str();
}