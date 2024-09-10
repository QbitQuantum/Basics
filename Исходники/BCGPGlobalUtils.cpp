//------------------------------------------------------------------------//
BOOL CBCGPGlobalUtils::DecimalFromString(DECIMAL& decimal, LPCTSTR psz)
{
	USES_CONVERSION;

	if (psz == NULL || _tcslen (psz) == 0)
	{
		psz = _T("0");
	}

	VARIANTARG varBstr;
	VARIANTARG varDecimal;
	AfxVariantInit(&varBstr);
	AfxVariantInit(&varDecimal);
	V_VT(&varBstr) = VT_BSTR;
	V_BSTR(&varBstr) = SysAllocString(T2COLE(psz));
	if (FAILED(VariantChangeType(&varDecimal, &varBstr, 0, VT_DECIMAL)))
	{
		VariantClear(&varBstr);
		VariantClear(&varDecimal);
		return FALSE;
	}
	decimal = V_DECIMAL(&varDecimal);
	VariantClear(&varBstr);
	VariantClear(&varDecimal);
	return TRUE;
}