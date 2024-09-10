VOID DLLEXPORT NORETURN WINAPI
UninstallHandler(DWORD dw)
{
  SetErrorMode(0);
  SetUnhandledExceptionFilter(NULL);

  if (dw > 0)
    MessageBox(NULL, "Exception handling restored to default mode.",
	       "noexcept.dll", MB_ICONINFORMATION | MB_SETFOREGROUND);

  FreeLibraryAndExitThread(hModDLL, dw);
}