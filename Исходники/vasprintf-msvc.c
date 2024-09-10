int vasprintf(char **strp, const char *fmt, va_list ap)
{
  int r = -1, size = _vscprintf(fmt, ap);

  if ((size >= 0) && (size < INT_MAX))
  {
    *strp = (char *)malloc(size+1); //+1 for null
    if (*strp)
    {
      r = vsnprintf(*strp, size+1, fmt, ap);  //+1 for null
      if ((r < 0) || (r > size))
      {
        insane_free(*strp);
        r = -1;
      }
    }
  }
  else { *strp = 0; }

  return(r);
}