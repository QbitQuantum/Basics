int
os_system(const char *cmd)
{
  char *s;
  int i;
  char *cmd1;

#if defined(OS2)
  if (_osmode == OS2_MODE)
    return(system(cmd));
#endif

  if ((cmd1 = scriptify(cmd)) == NULL) return(1);
  if (s = getenv("SHELL"))
    i = spawnlp(P_WAIT, s, s, cmd1 + strlen(s), NULL);
  else
    i = system(cmd1);
  unlink_and_free(cmd1);
  return(i);
}