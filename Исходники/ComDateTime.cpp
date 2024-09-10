LPCSTR CComDateTime::Format(DWORD dwFlags, LCID lcid) const
{
	USES_CONVERSION;

	// If null, return empty string
	if (GetStatus() == null)
		return NULL;

	// If invalid, return DateTime resource string
	if (GetStatus() == invalid)
		return NULL;

	CComVariant var;
	// Don't need to trap error. Should not fail due to type mismatch
	COM_VERIFY(VarBstrFromDate(m_dt, lcid, dwFlags, &V_BSTR(&var)));
	var.vt = VT_BSTR;

   strncpy(s_strDate, OLE2CT(V_BSTR(&var)), ELEMENTS_IN(s_strDate));
   s_strDate[ELEMENTS_IN(s_strDate)-1] = '\0';
	return s_strDate;
}