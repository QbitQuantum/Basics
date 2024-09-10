static CSSM_RETURN mds_CheckParamters(
	const BioAPI_MEMORY_FUNCS * pMemoryFunctions,
	MDS_FUNCS * pDlFunctions,
	MDS_HANDLE *hMds)
{
	if (IsBadReadPtr(pMemoryFunctions, sizeof(BioAPI_MEMORY_FUNCS)) ||
		IsBadCodePtr((CSSM_PROC_ADDR)pMemoryFunctions->Malloc_func) ||
		IsBadCodePtr((CSSM_PROC_ADDR)pMemoryFunctions->Free_func) ||
		IsBadCodePtr((CSSM_PROC_ADDR)pMemoryFunctions->Calloc_func) ||
		IsBadCodePtr((CSSM_PROC_ADDR)pMemoryFunctions->Realloc_func))
	{
		return CSSMERR_DL_INVALID_POINTER;
	}

	if (IsBadWritePtr(pDlFunctions, sizeof(MDS_FUNCS_PTR)))
	{
		return CSSMERR_DL_INVALID_POINTER;
	}

	if (IsBadWritePtr(hMds, sizeof(MDS_HANDLE)))
	{
		return CSSMERR_DL_INVALID_POINTER;
	}

	return CSSM_OK;
}