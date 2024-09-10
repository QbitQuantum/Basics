void TThreads::resume() {
   if (!inited) {
      SetFileApisToOEM();
      chandle[cnInput]  = GetStdHandle(STD_INPUT_HANDLE);
      chandle[cnOutput] = GetStdHandle(STD_OUTPUT_HANDLE);
      GetConsoleCursorInfo(chandle[cnOutput], &crInfo);
      GetConsoleScreenBufferInfo(chandle[cnOutput], &sbInfo);
      GetConsoleMode(chandle[cnInput],&consoleMode);
      consoleMode &= ~(ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT|ENABLE_WINDOW_INPUT);
      SetConsoleMode(chandle[cnInput],consoleMode);

      evpending = 0;
      inited = 1;
   }
}