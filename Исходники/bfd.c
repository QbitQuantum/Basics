bfd_vma
bfd_scan_vma (const char *string, const char **end, int base)
{
  bfd_vma value;
  bfd_vma cutoff;
  unsigned int cutlim;
  int overflow;

  /* Let the host do it if possible.  */
  if (sizeof (bfd_vma) <= sizeof (unsigned long))
    return strtoul (string, (char **) end, base);

  if (sizeof (bfd_vma) <= sizeof (unsigned long long))
    return strtoull (string, (char **) end, base);

  if (base == 0)
    {
      if (string[0] == '0')
	{
	  if ((string[1] == 'x') || (string[1] == 'X'))
	    base = 16;
	  else
	    base = 8;
	}
    }

  if ((base < 2) || (base > 36))
    base = 10;

  if (base == 16
      && string[0] == '0'
      && (string[1] == 'x' || string[1] == 'X')
      && ISXDIGIT (string[2]))
    {
      string += 2;
    }

  cutoff = (~ (bfd_vma) 0) / (bfd_vma) base;
  cutlim = (~ (bfd_vma) 0) % (bfd_vma) base;
  value = 0;
  overflow = 0;
  while (1)
    {
      unsigned int digit;

      digit = *string;
      if (ISDIGIT (digit))
	digit = digit - '0';
      else if (ISALPHA (digit))
	digit = TOUPPER (digit) - 'A' + 10;
      else
	break;
      if (digit >= (unsigned int) base)
	break;
      if (value > cutoff || (value == cutoff && digit > cutlim))
	overflow = 1;
      value = value * base + digit;
      ++string;
    }

  if (overflow)
    value = ~ (bfd_vma) 0;

  if (end != NULL)
    *end = string;

  return value;
}