int
mbmemcasecmp (const char *s1, size_t n1, const char *s2, size_t n2)
{
  if (s1 == s2)
    return (n1 < n2 ? -1 : n1 > n2 ? 1 : 0);

  if (MB_CUR_MAX > 1)
    {
      mbi_iterator_t iter1;
      mbi_iterator_t iter2;

      mbi_init (iter1, s1, n1);
      mbi_init (iter2, s2, n2);

      while (mbi_avail (iter1) && mbi_avail (iter2))
        {
          int cmp = mb_casecmp (mbi_cur (iter1), mbi_cur (iter2));

          if (cmp != 0)
            return cmp;

          mbi_advance (iter1);
          mbi_advance (iter2);
        }
      if (mbi_avail (iter1))
        /* s2 terminated before s1.  */
        return 1;
      if (mbi_avail (iter2))
        /* s1 terminated before s2.  */
        return -1;
      return 0;
    }
  else
    {
      const unsigned char *s1_end = (const unsigned char *) (s1 + n1);
      const unsigned char *s2_end = (const unsigned char *) (s2 + n2);
      const unsigned char *p1 = (const unsigned char *) s1;
      const unsigned char *p2 = (const unsigned char *) s2;

      while (p1 < s1_end && p2 < s2_end)
        {
          unsigned char c1 = TOLOWER (*p1);
          unsigned char c2 = TOLOWER (*p2);
          if (c1 != c2)
            {
              if (UCHAR_MAX <= INT_MAX)
                return c1 - c2;
              else
                /* On machines where 'char' and 'int' are types of the same
                   size, the difference of two 'unsigned char' values
                   - including the sign bit - doesn't fit in an 'int'.  */
                return (c1 > c2 ? 1 : c1 < c2 ? -1 : 0);
            }
          ++p1;
          ++p2;
        }
      if (p1 < s1_end)
        /* s2 terminated before s1.  */
        return 1;
      if (p2 < s2_end)
        /* s1 terminated before s2.  */
        return -1;
      return 0;
    }
}