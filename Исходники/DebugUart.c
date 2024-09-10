void PrintE(const char *pFormat, ...)
{
  va_list args;

  va_start(args, pFormat);
  vSprintF(Buffer, pFormat, args);
  va_end(args);

  PrintW(Buffer);
}