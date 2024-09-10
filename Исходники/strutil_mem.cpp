BOOL WINAPI HeapSafeFree(_Inout_ HANDLE hHeap, _In_ DWORD dwFlags, _In_opt_ _Post_ptr_invalid_ LPVOID lpMem)
{
	SIZE_T cbMem;
	BOOL res;

	if (!hHeap || !lpMem)
		return FALSE;

	if (!HeapLock(hHeap))
		return FALSE;

	cbMem = HeapSize(hHeap, dwFlags, lpMem);
	if (cbMem > 0 && cbMem != (SIZE_T)-1)
		SecureZeroMemory(lpMem, cbMem);

	res = HeapFree(hHeap, dwFlags, lpMem);

	HeapUnlock(hHeap);

	return res;
}