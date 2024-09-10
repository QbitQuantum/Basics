static ULONG WINAPI ACMStream_fnRelease(IAVIStream* iface)
{
  IAVIStreamImpl *This = (IAVIStreamImpl *)iface;
  ULONG ref = InterlockedDecrement(&This->ref);

  TRACE("(%p) -> %d\n", iface, ref);

  if (ref == 0) {
    /* destruct */
    if (This->has != NULL) {
      if (This->acmStreamHdr.fdwStatus & ACMSTREAMHEADER_STATUSF_PREPARED)
	acmStreamUnprepareHeader(This->has, &This->acmStreamHdr, 0);
      acmStreamClose(This->has, 0);
      This->has = NULL;
    }
    HeapFree(GetProcessHeap(), 0, This->acmStreamHdr.pbSrc);
    This->acmStreamHdr.pbSrc = NULL;
    HeapFree(GetProcessHeap(), 0, This->acmStreamHdr.pbDst);
    This->acmStreamHdr.pbDst = NULL;
    if (This->lpInFormat != NULL) {
      HeapFree(GetProcessHeap(), 0, This->lpInFormat);
      This->lpInFormat = NULL;
      This->cbInFormat = 0;
    }
    if (This->lpOutFormat != NULL) {
      HeapFree(GetProcessHeap(), 0, This->lpOutFormat);
      This->lpOutFormat = NULL;
      This->cbOutFormat = 0;
    }
    if (This->pStream != NULL) {
      IAVIStream_Release(This->pStream);
      This->pStream = NULL;
    }
    HeapFree(GetProcessHeap(), 0, This);

    return 0;
  }

  /* also release reference to the nested stream */
  if (This->pStream != NULL)
    IAVIStream_Release(This->pStream);

  return ref;
}