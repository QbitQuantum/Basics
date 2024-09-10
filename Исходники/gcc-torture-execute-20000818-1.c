int yylex (void)
{
  int ch;

#ifndef WORK_AROUND
  for (;;)
    {
      ch = input ();
      if (ISALNUM (ch))
        obstack_1grow (&temporary_obstack, ch);
      else if (ch != '_')
        break;
    }
#else
  do
    {
      ch = input ();
      if (ISALNUM (ch))
        obstack_1grow (&temporary_obstack, ch);
    } while (ch == '_');
#endif

  return ch;
}