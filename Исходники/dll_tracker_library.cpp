extern "C" BOOL __stdcall track_FreeLibrary(HINSTANCE hLibModule)
{
  uintptr_t loc = (uintptr_t)_ReturnAddress();

  tracker_library_free(loc, hLibModule);

  return dllFreeLibrary(hLibModule);
}