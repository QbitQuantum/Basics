static int
wputc(int c, FILE *f)
{ char buf[MB_CUR_MAX];
  int i, len = wctomb(buf, c);

  for(i=0; i<len; i++)
    putc(buf[i], f);

  return c;
}