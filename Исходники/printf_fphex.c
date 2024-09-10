int
__printf_fphex (FILE *fp,
		const struct printf_info *info,
		const void *const *args)
{
  /* The floating-point value to output.  */
  union
    {
      union ieee754_double dbl;
      union ieee854_long_double ldbl;
    }
  fpnum;

  /* Locale-dependent representation of decimal point.	*/
  const char *decimal;
  wchar_t decimalwc;

  /* "NaN" or "Inf" for the special cases.  */
  const char *special = NULL;
  const wchar_t *wspecial = NULL;

  /* Buffer for the generated number string for the mantissa.  The
     maximal size for the mantissa is 128 bits.  */
  char numbuf[32];
  char *numstr="";
  char *numend;
  wchar_t wnumbuf[32];
  wchar_t *wnumstr=L"";
  wchar_t *wnumend;
  int negative;

  /* The maximal exponent of two in decimal notation has 5 digits.  */
  char expbuf[5];
  char *expstr;
  wchar_t wexpbuf[5];
  wchar_t *wexpstr;
  int expnegative = 0;
  int exponent = 0;

  /* Non-zero is mantissa is zero.  */
  int zero_mantissa = 1;

  /* The leading digit before the decimal point.  */
  char leading = '0';

  /* Precision.  */
  int precision = info->prec;

  /* Width.  */
  int width = info->width;

  /* Number of characters written.  */
  int done = 0;

  /* Nonzero if this is output on a wide character stream.  */
  int wide = info->wide;


  /* Figure out the decimal point character.  */
  if (info->extra == 0)
    {
      decimal = _NL_CURRENT (LC_NUMERIC, DECIMAL_POINT);
      decimalwc = _NL_CURRENT_WORD (LC_NUMERIC, _NL_NUMERIC_DECIMAL_POINT_WC);
    }
  else
    {
      decimal = _NL_CURRENT (LC_MONETARY, MON_DECIMAL_POINT);
      decimalwc = _NL_CURRENT_WORD (LC_MONETARY,
				    _NL_MONETARY_DECIMAL_POINT_WC);
    }
  /* The decimal point character must never be zero.  */
  assert (*decimal != '\0' && decimalwc != L'\0');


  /* Fetch the argument value.	*/
#ifndef __NO_LONG_DOUBLE_MATH
  if (info->is_long_double && sizeof (long double) > sizeof (double))
    {
      fpnum.ldbl.d = *(const long double *) args[0];

      /* Check for special values: not a number or infinity.  */
      if (__isnanl (fpnum.ldbl.d))
	{
	  if (isupper (info->spec))
	    {
	      special = "NAN";
	      wspecial = L"NAN";
	    }
	  else
	    {
	      special = "nan";
	      wspecial = L"nan";
	    }
	  negative = 0;
	}
      else
	{
	  if (__isinfl (fpnum.ldbl.d))
	    {
	      if (isupper (info->spec))
		{
		  special = "INF";
		  wspecial = L"INF";
		}
	      else
		{
		  special = "inf";
		  wspecial = L"inf";
		}
	    }

	  negative = signbit (fpnum.ldbl.d);
	}
    }
  else
#endif	/* no long double */
    {
      fpnum.dbl.d = *(const double *) args[0];

      /* Check for special values: not a number or infinity.  */
      if (__isnan (fpnum.dbl.d))
	{
	  if (isupper (info->spec))
	    {
	      special = "NAN";
	      wspecial = L"NAN";
	    }
	  else
	    {
	      special = "nan";
	      wspecial = L"nan";
	    }
	  negative = 0;
	}
      else
	{
	  if (__isinf (fpnum.dbl.d))
	    {
	      if (isupper (info->spec))
		{
		  special = "INF";
		  wspecial = L"INF";
		}
	      else
		{
		  special = "inf";
		  wspecial = L"inf";
		}
	    }

	  negative = signbit (fpnum.dbl.d);
	}
    }

  if (special)
    {
      int width = info->width;

      if (negative || info->showsign || info->space)
	--width;
      width -= 3;

      if (!info->left && width > 0)
	PADN (' ', width);

      if (negative)
	outchar ('-');
      else if (info->showsign)
	outchar ('+');
      else if (info->space)
	outchar (' ');

      PRINT (special, wspecial, 3);

      if (info->left && width > 0)
	PADN (' ', width);

      return done;
    }

  if (info->is_long_double == 0 || sizeof (double) == sizeof (long double))
    {
      /* We have 52 bits of mantissa plus one implicit digit.  Since
	 52 bits are representable without rest using hexadecimal
	 digits we use only the implicit digits for the number before
	 the decimal point.  */
      unsigned long long int num;

      num = (((unsigned long long int) fpnum.dbl.ieee.mantissa0) << 32
	     | fpnum.dbl.ieee.mantissa1);

      zero_mantissa = num == 0;

      if (sizeof (unsigned long int) > 6)
	{
	  wnumstr = _itowa_word (num, wnumbuf + (sizeof wnumbuf) / sizeof (wchar_t), 16,
				 info->spec == 'A');
	  numstr = _itoa_word (num, numbuf + sizeof numbuf, 16,
			       info->spec == 'A');
	}
      else
	{
	  wnumstr = _itowa (num, wnumbuf + sizeof wnumbuf / sizeof (wchar_t), 16,
			    info->spec == 'A');
	  numstr = _itoa (num, numbuf + sizeof numbuf, 16,
			  info->spec == 'A');
	}

      /* Fill with zeroes.  */
      while (wnumstr > wnumbuf + (sizeof wnumbuf - 52) / sizeof (wchar_t))
	{
	  *--wnumstr = L'0';
	  *--numstr = '0';
	}

      leading = fpnum.dbl.ieee.exponent == 0 ? '0' : '1';

      exponent = fpnum.dbl.ieee.exponent;

      if (exponent == 0)
	{
	  if (zero_mantissa)
	    expnegative = 0;
	  else
	    {
	      /* This is a denormalized number.  */
	      expnegative = 1;
	      exponent = IEEE754_DOUBLE_BIAS - 1;
	    }
	}
      else if (exponent >= IEEE754_DOUBLE_BIAS)
	{
	  expnegative = 0;
	  exponent -= IEEE754_DOUBLE_BIAS;
	}
      else
	{
	  expnegative = 1;
	  exponent = -(exponent - IEEE754_DOUBLE_BIAS);
	}
    }
#ifdef PRINT_FPHEX_LONG_DOUBLE
  else
    PRINT_FPHEX_LONG_DOUBLE;
#endif

  /* Look for trailing zeroes.  */
  if (! zero_mantissa)
    {
      wnumend = &wnumbuf[sizeof wnumbuf / sizeof wnumbuf[0]];
      numend = &numbuf[sizeof numbuf / sizeof numbuf[0]];
      while (wnumend[-1] == L'0')
	{
	  --wnumend;
	  --numend;
	}

      if (precision == -1)
	precision = numend - numstr;
      else if (precision < numend - numstr
	       && (numstr[precision] > '8'
		   || (('A' < '0' || 'a' < '0')
		       && numstr[precision] < '0')
		   || (numstr[precision] == '8'
		       && (precision + 1 < numend - numstr
			   /* Round to even.  */
			   || (precision > 0
			       && ((numstr[precision - 1] & 1)
				   ^ (isdigit (numstr[precision - 1]) == 0)))
			   || (precision == 0
			       && ((leading & 1)
				   ^ (isdigit (leading) == 0)))))))
	{
	  /* Round up.  */
	  int cnt = precision;
	  while (--cnt >= 0)
	    {
	      char ch = numstr[cnt];
	      /* We assume that the digits and the letters are ordered
		 like in ASCII.  This is true for the rest of GNU, too.  */
	      if (ch == '9')
		{
		  wnumstr[cnt] = (wchar_t) info->spec;
		  numstr[cnt] = info->spec;	/* This is tricky,
		  				   think about it!  */
		  break;
		}
	      else if (tolower (ch) < 'f')
		{
		  ++numstr[cnt];
		  ++wnumstr[cnt];
		  break;
		}
	      else
		{
		  numstr[cnt] = '0';
		  wnumstr[cnt] = L'0';
		}
	    }
	  if (cnt < 0)
	    {
	      /* The mantissa so far was fff...f  Now increment the
		 leading digit.  Here it is again possible that we
		 get an overflow.  */
	      if (leading == '9')
		leading = info->spec;
	      else if (tolower (leading) < 'f')
		++leading;
	      else
		{
		  leading = '1';
		  if (expnegative)
		    {
		      exponent -= 4;
		      if (exponent <= 0)
			{
			  exponent = -exponent;
			  expnegative = 0;
			}
		    }
		  else
		    exponent += 4;
		}
	    }
	}
    }
  else
    {
      if (precision == -1)
	precision = 0;
      numend = numstr;
      wnumend = wnumstr;
    }

  /* Now we can compute the exponent string.  */
  expstr = _itoa_word (exponent, expbuf + sizeof expbuf, 10, 0);
  wexpstr = _itowa_word (exponent,
			 wexpbuf + sizeof wexpbuf / sizeof (wchar_t), 10, 0);

  /* Now we have all information to compute the size.  */
  width -= ((negative || info->showsign || info->space)
	    /* Sign.  */
	    + 2    + 1 + 0 + precision + 1 + 1
	    /* 0x    h   .   hhh         P   ExpoSign.  */
	    + ((expbuf + sizeof expbuf) - expstr));
	    /* Exponent.  */

  /* Count the decimal point.
     A special case when the mantissa or the precision is zero and the `#'
     is not given.  In this case we must not print the decimal point.  */
  if (precision > 0 || info->alt)
    width -= wide ? 1 : strlen (decimal);

  if (!info->left && info->pad != '0' && width > 0)
    PADN (' ', width);

  if (negative)
    outchar ('-');
  else if (info->showsign)
    outchar ('+');
  else if (info->space)
    outchar (' ');

  outchar ('0');
  if ('X' - 'A' == 'x' - 'a')
    outchar (info->spec + ('x' - 'a'));
  else
    outchar (info->spec == 'A' ? 'X' : 'x');

  if (!info->left && info->pad == '0' && width > 0)
    PADN ('0', width);

  outchar (leading);

  if (precision > 0 || info->alt)
    {
      const wchar_t *wtmp = &decimalwc;
      PRINT (decimal, wtmp, wide ? 1 : strlen (decimal));
    }

  if (precision > 0)
    {
      ssize_t tofill = precision - (numend - numstr);
      PRINT (numstr, wnumstr, MIN (numend - numstr, precision));
      if (tofill > 0)
	PADN ('0', tofill);
    }

  if ('P' - 'A' == 'p' - 'a')
    outchar (info->spec + ('p' - 'a'));
  else
    outchar (info->spec == 'A' ? 'P' : 'p');

  outchar (expnegative ? '-' : '+');

  PRINT (expstr, wexpstr, (expbuf + sizeof expbuf) - expstr);

  if (info->left && info->pad != '0' && width > 0)
    PADN (info->pad, width);

  return done;
}