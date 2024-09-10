/*---------------------------------------------------------------------------
|   Facility      :  libnform  
|   Function      :  static bool Check_This_Field(
|                                                 FIELD * field,
|                                                 const void * argp)
|   
|   Description   :  Validate buffer content to be a valid integer value
|
|   Return Values :  TRUE  - field is valid
|                    FALSE - field is invalid
+--------------------------------------------------------------------------*/
static bool
Check_This_Field(FIELD *field, const void *argp)
{
  const thisARG *argi = (const thisARG *)argp;
  long low = argi->low;
  long high = argi->high;
  int prec = argi->precision;
  unsigned char *bp = (unsigned char *)field_buffer(field, 0);
  char *s = (char *)bp;
  long val;
  char buf[100];
  bool result = FALSE;

  while (*bp && *bp == ' ')
    bp++;
  if (*bp)
    {
      if (*bp == '-')
	bp++;
#if USE_WIDEC_SUPPORT
      if (*bp)
	{
	  bool blank = FALSE;
	  int len;
	  int n;
	  wchar_t *list = _nc_Widen_String((char *)bp, &len);

	  if (list != 0)
	    {
	      result = TRUE;
	      for (n = 0; n < len; ++n)
		{
		  if (blank)
		    {
		      if (list[n] != ' ')
			{
			  result = FALSE;
			  break;
			}
		    }
		  else if (list[n] == ' ')
		    {
		      blank = TRUE;
		    }
		  else if (!isDigit(list[n]))
		    {
		      result = FALSE;
		      break;
		    }
		}
	      free(list);
	    }
	}
#else
      while (*bp)
	{
	  if (!isdigit(UChar(*bp)))
	    break;
	  bp++;
	}
      while (*bp && *bp == ' ')
	bp++;
      result = (*bp == '\0');
#endif
      if (result)
	{
	  val = atol(s);
	  if (low < high)
	    {
	      if (val < low || val > high)
		result = FALSE;
	    }
	  if (result)
	    {
	      snprintf(buf, sizeof(buf), "%.*ld", (prec > 0 ? prec : 0), val);
	      set_field_buffer(field, 0, buf);
	    }
	}
    }
  return (result);
}