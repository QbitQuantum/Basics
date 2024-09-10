GXHANDLE GXDLLAPI gxGetClipboardData(
            GXUINT uFormat   // clipboard format  
            )
{
#if defined(_WINDOWS) || defined(_WIN32)
  HANDLE handle = GetClipboardData((GXUINT)uFormat);
  if(handle)
  {
    LPVOID ptr = GlobalLock(handle);
    SIZE_T size = GlobalSize(handle);

    if(g_hClipboard) {
      gxGlobalFree(g_hClipboard);
    }

    g_hClipboard = gxGlobalAlloc(NULL, size);
    GXLPVOID pNative = gxGlobalLock(g_hClipboard);
    memcpy(pNative, ptr, size);
    gxGlobalUnlock(g_hClipboard);
    GlobalUnlock(handle);
    return (GXHANDLE)g_hClipboard;
  }
  return NULL;
#endif // #if defined(_WINDOWS) || defined(_WIN32)
}