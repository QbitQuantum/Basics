static void
mswindows_ensure_console_buffered (void)
{
  if (!mswindows_console_buffered)
    {
      COORD new_size;

      new_size.X = 80;
      new_size.Y = 1000;
      mswindows_ensure_console_allocated ();
      mswindows_console_buffer =
	CreateConsoleScreenBuffer (GENERIC_WRITE, 0, NULL,
				   CONSOLE_TEXTMODE_BUFFER, NULL);
      SetConsoleScreenBufferSize (mswindows_console_buffer, new_size);
      SetConsoleActiveScreenBuffer (mswindows_console_buffer);
      mswindows_console_buffered = 1;
    }
}