static ULONG   WINAPI IAVIEditStream_fnRelease(IAVIEditStream*iface)
{
  IAVIEditStreamImpl *This = impl_from_IAVIEditStream(iface);
  DWORD i;
  ULONG ref = InterlockedDecrement(&This->ref);

  TRACE("(%p) -> %d\n", iface, ref);

  if (!ref) {
    /* release memory */
    if (This->pg != NULL)
      AVIStreamGetFrameClose(This->pg);
    if (This->pStreams != NULL) {
      for (i = 0; i < This->nStreams; i++) {
        if (This->pStreams[i].pStream != NULL)
          IAVIStream_Release(This->pStreams[i].pStream);
      }
      HeapFree(GetProcessHeap(), 0, This->pStreams);
    }

    HeapFree(GetProcessHeap(), 0, This);
    return 0;
  }
  return ref;
}