int
json_get_token (const wchar_t * z, const size_t len, int *tokenType,
		double *number)
{
  wchar_t *p;
  int i;
  if (!z || !tokenType || len == 0 || !number)
    {
      return -1;
    }

  *tokenType = TK_ILLEGAL;

  if (iswspace (z[0]))
    {
      for (i = 1; iswspace (z[i]); i++)
	{
	}
      *tokenType = TK_SPACE;
      return i;
    }

  switch (*z)
    {
    case '"':
      {
	/* NOTE: See RFC 4627 Section 2.5 */
	for (i = 1; i < len; i++)
	  {
	    /* Check if we're at the end of the string */
	    if (z[i] == '"')
	      {
		*tokenType = TK_STRING;
		return i + 1;
	      }
	    /* Check for characters that are allowed unescaped */
	    else if (z[i] == 0x20 || z[i] == 0x21 ||
		     (z[i] >= 0x23 && z[i] <= 0x5B) ||
		     (z[i] >= 0x5D && z[i] <= 0x10FFFF))
	      {
		continue;
	      }
	    /* Check for allowed escaped characters */
	    else if (z[i] == '\\')
	      {
		if (++i >= len)
		  {
		    return -1;
		  }

		switch (z[i])
		  {
		  case '"':
		  case '\\':
		  case '/':
		  case 'b':
		  case 'f':
		  case 'n':
		  case 'r':
		  case 't':
		    break;
		  case 'u':
		    {
		      int offset;
		      i += 4;
		      if (i >= len)
			{
			  return -1;
			}

		      /* Check the four characters following \u are valid hex */
		      for (offset = 3; offset >= 0; offset--)
			{
			  if (!iswxdigit (z[i - offset]))
			    {
			      /* Illegal non-hex character after \u */
			      return -1;
			    }
			}
		      break;
		    }

		  default:
		    /* Illegal escape value */
		    return -1;
		  }
	      }
	    else
	      {
		/* Illegal code */
		return -1;
	      }
	  }
	break;
      }
    case ':':
      {
	*tokenType = TK_COLON;
	return 1;
      }
    case ',':
      {
	*tokenType = TK_COMMA;
	return 1;
      }
    case '{':
      {
	*tokenType = TK_LCURLY;
	return 1;
      }
    case '}':
      {
	*tokenType = TK_RCURLY;
	return 1;
      }
    case '[':
      {
	*tokenType = TK_LBRACKET;
	return 1;
      }
    case ']':
      {
	*tokenType = TK_RBRACKET;
	return 1;
      }
    }

  /* Check for keywords */
  for (i = 0; i < NUM_KEYWORDS; i++)
    {
      struct keyword *kw = keywords + i;
      if (wcsncmp (z, kw->z, kw->len) == 0)
	{
	  *tokenType = kw->tokenType;
	  return kw->len;
	}
    }

  /* Check for number */
  *number = wcstod (z, &p);
  if (p != z)
    {
      *tokenType = TK_NUMBER;
      return (p - z);
    }

  /* ???? */
  *tokenType = TK_ILLEGAL;
  return -1;
}