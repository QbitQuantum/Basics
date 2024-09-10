extern "C" BOOL __stdcall DllMain(HINSTANCE hinstance, DWORD reason, void* pv)
{
  if (DLL_PROCESS_ATTACH == reason)
  {
    ghInstance = hinstance;
    DllRegisterServer();
  }
  return 1;
}