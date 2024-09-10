//***********************************************************
//  This replaces the CXL function of the same name
//***********************************************************
void set_lines(int crt_lines)
   {
   // COORD dwSize = { 80, crt_lines } ;
   // SetConsoleScreenBufferSize(hStdOut, dwSize) ;
   
   //  The preceding method changes the actual buffer size,
   //  not the window size, which may not be what is wanted
   //  under WinNT.  This method changes the actual window
   //  size, but positions the new window at the *top* of
   //  the screen buffer, which may give unexpected results
   //  if used with "don't clear screen" in a large window.
   //  Neither method is exactly correct in all cases,
   //  but will probably suffice most times...
   SMALL_RECT newwin = { 0, 0, 79, crt_lines-1 } ;
   SetConsoleWindowInfo(hStdOut, TRUE, &newwin) ;
   }