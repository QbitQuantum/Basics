struct ether_addr *
ether_aton_r (const char *asc, struct ether_addr *addr)
{
  size_t cnt;

  for (cnt = 0; cnt < 6; ++cnt)
    {
      unsigned int number;
      char ch;

      ch = _tolower (*asc++);
      if ((ch < '0' || ch > '9') && (ch < 'a' || ch > 'f'))
	return NULL;
      number = isdigit (ch) ? (ch - '0') : (ch - 'a' + 10);

      ch = _tolower (*asc);
      if ((cnt < 5 && ch != ':') || (cnt == 5 && ch != '\0' && !isspace (ch)))
	{
	  ++asc;
	  if ((ch < '0' || ch > '9') && (ch < 'a' || ch > 'f'))
	    return NULL;
	  number <<= 4;
	  number += isdigit (ch) ? (ch - '0') : (ch - 'a' + 10);

	  ch = *asc;
	  if (cnt < 5 && ch != ':')
	    return NULL;
	}

      /* Store result.  */
      addr->ether_addr_octet[cnt] = (unsigned char) number;

      /* Skip ':'.  */
      ++asc;
    }

  return addr;
}