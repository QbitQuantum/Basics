LPWSTR WINAPI StringDupW(_In_ HANDLE hHeap, _In_ LPCWSTR lpszString)
{
	LPWSTR lpszCopy;
	size_t cbCopy;
	HRESULT hr;

	if (!lpszString)
		return NULL;

	hr = StringCbLengthW(lpszString, (STRSAFE_MAX_CCH-1) * sizeof(WCHAR), &cbCopy);
	if (FAILED(hr))
		return NULL;

	if ((cbCopy + sizeof(WCHAR)) <= cbCopy)
		return NULL;

	cbCopy += sizeof(WCHAR);
	lpszCopy = (LPWSTR) HeapAlloc(hHeap, HEAP_ZERO_MEMORY, cbCopy);
	if (!lpszCopy)
		return NULL;

	hr = StringCbCopyNW(lpszCopy, cbCopy, lpszString, cbCopy);
	if (FAILED(hr)) {
		HeapSafeFree(hHeap, 0, lpszCopy);
		return NULL;
	}

	return lpszCopy;
}