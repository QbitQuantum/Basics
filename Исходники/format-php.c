static void *
format_parse (const char *format, bool translated, char **invalid_reason)
{
  unsigned int directives;
  unsigned int numbered_arg_count;
  unsigned int allocated;
  struct numbered_arg *numbered;
  unsigned int unnumbered_arg_count;
  struct spec *result;

  directives = 0;
  numbered_arg_count = 0;
  allocated = 0;
  numbered = NULL;
  unnumbered_arg_count = 0;

  for (; *format != '\0';)
    if (*format++ == '%')
      {
	/* A directive.  */
	directives++;

	if (*format != '%')
	  {
	    /* A complex directive.  */
	    unsigned int number;
	    enum format_arg_type type;

	    number = ++unnumbered_arg_count;
	    if (isdigit (*format))
	      {
		const char *f = format;
		unsigned int m = 0;

		do
		  {
		    m = 10 * m + (*f - '0');
		    f++;
		  }
		while (isdigit (*f));

		if (*f == '$')
		  {
		    if (m == 0)
		      {
			*invalid_reason = INVALID_ARGNO_0 (directives);
			goto bad_format;
		      }
		    number = m;
		    format = ++f;
		    --unnumbered_arg_count;
		  }
	      }

	    /* Parse flags.  */
	    for (;;)
	      {
		if (*format == '0' || *format == '-' || *format == ' ')
		  format++;
		else if (*format == '\'')
		  {
		    format++;
		    if (*format == '\0')
		      {
			*invalid_reason = INVALID_UNTERMINATED_DIRECTIVE ();
			goto bad_format;
		      }
		    format++;
		  }
		else
		  break;
	      }

	    /* Parse width.  */
	    if (isdigit (*format))
	      {
		do
		  format++;
		while (isdigit (*format));
	      }

	    /* Parse precision.  */
	    if (*format == '.')
	      {
		format++;

		if (isdigit (*format))
		  {
		    do
		      format++;
		    while (isdigit (*format));
		  }
		else
		  --format;	/* will jump to bad_format */
	      }

	    /* Parse size.  */
	    if (*format == 'l')
	      format++;

	    switch (*format)
	      {
	      case 'b': case 'd': case 'u': case 'o': case 'x': case 'X':
		type = FAT_INTEGER;
		break;
	      case 'e': case 'f':
		type = FAT_FLOAT;
		break;
	      case 'c':
		type = FAT_CHARACTER;
		break;
	      case 's':
		type = FAT_STRING;
		break;
	      default:
		*invalid_reason =
		  (*format == '\0'
		   ? INVALID_UNTERMINATED_DIRECTIVE ()
		   : INVALID_CONVERSION_SPECIFIER (directives, *format));
		goto bad_format;
	      }

	    if (allocated == numbered_arg_count)
	      {
		allocated = 2 * allocated + 1;
		numbered = (struct numbered_arg *) xrealloc (numbered, allocated * sizeof (struct numbered_arg));
	      }
	    numbered[numbered_arg_count].number = number;
	    numbered[numbered_arg_count].type = type;
	    numbered_arg_count++;
	  }

	format++;
      }

  /* Sort the numbered argument array, and eliminate duplicates.  */
  if (numbered_arg_count > 1)
    {
      unsigned int i, j;
      bool err;

      qsort (numbered, numbered_arg_count,
	     sizeof (struct numbered_arg), numbered_arg_compare);

      /* Remove duplicates: Copy from i to j, keeping 0 <= j <= i.  */
      err = false;
      for (i = j = 0; i < numbered_arg_count; i++)
	if (j > 0 && numbered[i].number == numbered[j-1].number)
	  {
	    enum format_arg_type type1 = numbered[i].type;
	    enum format_arg_type type2 = numbered[j-1].type;
	    enum format_arg_type type_both;

	    if (type1 == type2)
	      type_both = type1;
	    else
	      {
		/* Incompatible types.  */
		type_both = type1;
		if (!err)
		  *invalid_reason =
		    INVALID_INCOMPATIBLE_ARG_TYPES (numbered[i].number);
		err = true;
	      }

	    numbered[j-1].type = type_both;
	  }
	else
	  {
	    if (j < i)
	      {
		numbered[j].number = numbered[i].number;
		numbered[j].type = numbered[i].type;
	      }
	    j++;
	  }
      numbered_arg_count = j;
      if (err)
	/* *invalid_reason has already been set above.  */
	goto bad_format;
    }

  result = (struct spec *) xmalloc (sizeof (struct spec));
  result->directives = directives;
  result->numbered_arg_count = numbered_arg_count;
  result->allocated = allocated;
  result->numbered = numbered;
  return result;

 bad_format:
  if (numbered != NULL)
    free (numbered);
  return NULL;
}