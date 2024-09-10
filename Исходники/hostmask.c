/* Fixed so ::/0 (any IPv6 address) is valid
   Also a bug in DigitParse above.
   -Gozem 2002-07-19 [email protected]
*/
static int
try_parse_v6_netmask(const char *text, struct irc_ssaddr *addr, int *b)
{
  char c;
  int d[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  int dp = 0;
  int nyble = 4;
  int finsert = -1;
  int bits = 128;
  int deficit = 0;
  short dc[8];
  struct sockaddr_in6 *const v6 = (struct sockaddr_in6 *)addr;

  for (const char *p = text; (c = *p); ++p)
  {
    if (IsXDigit(c))
    {
      if (nyble == 0)
        return HM_HOST;
      DigitParse(c);
      d[dp] |= c << (4 * --nyble);
    }
    else if (c == ':')
    {
      if (p > text && *(p - 1) == ':')
      {
        if (finsert >= 0)
          return HM_HOST;
        finsert = dp;
      }
      else
      {
        /* If there were less than 4 hex digits, e.g. :ABC: shift right
         * so we don't interpret it as ABC0 -A1kmm */
        d[dp] = d[dp] >> 4 * nyble;
        nyble = 4;
        if (++dp >= 8)
          return HM_HOST;
      }
    }
    else if (c == '*')
    {
      /* * must be last, and * is ambiguous if there is a ::... -A1kmm */
      if (finsert >= 0 || *(p + 1) || dp == 0 || *(p - 1) != ':')
        return HM_HOST;
      bits = dp * 16;
    }
    else if (c == '/')
    {
      char *after;

      d[dp] = d[dp] >> 4 * nyble;
      ++dp;
      bits = strtoul(p + 1, &after, 10);

      if (bits < 0 || *after)
        return HM_HOST;
      if (bits > dp * 4 && !(finsert >= 0 && bits <= 128))
        return HM_HOST;
      break;
    }