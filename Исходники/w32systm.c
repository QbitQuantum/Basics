int w32system(const char *cp)
{
  char argbuf[256];
  char *argv[32];
  char *tp;
  int argc;

  tp = argbuf;
  argc = 0;
  while(*cp) {
    while(*cp && (*cp == ' ')) cp++;
    if(*cp) {
      argv[argc++] = tp;
      if(*cp == '"') {
       cp++;
       while(*cp && (*cp != '"')) *tp++ = *cp++;
       if(*cp == '"') cp++;
      }
      else {
       while(*cp &&  (*cp != ' ')) *tp++ = *cp++;
      }
      *tp++ = '\0';
    }
  }
  argv[argc] = NULL;

  return(spawnvp(P_WAIT, argv[0], argv));
}