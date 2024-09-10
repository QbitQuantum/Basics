int
ether_line (const char *line, struct ether_addr *addr, char *hostname)
{
  size_t cnt;
  char *cp;

  for (cnt = 0; cnt < 6; ++cnt)
    {
      unsigned int number;
      char ch;

      ch = _tolower (*line++);
      if ((ch < '0' || ch > '9') && (ch < 'a' || ch > 'f'))
	return -1;
      number = isdigit (ch) ? (ch - '0') : (ch - 'a' + 10);

      ch = _tolower (*line);
      if ((cnt < 5 && ch != ':') || (cnt == 5 && ch != '\0' && !isspace (ch)))
	{
	  ++line;
	  if ((ch < '0' || ch > '9') && (ch < 'a' || ch > 'f'))
	    return -1;
	  number <<= 4;
	  number += isdigit (ch) ? (ch - '0') : (ch - 'a' + 10);

	  ch = *line;
	  if (cnt < 5 && ch != ':')
	    return -1;
	}

      /* Store result.  */
      addr->ether_addr_octet[cnt] = (unsigned char) number;

      /* Skip ':'.  */
      if (ch != '\0')
	++line;
    }

  /* Remove trailing white space.  */
  cp = strchr (line, '#');
  if (cp == NULL)
    cp = line + strlen (line);
  while (cp > line && isspace (cp[-1]))
    --cp;

  if (cp == line)
    /* No hostname.  */
    return -1;

  /* XXX This can cause trouble because the hostname might be too long
     but we have no possibility to check it here.  */
  memcpy (hostname, line, cp - line);
  hostname [cp - line] = '\0';

  return 0;
}