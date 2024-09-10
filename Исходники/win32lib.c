FILE * win32_popen (const char *cmd, const char *fmode)
{
  char mode[3];
  char *p, *q;
  const char *cmd2;
  FILE *ret;

  mode[0] = fmode[0];
  mode[1] = 'b';
  mode[2] = '\0';

  if (is_include_space (cmd)) {
    cmd2 = xmalloc (strlen (cmd) + 3);
    q = (char *)cmd2;
    p = (char *)cmd;
    *q++= '\"';
    while(*p)
      *q++ = *p++;
    *q++ = '\"';
    *q = '\0';
    ret = _popen (cmd2, mode);
    free ((char *)cmd2);
    return ret;
  } else {
    return _popen (cmd, mode);
  }
}