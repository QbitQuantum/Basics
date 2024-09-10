static unichar *
handle_uniquotes (rc_uint_type *len)
{
  const char *input = rclex_tok;
  unichar *ret, *s;
  const char *t;
  int ch;
  int num_xdigits;

  ret = get_unistring (strlen (input) + 1);

  s = ret;
  t = input;
  if ((*t == 'L' || *t == 'l') && t[1] == '"')
    t += 2;
  else if (*t == '"')
    ++t;
  while (*t != '\0')
    {
      if (*t == '\\')
	{
	  ++t;
	  switch (*t)
	    {
	    case '\0':
	      rcparse_warning ("backslash at end of string");
	      break;

	    case '\"':
	      rcparse_warning ("use \"\" to put \" in a string");
	      break;

	    case 'a':
	      *s++ = ESCAPE_B; /* Strange, but true...  */
	      ++t;
	      break;

	    case 'b':
	      *s++ = ESCAPE_B;
	      ++t;
	      break;

	    case 'f':
	      *s++ = ESCAPE_F;
	      ++t;
	      break;

	    case 'n':
	      *s++ = ESCAPE_N;
	      ++t;
	      break;

	    case 'r':
	      *s++ = ESCAPE_R;
	      ++t;
	      break;

	    case 't':
	      *s++ = ESCAPE_T;
	      ++t;
	      break;

	    case 'v':
	      *s++ = ESCAPE_V;
	      ++t;
	      break;

	    case '\\':
	      *s++ = (unichar) *t++;
	      break;

	    case '0': case '1': case '2': case '3':
	    case '4': case '5': case '6': case '7':
	      ch = *t - '0';
	      ++t;
	      if (*t >= '0' && *t <= '7')
		{
		  ch = (ch << 3) | (*t - '0');
		  ++t;
		  if (*t >= '0' && *t <= '7')
		    {
		      ch = (ch << 3) | (*t - '0');
		      ++t;
		    }
		}
	      *s++ = (unichar) ch;
	      break;

	    case 'x': case 'X':
	      ++t;
	      ch = 0;
	      /* We only handle two byte chars here.  Make sure
		 we finish an escape sequence like "/xB0ABC" after
		 the first two digits.  */
              num_xdigits = 4;
 	      while (num_xdigits--)
		{
		  if (*t >= '0' && *t <= '9')
		    ch = (ch << 4) | (*t - '0');
		  else if (*t >= 'a' && *t <= 'f')
		    ch = (ch << 4) | (*t - 'a' + 10);
		  else if (*t >= 'A' && *t <= 'F')
		    ch = (ch << 4) | (*t - 'A' + 10);
		  else
		    break;
		  ++t;
		}
	      *s++ = (unichar) ch;
	      break;

	    default:
	      rcparse_warning ("unrecognized escape sequence");
	      *s++ = '\\';
	      *s++ = (unichar) *t++;
	      break;
	    }
	}
      else if (*t != '"')
	*s++ = (unichar) *t++;
      else if (t[1] == '\0')
	break;
      else if (t[1] == '"')
	{
	  *s++ = '"';
	  t += 2;
	}
      else
	{
	  ++t;
	  assert (ISSPACE (*t));
	  while (ISSPACE (*t))
	    {
	      if ((*t) == '\n')
		++rc_lineno;
	      ++t;
	    }
	  if (*t == '\0')
	    break;
	  assert (*t == '"');
	  ++t;
	}
    }

  *s = '\0';

  *len = s - ret;

  return ret;
}