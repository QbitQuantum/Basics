// LCOV_EXCL_START :dpm
void NADebug()
{
  if (getenv("SQL_DEBUGLOOP") == NULL)
   DebugBreak();
  else
  {Int32 dbgv = 1;
   Int32 woody; // as in Woody Allen aka Sleeper.

   while (dbgv == 1)
   { woody = SleepEx(100,FALSE); // delay 0.1 seconds
     dbgv = 2 - dbgv;  // another way of saying, "leave dbgv at 1"
   };

  }

}