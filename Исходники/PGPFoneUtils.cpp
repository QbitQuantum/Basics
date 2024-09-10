void pgp_free(void *freePtr)
{
#ifdef	PGP_MACINTOSH
	/*long len = GetPtrSize((Ptr)freePtr);
	DebugLog("free:%ld\r",GetPtrSize((Ptr)freePtr));*/
	DisposePtr((Ptr)freePtr);
#elif	PGP_WIN32
#ifdef _DEBUG
	if (!HeapValidate(heapID, 0, NULL))
		DebugLog("validation failed before freeing %p", freePtr);
#endif	// _DEBUG

	HeapFree(heapID, 0, freePtr);

#ifdef _DEBUG
	if (!HeapValidate(heapID, 0, NULL))
		DebugLog("validation failed after freeing %p", freePtr);
#endif	// _DEBUG
#endif	// PGP_WIN32
}