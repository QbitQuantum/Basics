LPVOID
CPropertyPageEx::operator new(size_t size)
{
#ifdef _WIN32
	return HeapAlloc(GetProcessHeap(), 0, size);
#else
	LPMALLOC	pMalloc;

	if (SUCCEEDED(CoGetMalloc(MEMCTX_TASK, &pMalloc))) {
		LPVOID	lpv = pMalloc->Alloc(size);

		pMalloc->Release();
		return lpv;
	}

	return NULL;
#endif
}