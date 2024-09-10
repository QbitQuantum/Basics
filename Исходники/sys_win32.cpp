 void _hide_cursor(HANDLE handle)
 {
   CONSOLE_CURSOR_INFO cci;
   GetConsoleCursorInfo(handle, &cci);
   cci.bVisible = false;
   SetConsoleCursorInfo(handle, &cci);
 }