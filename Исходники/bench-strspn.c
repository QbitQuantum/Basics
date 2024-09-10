static void
do_test (size_t align, size_t pos, size_t len)
{
  size_t i;
  CHAR *acc, *s;

  align &= 7;
  if ((align + pos + 10) * sizeof (CHAR) >= page_size || len > 240 || ! len)
    return;

  acc = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  for (i = 0; i < len; ++i)
    {
      acc[i] = random () & BIG_CHAR;
      if (!acc[i])
	acc[i] = random () & BIG_CHAR;
      if (!acc[i])
	acc[i] = 1 + (random () & SMALL_CHAR);
    }
  acc[len] = '\0';

  for (i = 0; i < pos; ++i)
    s[i] = acc[random () % len];
  s[pos] = random () & BIG_CHAR;
  if (STRCHR (acc, s[pos]))
    s[pos] = '\0';
  else
    {
      for (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }

  printf ("Length %4zd, alignment %2zd, acc len %2zd:", pos, align, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, acc, pos);

  putchar ('\n');
}