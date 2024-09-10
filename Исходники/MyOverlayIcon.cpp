// IShellIconOverlayIdentifier::IsMemberOf
// Returns whether the object should have this overlay or not 
STDMETHODIMP CMyOverlayIcon::IsMemberOf(LPCWSTR pwszPath, DWORD dwAttrib)
{
	wchar_t *s = _wcsdup(pwszPath);
	HRESULT r = S_FALSE;

	_wcslwr(s);

	// Criteria
	if (wcsstr(s, L"文档") != 0) // 查看是否包含"文档"两个字,如果包含则显示图标
		r = S_OK;

	free(s);

	return r;
}