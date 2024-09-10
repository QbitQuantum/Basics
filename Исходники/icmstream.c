static ULONG WINAPI ICMStream_fnRelease(IAVIStream* iface)
{
  IAVIStreamImpl *This = impl_from_IAVIStream(iface);
  ULONG ref = InterlockedDecrement(&This->ref);

  TRACE("(%p) -> %d\n", iface, ref);

  if (ref == 0) {
    /* destruct */
    if (This->pg != NULL) {
      AVIStreamGetFrameClose(This->pg);
      This->pg = NULL;
    }
    if (This->pStream != NULL) {
      IAVIStream_Release(This->pStream);
      This->pStream = NULL;
    }
    if (This->hic != NULL) {
      if (This->lpbiPrev != NULL) {
	ICDecompressEnd(This->hic);
	HeapFree(GetProcessHeap(), 0, This->lpbiPrev);
	This->lpbiPrev = NULL;
	This->lpPrev   = NULL;
      }
      ICCompressEnd(This->hic);
      This->hic = NULL;
    }
    if (This->lpbiCur != NULL) {
      HeapFree(GetProcessHeap(), 0, This->lpbiCur);
      This->lpbiCur = NULL;
      This->lpCur   = NULL;
    }
    if (This->lpbiOutput != NULL) {
      HeapFree(GetProcessHeap(), 0, This->lpbiOutput);
      This->lpbiOutput = NULL;
      This->cbOutput   = 0;
    }
    if (This->lpbiInput != NULL) {
      HeapFree(GetProcessHeap(), 0, This->lpbiInput);
      This->lpbiInput = NULL;
      This->cbInput   = 0;
    }

    HeapFree(GetProcessHeap(), 0, This);

    return 0;
  }

  /* also release reference to the nested stream */
  if (This->pStream != NULL)
    IAVIStream_Release(This->pStream);

  return ref;
}