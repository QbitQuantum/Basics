static int
wpadn (FILE *fp, wint_t pad, int count)
{
  int i;
  int written = 0;

  for (i=0;i<count;i++)
      if(putwc(pad,fp) != WEOF)
	written++;

  return written;
}