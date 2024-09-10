int
decode_ll(
  struct attribute *patr,
  char *name,  /* attribute name */
  char *rescn,  /* resource name, unused here */
  char *val  /* attribute value */
)
  {
  char *pc;

  if ((val != (char *)0) && (strlen(val) != 0))
    {

    patr->at_val.at_ll = (Long)strTouL(val, &pc, 0);

    if (*pc != '\0')
      return (PBSE_BADATVAL);  /* invalid string */

    patr->at_flags |= ATR_VFLAG_SET | ATR_VFLAG_MODIFY;
    }
  else
    {
    patr->at_flags = (patr->at_flags & ~ATR_VFLAG_SET) |
                     ATR_VFLAG_MODIFY;
    patr->at_val.at_ll = 0;
    }

  return (0);
  }