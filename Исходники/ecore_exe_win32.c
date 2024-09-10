static DWORD WINAPI
_ecore_exe_thread_procedure(LPVOID data __UNUSED__)
{
   GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
   GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, 0);
   return 1;
}