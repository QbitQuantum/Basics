static void
voutf_master_tty (const char * format, va_list args)
{
  char buf [1000];
  VSNPRINTF (buf, 1000, format, args);
  Screen_WriteText (master_tty_window, buf);
}