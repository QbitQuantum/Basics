CStdString ComConvertUtils::PropVariantToString(const PROPVARIANT& propVar)
{
	CStdString sPropValue;
	variant_t varPropValue;
	if (SUCCEEDED(VariantChangeType(&varPropValue, (VARIANTARG*)&propVar, VARIANT_LOCALBOOL, VT_BSTR)))
		sPropValue = varPropValue.bstrVal;
	else
	{
		//VT_BLOB and VT_LPSTR are uncommon co-ercions
		switch(propVar.vt)
		{
		case VT_BLOB:
			sPropValue.Format(_T("%s"), CStdString((LPCWSTR)propVar.blob.pBlobData).c_str());
			break;
		case VT_LPSTR:
			sPropValue.Format(_T("%hs"), propVar.pszVal);
			break;
		case VT_LPWSTR:
			sPropValue = propVar.pwszVal;
			break;
		case VT_FILETIME:
			sPropValue = FiletimeAsString(propVar.filetime);
			break;
		}
	}
	return sPropValue;
}