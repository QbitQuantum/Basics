// 写HTML到document
void CLog::WriteDocument(const CString& content)
{
	SAFEARRAY *arr = SafeArrayCreateVector(VT_VARIANT, 0, 1);
	VARIANT *str = NULL;
	if (FAILED(SafeArrayAccessData(arr, (LPVOID*)&str)))
		return;
	str->vt = VT_BSTR;
	str->bstrVal = content.AllocSysString();
	SafeArrayUnaccessData(arr);
	m_logDocument->write(arr);
	SafeArrayDestroy(arr);
}