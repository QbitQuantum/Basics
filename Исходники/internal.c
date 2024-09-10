/**
 * Process escape sequences ('+'=space, %HH)
 */
size_t
MHD_http_unescape (char *val)
{
  char *rpos = val;
  char *wpos = val;
  unsigned int num;

  while ('\0' != *rpos)
    {
      switch (*rpos)
	{
	case '+':
	  *wpos = ' ';
	  wpos++;
	  rpos++;
	  break;
	case '%':
	  if ( (1 == SSCANF (&rpos[1],
			     "%2x", &num)) ||
	       (1 == SSCANF (&rpos[1],
			     "%2X", &num)) )
	    {
	      *wpos = (unsigned char) num;
	      wpos++;
	      rpos += 3;
	      break;
	    }
	  /* intentional fall through! */
	default:
	  *wpos = *rpos;
	  wpos++;
	  rpos++;
	}
    }
  *wpos = '\0'; /* add 0-terminator */
  return wpos - val; /* = strlen(val) */
}