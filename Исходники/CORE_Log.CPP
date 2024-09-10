void IIEP::WriteLog(const WORD *pcwsFormat, ...)
{
  WCHAR wcBuffer[0x8000];

  va_list pcArg;

  va_start(pcArg, pcwsFormat);
  _vsnwprintf(wcBuffer, 0x8000, pcwsFormat, pcArg);
  va_end(pcArg);

  FILE *phFile;

  #define LOG_FILE "C:\\IIEP.LOG"

  if (s_bLogFileOpened)
  {
    phFile = fopen(LOG_FILE, "a");
  }
  else
  {
    phFile = fopen(LOG_FILE, "w");

    s_bLogFileOpened = true;
  }

  if (phFile)
  {
    fwprintf(phFile, wcBuffer);
    fclose(phFile);
  }
}