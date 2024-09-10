//----------------------------------------------------------------------------
static FARPROC WINAPI delayFailureHook(/*dliNotification*/unsigned dliNotify,
                                       PDelayLoadInfo pdli)
{
    if(   dliNotify == /*dliFailGetProcAddress*/dliFailGetProc
       && pdli && pdli->cb == sizeof(*pdli)
       && pdli->hmodCur == GetModuleHandleA("kernel32")
       && pdli->dlp.fImportByName && pdli->dlp.szProcName
       && (   !lstrcmpA(pdli->dlp.szProcName, "EncodePointer")
           || !lstrcmpA(pdli->dlp.szProcName, "DecodePointer")))
    {
      return (FARPROC)no_recode_pointer;
    }
    return nullptr;
}