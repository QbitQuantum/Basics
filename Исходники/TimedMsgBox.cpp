int WINAPI _tWinMain(HINSTANCE, HINSTANCE, PTSTR, int) 
{
   //TcpClient(); 
   _tcscpy_s(g_szCaption, _countof(g_szCaption), TEXT("Timed Message Box"));

   // How many seconds we'll give the user to respond
   g_nSecLeft = 10;

   // Create the threadpool timer object
   PTP_TIMER lpTimer = 
      CreateThreadpoolTimer(MsgBoxTimeoutCallback, NULL, NULL);

   if (lpTimer == NULL) {
      TCHAR szMsg[MAX_PATH];
      StringCchPrintf(szMsg, _countof(szMsg), 
         TEXT("Impossible to create the timer: %u"), GetLastError());
      MessageBox(NULL, szMsg, TEXT("Error"), MB_OK | MB_ICONERROR);

      return(-1);
   }

   // Start the timer in one second to trigger every 1 second
   ULARGE_INTEGER ulRelativeStartTime;
   ulRelativeStartTime.QuadPart = (LONGLONG) -(10000000);  // start in 1 second

   FILETIME ftRelativeStartTime;
   ftRelativeStartTime.dwHighDateTime = ulRelativeStartTime.HighPart;
   ftRelativeStartTime.dwLowDateTime  = ulRelativeStartTime.LowPart;

   SetThreadpoolTimer(
      lpTimer, 
      &ftRelativeStartTime, 
      1000, // Triggers every 1000 milliseconds
      0
      );

   // Display the message box
   MessageBox(NULL, TEXT("You have 10 seconds to respond"), 
      g_szCaption, MB_OK);
   
   // Clean up the timer
   CloseThreadpoolTimer(lpTimer);
   
   // Let us know if the user responded or if we timed out
   MessageBox(
      NULL, (g_nSecLeft == 1) ? TEXT("Timeout") : TEXT("User responded"), 
      TEXT("Result"), MB_OK);
   
   return(0);
}