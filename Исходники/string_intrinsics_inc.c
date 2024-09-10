int
compare_string (gfc_charlen_type len1, const CHARTYPE *s1,
		gfc_charlen_type len2, const CHARTYPE *s2)
{
  const UCHARTYPE *s;
  gfc_charlen_type len;
  int res;

  res = MEMCMP (s1, s2, ((len1 < len2) ? len1 : len2));
  if (res != 0)
    return res;

  if (len1 == len2)
    return 0;

  if (len1 < len2)
    {
      len = len2 - len1;
      s = (UCHARTYPE *) &s2[len1];
      res = -1;
    }
  else
    {
      len = len1 - len2;
      s = (UCHARTYPE *) &s1[len2];
      res = 1;
    }

  while (len--)
    {
      if (*s != ' ')
        {
          if (*s > ' ')
            return res;
          else
            return -res;
        }
      s++;
    }

  return 0;
}