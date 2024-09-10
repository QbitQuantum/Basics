char *
getpass (const char * prompt)
{
  static char input[256];
  HANDLE in;
  HANDLE err;
  DWORD  count;

  in = GetStdHandle (STD_INPUT_HANDLE);
  err = GetStdHandle (STD_ERROR_HANDLE);

  if (in == INVALID_HANDLE_VALUE || err == INVALID_HANDLE_VALUE)
    return NULL;

  if (WriteFile (err, prompt, strlen (prompt), &count, NULL))
    {
      int istty = (GetFileType (in) == FILE_TYPE_CHAR);
      DWORD old_flags;
      int rc;

      if (istty)
	{
	  if (GetConsoleMode (in, &old_flags))
	    SetConsoleMode (in, ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT);
	  else
	    istty = 0;
	}
      rc = ReadFile (in, input, sizeof (input), &count, NULL);
      if (count >= 2 && input[count - 2] == '\r')
	input[count - 2] = '\0';
      else
	{
	  char buf[256];
	  while (ReadFile (in, buf, sizeof (buf), &count, NULL) > 0)
	    if (count >= 2 && buf[count - 2] == '\r')
	      break;
	}
      WriteFile (err, "\r\n", 2, &count, NULL);
      if (istty)
	SetConsoleMode (in, old_flags);
      if (rc)
	return input;
    }

  return NULL;
}