static int
RunCommand (char *command)
{
  char *buffer;
  char *shell;
  int pid;

  /* Locate the command shell. */
  shell = o_shell ? tochar8 (o_shell) : getenv ("COMSPEC");
  if (shell == NULL)
    {
      shell = "cmd.exe";
    }

  if ((buffer = malloc (strlen (command) + 5)) != NULL) 
    {
    /*
     * Herbert:
     * Find the name of the shell. I assume cmd.exe and 4os2.exe to
     * understand the "/c" switch and use "-c" for all the others.
     * The quotes around the command *seem* to work for Unix-like
     * shells, they are meant to pass the command to the shell as
     * one string.
     */
      char *org_sep = strrchr (shell, OSPATHSEP);
      char *alt_sep = strrchr (shell, OSALTPSEP);
      char *base = org_sep < alt_sep ? alt_sep : org_sep;
      base = base == NULL? shell: base+1;

      if ( stricmp (base, "cmd.exe") == 0 
           || stricmp (base, "4os2.exe") == 0) 
        {
          sprintf (buffer, "/c %s", command);
        }
      else 
        {
          sprintf (buffer, "-c \"%s\"", command);
        }

      pid = spawnlp (P_NOWAIT, shell, shell, buffer, NULL);
      free (buffer);
      return pid;
    } 
  else 
    {
      return -1;
    }
}