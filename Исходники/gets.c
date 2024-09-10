char *gets(
    _In_ char *buf)
{
  int    cc;
  char * buf_start = buf;

  _lock_file(stdin);
  for(cc = fgetc(stdin); cc != EOF && cc != '\n';
      cc = fgetc(stdin))
  if(cc != '\r') *buf++ = (char)cc;

  *buf = '\0';
  
  _unlock_file(stdin);
  return buf_start;
}