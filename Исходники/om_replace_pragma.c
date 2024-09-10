static int startsWithWord(char *p, char *w)
{
  int wordLen = strlen(w);
  if( strncmp(p, w, wordLen) != 0 ) return 0;
  if( ! isBlank(p[wordLen]) ) return 0;
  return 1;
}