static void
setProgramName (char *argv0)
{
  char *pn;

  if (programName)
    localFree (programName);

  if (argv0 == (char *) 0)
    {
      programName = (char *) 0;
      return;
    }

  for (pn = argv0 + strlen (argv0); pn > argv0; --pn)
    if (*pn == '/')
      {
        pn++;
        break;
      }

  programName = localStrdup (pn);
}