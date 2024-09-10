void setEcho(int flag) 
{
#ifdef WINDOWS
   HANDLE hConsole;
   DWORD  dwMode;

   hConsole = CreateFile("CONIN$", 
              GENERIC_READ|GENERIC_WRITE, 
              FILE_SHARE_READ|FILE_SHARE_WRITE,
              NULL,
              OPEN_EXISTING,
              0,
              NULL);

   if(hConsole != INVALID_HANDLE_VALUE) {
      GetConsoleMode(hConsole, &dwMode);
      if(flag) {
         dwMode |= ENABLE_ECHO_INPUT;
      } else {
         dwMode &= ~ENABLE_ECHO_INPUT;
      }
      SetConsoleMode(hConsole, dwMode);
      CloseHandle(hConsole);
   }
#else /* unix */
   static struct termios init_set;
   static int initialized = 0;

   struct termios new_set;
   
   if(initialized == 0) {
      tcgetattr(fileno(stdin), &init_set);
      initialized = 1;
   }

   new_set = init_set;
   if(flag) {   
      tcsetattr(fileno(stdin), TCSAFLUSH, &init_set);
   } else {
      new_set.c_lflag &= ~ECHO;
      tcsetattr(fileno(stdin), TCSAFLUSH, &new_set);
   }

#endif
}