void Show_Console_Cursor(
    bool Show_Flag)  // Controls the visibility of the console cursor
{
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(out, &cursorInfo);
  cursorInfo.bVisible = Show_Flag;  // Sets the cursor visibility
  SetConsoleCursorInfo(out, &cursorInfo);
}