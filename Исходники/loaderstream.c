static HRESULT WINAPI IDirectMusicLoaderGenericStream_IStream_Write (LPSTREAM iface, const void* pv, ULONG cb, ULONG* pcbWritten) {
	ICOM_THIS_MULTI(IDirectMusicLoaderGenericStream, StreamVtbl, iface);	
	TRACE_(dmfileraw)("(%p, %p, 0x%08lX, %p): redirecting to low-level stream\n", This, pv, cb, pcbWritten);
	if (!This->pStream)
		return E_FAIL;

	return IStream_Write (This->pStream, pv, cb, pcbWritten);
}