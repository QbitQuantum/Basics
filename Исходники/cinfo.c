void
upmapinit (void)
{
  register int i;

  for (i = 0; i < 256; i++)
    {
      if (ISLOWER (i) && casefold)
	upmap[i] = TOUPPER (i);
      else
	upmap[i] = i;
    }
}