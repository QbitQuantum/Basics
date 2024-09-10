void WriteConsoleKey(HANDLE console,DWORD Key,DWORD State)
{
  INPUT_RECORD event; DWORD written;
  event.EventType=KEY_EVENT;
  event.Event.KeyEvent.bKeyDown=TRUE;
  event.Event.KeyEvent.wRepeatCount=1;
  event.Event.KeyEvent.wVirtualKeyCode=(WORD)Key;
  event.Event.KeyEvent.wVirtualScanCode=0;
  event.Event.KeyEvent.uChar.UnicodeChar=0;
  event.Event.KeyEvent.dwControlKeyState=State;
  WriteConsoleInputW(console,&event,1,&written);
}