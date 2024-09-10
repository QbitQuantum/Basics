FLOAT
STRTOD_NAN (const STRING_TYPE *str, STRING_TYPE **endptr, STRING_TYPE endc)
{
  const STRING_TYPE *cp = str;

  while ((*cp >= L_('0') && *cp <= L_('9'))
	 || (*cp >= L_('A') && *cp <= L_('Z'))
	 || (*cp >= L_('a') && *cp <= L_('z'))
	 || *cp == L_('_'))
    ++cp;

  FLOAT retval = NAN;
  if (*cp != endc)
    goto out;

  /* This is a system-dependent way to specify the bitmask used for
     the NaN.  We expect it to be a number which is put in the
     mantissa of the number.  */
  STRING_TYPE *endp;
  unsigned long long int mant;

  mant = STRTOULL (str, &endp, 0);
  if (endp == cp)
    SET_NAN_PAYLOAD (retval, mant);

 out:
  if (endptr != NULL)
    *endptr = (STRING_TYPE *) cp;
  return retval;
}