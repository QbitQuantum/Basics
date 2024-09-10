/*
 * static int
 * inet_net_pton_ipv4(src, dst, size)
 *      convert IPv4 network number from presentation to network format.
 *      accepts hex octets, hex strings, decimal octets, and /CIDR.
 *      "size" is in bytes and describes "dst".
 * return:
 *      number of bits, either imputed classfully or specified with /CIDR,
 *      or -1 if some failure occurred (check errno).  ENOENT means it was
 *      not an IPv4 network specification.
 * note:
 *      network byte order assumed.  this means 192.5.5.240/28 has
 *      0b11110000 in its fourth octet.
 * note:
 *      On Windows we store the error in the thread errno, not
 *      in the winsock error code. This is to avoid loosing the
 *      actual last winsock error. So use macro ERRNO to fetch the
 *      errno this funtion sets when returning (-1), not SOCKERRNO.
 * author:
 *      Paul Vixie (ISC), June 1996
 */
static int
inet_net_pton_ipv4(const char *src, unsigned char *dst, size_t size)
{
  static const char xdigits[] = "0123456789abcdef";
  static const char digits[] = "0123456789";
  int n, ch, tmp = 0, dirty, bits;
  const unsigned char *odst = dst;

  ch = *src++;
  if (ch == '0' && (src[0] == 'x' || src[0] == 'X')
      && ISXDIGIT(src[1])) {
    /* Hexadecimal: Eat nybble string. */
    if (!size)
      goto emsgsize;
    dirty = 0;
    src++;  /* skip x or X. */
    while ((ch = *src++) != '\0' && ISXDIGIT(ch)) {
      if (ISUPPER(ch))
        ch = tolower(ch);
      n = (int)(strchr(xdigits, ch) - xdigits);
      if (dirty == 0)
        tmp = n;
      else
        tmp = (tmp << 4) | n;
      if (++dirty == 2) {
        if (!size--)
          goto emsgsize;
        *dst++ = (unsigned char) tmp;
        dirty = 0;
      }
    }
    if (dirty) {  /* Odd trailing nybble? */
      if (!size--)
        goto emsgsize;
      *dst++ = (unsigned char) (tmp << 4);
    }
  } else if (ISDIGIT(ch)) {
    /* Decimal: eat dotted digit string. */
    for (;;) {
      tmp = 0;
      do {
        n = (int)(strchr(digits, ch) - digits);
        tmp *= 10;
        tmp += n;
        if (tmp > 255)
          goto enoent;
      } while ((ch = *src++) != '\0' &&
               ISDIGIT(ch));
      if (!size--)
        goto emsgsize;
      *dst++ = (unsigned char) tmp;
      if (ch == '\0' || ch == '/')
        break;
      if (ch != '.')
        goto enoent;
      ch = *src++;
      if (!ISDIGIT(ch))
        goto enoent;
    }
  } else
    goto enoent;

  bits = -1;
  if (ch == '/' &&
      ISDIGIT(src[0]) && dst > odst) {
    /* CIDR width specifier.  Nothing can follow it. */
    ch = *src++;    /* Skip over the /. */
    bits = 0;
    do {
      n = (int)(strchr(digits, ch) - digits);
      bits *= 10;
      bits += n;
    } while ((ch = *src++) != '\0' && ISDIGIT(ch));
    if (ch != '\0')
      goto enoent;
    if (bits > 32)
      goto emsgsize;
  }

  /* Firey death and destruction unless we prefetched EOS. */
  if (ch != '\0')
    goto enoent;

  /* If nothing was written to the destination, we found no address. */
  if (dst == odst)
    goto enoent;
  /* If no CIDR spec was given, infer width from net class. */
  if (bits == -1) {
    if (*odst >= 240)       /* Class E */
      bits = 32;
    else if (*odst >= 224)  /* Class D */
      bits = 8;
    else if (*odst >= 192)  /* Class C */
      bits = 24;
    else if (*odst >= 128)  /* Class B */
      bits = 16;
    else                    /* Class A */
      bits = 8;
    /* If imputed mask is narrower than specified octets, widen. */
    if (bits < ((dst - odst) * 8))
      bits = (int)(dst - odst) * 8;
    /*
     * If there are no additional bits specified for a class D
     * address adjust bits to 4.
     */
    if (bits == 8 && *odst == 224)
      bits = 4;
  }
  /* Extend network to cover the actual mask. */
  while (bits > ((dst - odst) * 8)) {
    if (!size--)
      goto emsgsize;
    *dst++ = '\0';
  }
  return (bits);

  enoent:
  SET_ERRNO(ENOENT);
  return (-1);

  emsgsize:
  SET_ERRNO(EMSGSIZE);
  return (-1);
}