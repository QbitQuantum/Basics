BOOL He4HookDriverHide::GetNtProcAddresses()
{
  if (pRtlNtStatusToDosError == NULL)
  {
    HMODULE hNtDll = GetModuleHandle("ntdll.dll");
    if (hNtDll != NULL)
    {
      pRtlNtStatusToDosError = (RTLNTSTATUSTODOSERROR)GetProcAddress(hNtDll, "RtlNtStatusToDosError");
      if (IsBadCodePtr((FARPROC)pRtlNtStatusToDosError))
        pRtlNtStatusToDosError = NULL;
    }
  }

  return (BOOL)pRtlNtStatusToDosError;
}