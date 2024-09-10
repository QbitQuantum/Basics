/*
 * @implemented
 */
int _cputs(const char *_str)
{
  DWORD count;
  int retval = EOF;
  HANDLE console_out = GetStdHandle(STD_OUTPUT_HANDLE);

  //LOCK_CONSOLE;
  if (WriteConsoleA(console_out, _str, strlen(_str), &count, NULL)
      && count == 1)
    retval = 0;
  //UNLOCK_CONSOLE;
  return retval;
}