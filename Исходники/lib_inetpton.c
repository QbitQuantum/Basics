int inet_pton(int af, FAR const char *src, FAR void *dst)
{
#ifndef CONFIG_NET_IPv6
  size_t srcoffset;
  size_t numoffset;
  int value;
  int ndots;
  uint8_t ch;
  char numstr[4];
  uint8_t *ip;

  DEBUGASSERT(src && dst);

  if (af != AF_INET)
    {
      set_errno(EAFNOSUPPORT);
      return -1;
    }

  (void)memset(dst, 0, sizeof(struct in_addr));

  ip        = (uint8_t *)dst;
  srcoffset = 0;
  numoffset = 0;
  ndots     = 0;

  for(;;)
    {
      ch = (uint8_t)src[srcoffset++];

      if (ch == '.' || ch == '\0')
        {
          if (ch == '.' && ndots >= 4)
            {
              /* Too many dots */

              break;
            }

          if (numoffset <= 0)
            {
              /* Empty numeric string */

              break;
            }

          numstr[numoffset] = '\0';
          numoffset = 0;

          value = atoi(numstr);
          if (value < 0 || value > 255)
            {
              /* Out of range value */

              break;
            }

          ip[ndots] = (uint8_t)value;

          if (ch == '\0')
            {
              if (ndots != 3)
                {
                  /* Not enough dots */

                  break;
                }

              /* Return 1 if the conversion succeeds */

              return 1;
            }

          ndots++;
        }
      else if (ch >= '0' && ch <= '9')
        {
          numstr[numoffset++] = ch;
          if (numoffset >= 4)
            {
              /* Number is too long */

              break;
            }
        }
      else
        {
          /* Illegal character */

          break;
        }
    }

  /* Return zero if there is any problem parsing the input */

  return 0;
#else
  size_t srcoffset;
  size_t numoffset;
  long value;
  int nsep;
  int nrsep;
  uint8_t ch;
  char numstr[5];
  uint8_t ip[sizeof(struct in6_addr)];
  uint8_t rip[sizeof(struct in6_addr)];
  bool rtime;

  DEBUGASSERT(src && dst);

  if (af != AF_INET6)
    {
      set_errno(EAFNOSUPPORT);
      return -1;
    }

  (void)memset(dst, 0, sizeof(struct in6_addr));

  srcoffset = 0;
  numoffset = 0;
  nsep      = 0;
  nrsep     = 0;
  rtime     = false;

  for(;;)
    {
      ch = (uint8_t)src[srcoffset++];

      if (ch == ':' || ch == '\0')
        {
          if (ch == ':' && (nsep + nrsep) >= 8)
            {
              /* Too many separators */

              break;
            }

          if (ch != '\0' && numoffset <= 0)
            {
              /* Empty numeric string */

              if (rtime && nrsep > 1)
                {
                  /* dup simple */

                  break;
                }

              numoffset = 0;
              rtime = true;
              continue;
            }

          numstr[numoffset] = '\0';
          numoffset = 0;

          value = strtol(numstr, NULL, 16);
          if (value < 0 || value > 0xffff)
            {
              /* Out of range value */

              break;
            }

          if (!rtime)
            {
              ip[(nsep << 1) + 0] = (uint8_t)((value >> 8) & 0xff);
              ip[(nsep << 1) + 1] = (uint8_t)((value >> 0) & 0xff);
              nsep++;
            }
          else
            {
              rip[(nrsep << 1) + 0] = (uint8_t)((value >> 8) & 0xff);
              rip[(nrsep << 1) + 1] = (uint8_t)((value >> 0) & 0xff);
              nrsep++;
            }

          if (ch == '\0' /* || ch == '/' */)
            {
              if ((nsep <= 1 && nrsep <= 0) ||
                  (nsep + nrsep) < 1 ||
                  (nsep + nrsep) > 8)
                {
                  /* Separator count problem */

                  break;
                }

              if (nsep > 0)
                {
                  memcpy(dst, &ip[0], nsep << 1);
                }

              if (nrsep > 0)
                {
                  memcpy(dst + (16 - (nrsep << 1)), &rip[0], nrsep << 1);
                }

              /* Return 1 if the conversion succeeds */

              return 1;
            }
        }