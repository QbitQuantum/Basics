int socks5_connect (BIO *b)
{
  unsigned char buf[NI_MAXHOST + 16];
  int r;
  struct proxy_ctx *ctx = (struct proxy_ctx *) b->ptr;
  uint16_t port_n = htons (ctx->port);
  size_t sz = 0;
  /* the length for SOCKS addresses is only one byte. */
  if (strnlen (ctx->host, UINT8_MAX + 1) == UINT8_MAX + 1)
    return 0;
  verb ("V: proxy5: connecting %s:%d", ctx->host, ctx->port);
  /*
   * Hello packet layout:
   * 1b: Version
   * 1b: auth methods
   * nb: method types
   *
   * We support only one method (no auth, 0x00). Others listed in RFC
   * 1928.
   */
  buf[0] = 0x05;
  buf[1] = 0x01;
  buf[2] = 0x00;
  r = BIO_write (b->next_bio, buf, 3);
  if (r != 3)
    return 0;
  r = BIO_read (b->next_bio, buf, 2);
  if (r != 2)
    return 0;
  if (buf[0] != 0x05 || buf[1] != 0x00)
    {
      verb ("V: proxy5: auth error %02x %02x", buf[0], buf[1]);
      return 0;
    }
  /*
   * Connect packet layout:
   * 1b: version
   * 1b: command (0x01 is connect)
   * 1b: reserved, 0x00
   * 1b: addr type (0x03 is domain name)
   * nb: addr len (1b) + addr bytes, no null termination
   * 2b: port, network byte order
   */
  buf[0] = 0x05;
  buf[1] = 0x01;
  buf[2] = 0x00;
  buf[3] = 0x03;
  buf[4] = strlen (ctx->host);
  sz += 5;
  memcpy (buf + 5, ctx->host, strlen (ctx->host));
  sz += strlen (ctx->host);
  memcpy (buf + sz, &port_n, sizeof (port_n));
  sz += sizeof (port_n);
  r = BIO_write (b->next_bio, buf, sz);
  if ( -1 == r )
    return -1;
  if ( (size_t) r != sz)
    return 0;
  /*
   * Server's response:
   * 1b: version
   * 1b: status (0x00 is okay)
   * 1b: reserved, 0x00
   * 1b: addr type (0x03 is domain name, 0x01 ipv4)
   * nb: addr len (1b) + addr bytes, no null termination
   * 2b: port, network byte order
   */
  /* grab up through the addr type */
  r = BIO_read (b->next_bio, buf, 4);
  if ( -1 == r )
    return -1;
  if (r != 4)
    return 0;
  if (buf[0] != 0x05 || buf[1] != 0x00)
    {
      verb ("V: proxy5: connect error %02x %02x", buf[0], buf[1]);
      return 0;
    }
  if (buf[3] == 0x03)
    {
      unsigned int len;
      r = BIO_read (b->next_bio, buf + 4, 1);
      if (r != 1)
        return 0;
      /* host (buf[4] bytes) + port (2 bytes) */
      len = buf[4] + 2;
      while (len)
        {
          r = BIO_read (b->next_bio, buf + 5, min (len, sizeof (buf)));
          if (r <= 0)
            return 0;
          len -= min (len, r);
        }
    }
  else if (buf[3] == 0x01)
    {
      /* 4 bytes ipv4 addr, 2 bytes port */
      r = BIO_read (b->next_bio, buf + 4, 6);
      if (r != 6)
        return 0;
    }
  verb ("V: proxy5: connected");
  ctx->connected = 1;
  return 1;
}