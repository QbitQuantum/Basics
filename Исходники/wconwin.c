static BOOL CALLBACK GetConsoleWindowProc(HWND hWnd, LPARAM lParam)
{
   const char cConsoleClassName[] = "ConsoleWindowClass";
   DWORD dwPid = (DWORD)-1;
   char cBuf[sizeof(cConsoleClassName)] = "";

   GetWindowThreadProcessId(hWnd, &dwPid);
   if (dwPid != GetCurrentProcessId())
      return TRUE;

   if (GetClassName(hWnd, cBuf, sizeof cBuf) != sizeof(cConsoleClassName)-1)
      return TRUE;

   if (strcmp(cConsoleClassName, cBuf) != 0)
      return TRUE;

   *(HWND*)lParam = hWnd;
   return FALSE;
}