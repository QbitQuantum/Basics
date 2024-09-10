static void MrEdSchemeMessages(char *msg, ...)
{
  GC_CAN_IGNORE va_list args;
  
  scheme_start_atomic();

  XFORM_HIDE_EXPR(va_start(args, msg));

  if (!console_out) {
    AllocConsole();
    console_out = GetStdHandle(STD_OUTPUT_HANDLE);

    if (!wx_in_terminal) {
      has_stdio = 1;
      waiting_sema = CreateSemaphore(NULL, 0, 1, NULL);
      orig_signal_handle = scheme_get_signal_handle();
      orig_break_handle = scheme_get_main_thread_break_handle();
      SetConsoleCtrlHandler(ConsoleHandler, TRUE);      

      {
	HMODULE hm;
	gcw_proc gcw;

	hm = LoadLibrary("kernel32.dll");
	if (hm)
	  gcw = (gcw_proc)GetProcAddress(hm, "GetConsoleWindow");
	else
	  gcw = NULL;
    
	if (gcw)
	  console_hwnd = gcw();
      }

      if (console_hwnd) {
	EnableMenuItem(GetSystemMenu(console_hwnd, FALSE), SC_CLOSE,
		       MF_BYCOMMAND | MF_GRAYED);
	RemoveMenu(GetSystemMenu(console_hwnd, FALSE), SC_CLOSE, MF_BYCOMMAND);
      }
    }
  }

  if (!msg) {
    char *s;
    intptr_t l, d;
    DWORD wrote;

    s = va_arg(args, char*);
    d = va_arg(args, intptr_t);
    l = va_arg(args, intptr_t);

    WriteConsole(console_out, s XFORM_OK_PLUS d, l, &wrote, NULL);
  } else {