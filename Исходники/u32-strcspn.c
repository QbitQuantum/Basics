size_t
FUNC (const UNIT *str, const UNIT *reject)
{
  /* Optimize two cases.  */
  if (reject[0] == 0)
    return U_STRLEN (str);
  if (reject[1] == 0)
    {
      ucs4_t uc = reject[0];
      const UNIT *ptr = str;
      for (; *ptr != 0; ptr++)
        if (*ptr == uc)
          break;
      return ptr - str;
    }
  /* General case.  */
  {
    const UNIT *ptr = str;
    for (; *ptr != 0; ptr++)
      if (U_STRCHR (reject, *ptr))
        break;
    return ptr - str;
  }
}