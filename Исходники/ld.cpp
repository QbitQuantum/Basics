/*---------------------------------------------------------------------*/
static int run(char *line, bool isvc)
{
  char *nargv[10000];
  char *ptr = line;
  int i;
  for ( i=0; i < 10000-1; i++ )
  {
    while ( *ptr == ' ' || *ptr == '\t' )
      ptr++;
    if ( *ptr == '\0' )
      break;
    if ( *ptr == '"' || *ptr == '\'' )
    {
      char lim = *ptr++;
      nargv[i] = ptr;
      while ( *ptr != lim && *ptr != '\0' )
      {
        if ( *ptr == '\\' && (*ptr == '"' || *ptr == '\'') )
          memmove(ptr, ptr+1, strlen(ptr));
        ptr++;
      }
    }
    else
    {
      nargv[i] = ptr;
      while ( *ptr != ' ' && *ptr != '\t' && *ptr != '\0' )
        ptr++;
    }
    if ( *ptr != '\0' )
      *ptr++ = '\0';
  }
  nargv[i] = NULL;

  i = spawnvp(P_WAIT, nargv[0], nargv);
  if ( i != 0 )
  {
    if ( i == -1 )
      perror("exec error");
    else
      printf("ld error: '%s' exit with code %d\n", nargv[0], i);
    exit(3);
  }
  else if ( isvc )
  {
    remove_exp_and_lib(nargv);
  }
  return 0;
}