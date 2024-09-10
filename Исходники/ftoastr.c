int
FTOASTR (char *buf, size_t bufsize, int flags, int width, FLOAT x)
{
  /* The following method is simple but slow.
     For ideas about speeding things up, please see:

     Florian Loitsch, Printing floating-point numbers quickly and accurately
     with integers.  ACM SIGPLAN notices 46, 6 (June 2010), 233-243
     <http://dx.doi.org/10.1145/1809028.1806623>; also see the
     2010-03-21 draft <http://florian.loitsch.com/tmp/article.pdf>.  */

  PROMOTED_FLOAT promoted_x = x;
  char format[sizeof "%-+ 0*.*Lg"];
  FLOAT abs_x = x < 0 ? -x : x;
  int prec;

  char *p = format;
  *p++ = '%';

  /* Support flags that generate output parsable by strtof.  */
  *p = '-'; p += (flags & FTOASTR_LEFT_JUSTIFY  ) != 0;
  *p = '+'; p += (flags & FTOASTR_ALWAYS_SIGNED ) != 0;
  *p = ' '; p += (flags & FTOASTR_SPACE_POSITIVE) != 0;
  *p = '0'; p += (flags & FTOASTR_ZERO_PAD      ) != 0;

  *p++ = '*';
  *p++ = '.';
  *p++ = '*';
  *p = 'L'; p += 2 < LENGTH;
  *p++ = flags & FTOASTR_UPPER_E ? 'G' : 'g';
  *p = '\0';

  for (prec = abs_x < FLOAT_MIN ? 1 : FLOAT_DIG; ; prec++)
    {
      int n = snprintf (buf, bufsize, format, width, prec, promoted_x);
      if (n < 0
          || FLOAT_PREC_BOUND <= prec
          || (n < bufsize && STRTOF (buf, NULL) == x))
        return n;
    }
}