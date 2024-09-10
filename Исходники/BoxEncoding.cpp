BSTR CBoxEncoding::BinToStr(VARIANT& var, VARIANT &varCP)
{
	CBoxBinPtr varPtr(var);
	UINT nCodePage;

	if(varCP.vt == VT_ERROR)
		nCodePage = _AtlGetConversionACP();
	else
	{
		CComVariant varTemp;

		varTemp.ChangeType(VT_I4, &varCP);
		if(varTemp.vt == VT_I4)
			nCodePage = varTemp.lVal;
		else
			AfxThrowOleException(TYPE_E_TYPEMISMATCH);
	}

	int _nTempCount = ::MultiByteToWideChar(nCodePage, 0, varPtr, varPtr.m_nSize, NULL, NULL);
	BSTR bstr = ::SysAllocStringLen(NULL, _nTempCount);
	if(bstr != NULL)
		::MultiByteToWideChar(nCodePage, 0, varPtr, varPtr.m_nSize, bstr, _nTempCount);
	return bstr;
}