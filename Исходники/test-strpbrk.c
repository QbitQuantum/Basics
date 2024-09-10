static void
do_random_tests (void)
{
  size_t i, j, n, align, pos, len, rlen;
  RES_TYPE result;
  int c;
  UCHAR *p = (UCHAR *) (buf1 + page_size) - 512;
  UCHAR *rej;

  for (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      if (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      if (pos >= len && (random () & 1))
	len = pos + 1 + (random () & 7);
      if (len + align >= 512)
	len = 511 - align - (random () & 7);
      if (random () & 1)
	rlen = random () & 63;
      else
	rlen = random () & 15;
      rej = (UCHAR *) (buf2 + page_size) - rlen - 1 - (random () & 7);
      for (i = 0; i < rlen; ++i)
	{
	  rej[i] = random () & BIG_CHAR;
	  if (!rej[i])
	    rej[i] = random () & BIG_CHAR;
	  if (!rej[i])
	    rej[i] = 1 + (random () & SMALL_CHAR);
	}
      rej[i] = '\0';
      for (c = 1; c <= BIG_CHAR; ++c)
	if (STRCHR ((CHAR *) rej, c) == NULL)
	  break;
      j = (pos > len ? pos : len) + align + 64;
      if (j > 512)
	j = 512;

      for (i = 0; i < j; i++)
	{
	  if (i == len + align)
	    p[i] = '\0';
	  else if (i == pos + align)
	    p[i] = rej[random () % (rlen + 1)];
	  else if (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  else
	    {
	      p[i] = random () & BIG_CHAR;
	      if (STRCHR ((CHAR *) rej, p[i]))
		{
		  p[i] = random () & BIG_CHAR;
		  if (STRCHR ((CHAR *) rej, p[i]))
		    p[i] = c;
		}
	    }
	}

      result = STRPBRK_RESULT ((CHAR *) (p + align), pos < len ? pos : len);

      FOR_EACH_IMPL (impl, 1)
	if (CALL (impl, (CHAR *) (p + align), (CHAR *) rej) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %p != %p",
		   n, impl->name, align, rej, rlen, pos, len,
		   (void *) CALL (impl, (CHAR *) (p + align), (CHAR *) rej),
		   (void *) result);
	    ret = 1;
	  }
    }
}