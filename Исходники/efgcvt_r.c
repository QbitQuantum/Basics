int
__APPEND (FUNC_PREFIX, fcvt_r) (FLOAT_TYPE value, int ndigit, int *decpt,
				int *sign, char *buf, size_t len)
{
  ssize_t n;
  ssize_t i;
  int left;

  if (buf == NULL)
    {
      __set_errno (EINVAL);
      return -1;
    }

  left = 0;
  if (isfinite (value))
    {
      *sign = signbit (value) != 0;
      if (*sign)
	value = -value;

      if (ndigit < 0)
	{
	  /* Rounding to the left of the decimal point.  */
	  while (ndigit < 0)
	    {
	      FLOAT_TYPE new_value = value * 0.1;

	      if (new_value < 1.0)
		{
		  ndigit = 0;
		  break;
		}

	      value = new_value;
	      ++left;
	      ++ndigit;
	    }
	}
    }
  else
    /* Value is Inf or NaN.  */
    *sign = 0;

  n = __snprintf (buf, len, "%.*" FLOAT_FMT_FLAG "f", MIN (ndigit, NDIGIT_MAX),
		  value);
  /* Check for a too small buffer.  */
  if (n >= (ssize_t) len)
    return -1;

  i = 0;
  while (i < n && isdigit (buf[i]))
    ++i;
  *decpt = i;

  if (i == 0)
    /* Value is Inf or NaN.  */
    return 0;

  if (i < n)
    {
      do
	++i;
      while (i < n && !isdigit (buf[i]));

      if (*decpt == 1 && buf[0] == '0' && value != 0.0)
	{
	  /* We must not have leading zeroes.  Strip them all out and
	     adjust *DECPT if necessary.  */
	  --*decpt;
	  while (i < n && buf[i] == '0')
	    {
	      --*decpt;
	      ++i;
	    }
	}

      memmove (&buf[MAX (*decpt, 0)], &buf[i], n - i);
      buf[n - (i - MAX (*decpt, 0))] = '\0';
    }

  if (left)
    {
      *decpt += left;
      if ((ssize_t) --len > n)
	{
	  while (left-- > 0 && n < (ssize_t) len)
	    buf[n++] = '0';
	  buf[n] = '\0';
	}
    }

  return 0;
}