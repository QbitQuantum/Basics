CAMLprim value win32_interrupt(value pseudopid) {
  CAMLparam1(pseudopid);
  HANDLE h;
  DWORD pid;
  FreeConsole(); /* Normally unnecessary, just to be sure... */
  h = (HANDLE)(Long_val(pseudopid));
  pid = GetProcessId(h);
  AttachConsole(pid);
  /* We want to survive the Ctrl-C that will also concerns us */
  SetConsoleCtrlHandler(NULL,TRUE); /* NULL + TRUE means ignore */
  GenerateConsoleCtrlEvent(CTRL_C_EVENT,0); /* signal our co-console */
  FreeConsole();
  CAMLreturn(Val_unit);
}