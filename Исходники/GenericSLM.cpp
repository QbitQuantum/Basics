// Windows GUI thread to prevent screen savers or hibernation, and prevent the cursor from getting lost.
int GenericSLMWindowsGUIThread::svc(void)
{
   long i=0;
   while(!stop_)
   {

      ++i;

      if ((i % 900) == 0) {  // Every 30 seconds or so ...
         // ... reset idle clocks to prevent screensaver or hibernation (would appear on SLM).
         SetThreadExecutionState(ES_DISPLAY_REQUIRED | ES_SYSTEM_REQUIRED);
      }

      if ((i % 30) == 0)
      {
         //FixWindows(hwnd_); // This seems to be too slow. Run in separate thread?
         //SetWindowPos(hwnd_, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // This seems to be too slow.
      }


      RestrictCursor();

      Sleep(30);
   }

   return 0;
}