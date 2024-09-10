static bool peek_ipv6(const char *str, size_t *skip)
{
  /*
   * Scan for a potential IPv6 literal.
   * - Valid globs contain a hyphen and <= 1 colon.
   * - IPv6 literals contain no hyphens and >= 2 colons.
   */
  size_t i = 0;
  size_t colons = 0;
  if(str[i++] != '[') {
    return FALSE;
  }
  for(;;) {
    const char c = str[i++];
    if(ISALNUM(c) || c == '.' || c == '%') {
      /* ok */
    }
    else if(c == ':') {
      colons++;
    }
    else if(c == ']') {
      *skip = i;
      return colons >= 2 ? TRUE : FALSE;
    }
    else {
      return FALSE;
    }
  }
}