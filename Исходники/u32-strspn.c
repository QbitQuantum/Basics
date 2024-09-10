size_t
FUNC (const UNIT *str, const UNIT *accept)
{
  /* Optimize two cases.  */
  if (accept[0] == 0)
    return 0;
  if (accept[1] == 0)
    {
      ucs4_t uc = accept[0];
      const UNIT *ptr = str;
      for (; *ptr != 0; ptr++)
        if (*ptr != uc)
          break;
      return ptr - str;
    }
  /* General case.  */
  {
    const UNIT *ptr = str;
    for (; *ptr != 0; ptr++)
      if (!U_STRCHR (accept, *ptr))
        break;
    return ptr - str;
  }
}