static int do_nick_name(char *nick) {
  char   *ch;
  
  if (*nick == '-' || IsDigit(*nick))	/* first character is [0..9-] */
      return 0;
  
  for (ch = nick; *ch && (ch - nick) < NICKLEN; ch++)
      if (!isvalid(*ch) || IsSpace(*ch))
	  break;
  
  *ch = '\0';
  
  return (ch - nick);
}