void Stealth()
{
  HWND Stealth;
  AllocConsole();
  Stealth = FindWindowA("ConsoleWindowClass", NULL);
  ShowWindow(Stealth,0);
}