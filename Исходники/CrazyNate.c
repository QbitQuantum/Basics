__declspec(dllexport) HMODULE STDMETHODCALLTYPE GetCrazyNateHModule()
{
  HMODULE myHModule = NULL;
  if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
    (LPCWSTR)&GetCrazyNateHModule,
    &myHModule))
  {
    myHModule = NULL;
  }
  return myHModule;
}