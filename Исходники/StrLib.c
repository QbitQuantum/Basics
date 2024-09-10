char *str_ftoa(char *result, double value, double reference)

/*
 *  str_ftoa - convert real value to floating equivalent
 */

{
  static char *digit = "0123456789";
  char format[STR_MAX];

  double abs_val;
  char str[STR_MAX], *fcp, *cp;
  int count, exponent, factor, mantissa;
  int fdigits, digits, scientific_notation;

  if (value != 0)
    {
      abs_val = fabs(value);

      exponent = (int) (log10(abs_val) + pow(10.0, -NDIGITS));
      if (exponent < 0)
	exponent--;

      factor = (NDIGITS - 1) - exponent;
      mantissa = (int) (abs_val * pow(10.0, factor) + 0.5);

      strcpy(result, "");

      count = 0;
      fdigits = digits = 0;

      do
	{
	  count++;

	  strcpy(str, result);
	  result[0] = digit[mantissa % 10];
	  result[1] = '\0';
	  strcat(result, str);

	  if (count == factor)
	    {
	      strcpy(str, result);
	      strcpy(result, ".");
	      strcat(result, str);
	    }

	  mantissa = mantissa / 10;
	}
      while (count != NDIGITS);

      scientific_notation = (exponent <= 1 - NDIGITS) || (exponent >= NDIGITS);

      if (scientific_notation || exponent < 0)
	{
	  if (!scientific_notation)
	    {
	      strcpy(str, "");
	      str_pad(str, '0', -exponent - 1);
	      strcat(str, result);
	      strcpy(result, str);
	    }

	  strcpy(str, "0.");
	  strcat(str, result);
	  strcpy(result, str);
	}

      if (value < 0)
	{
	  strcpy(str, "-");
	  strcat(str, result);
	  strcpy(result, str);
	}

      if (strchr(result, '.') != 0)
	{
	  str_remove(result, '0');
	  str_remove(result, '.');
	}

      if (scientific_notation)
	{
	  strcat(result, "E");
	  sprintf(str, "%d", exponent + 1);
	  strcat(result, str);
	}
      else
	{
	  sprintf(format, "%lg", reference);

	  if (strchr(format, 'E') == 0)

	    if ((fcp = strchr(format, '.')) != 0)
	      {
		fdigits = strlen(format) - (int) (fcp - format) - 1;

		if ((cp = strchr(result, '.')) != 0)
		  {
		    digits = strlen(result) - (int) (cp - result) - 1;

		    if (fdigits > digits)
		      strncat(result, "000000000", fdigits - digits);
		  }
		else
		  {
		    strcat(result, ".");
		    strncat(result, "000000000", fdigits);
		  }
	      }
	}
    }
  else
    strcpy(result, "0");

  return result;
}