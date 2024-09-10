/*
 * Compare two characters converting collate information
 * into ASCII-compatible range, it allows to handle
 * "[a-z]"-type ranges with national characters.
 */
static int collate_range_cmp(int c1, int c2) {
  static char s1[2], s2[2];
  int ret;
#ifndef ASCII_COMPATIBLE_COLLATE
  int as1, as2, al1, al2;
#endif

  c1 &= UCHAR_MAX;
  c2 &= UCHAR_MAX;
  if (c1 == c2)
    return (0);

#ifndef ASCII_COMPATIBLE_COLLATE
  as1 = isascii(c1);
  as2 = isascii(c2);
  al1 = isalpha(c1);
  al2 = isalpha(c2);

  if (as1 || as2 || al1 || al2) {
    if ((as1 && as2) || (!al1 && !al2))
      return (c1 - c2);
    if (al1 && !al2) {
      if (isupper(c1))
        return ('A' - c2);
      else
        return ('a' - c2);
    } else if (al2 && !al1) {
      if (isupper(c2))
        return (c1 - 'A');
      else
        return (c1 - 'a');
    }
  }
#endif
  s1[0] = c1;
  s2[0] = c2;
  if ((ret = strcoll(s1, s2)) != 0)
    return (ret);
  return (c1 - c2);
}