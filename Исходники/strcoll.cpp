long CStringCollect::Remove(const VARIANT FAR& removeValue)
{
	int nIndex = -1;

	VARIANT varTemp;
	VariantInit(&varTemp);
	const VARIANT* pvar = &removeValue;
	if (removeValue.vt != VT_BSTR)
	{
		if (VariantChangeType(&varTemp, (VARIANT*)&removeValue, 0, VT_I4) == NOERROR)
			pvar = &varTemp;
		else if (VariantChangeType(&varTemp, (VARIANT*)&removeValue, 0, VT_BSTR) == NOERROR)
			pvar = &varTemp;
		else
			AfxThrowOleException(DISP_E_TYPEMISMATCH);
	}
	if (pvar->vt == VT_BSTR)
		nIndex = (int)Find(CString(pvar->bstrVal));
	else if (pvar->vt == VT_I4)
		nIndex = (int)pvar->lVal;
	VariantClear(&varTemp);

	CheckIndex(nIndex);

	m_strArray.RemoveAt(nIndex);
	return (long)m_strArray.GetSize();
}