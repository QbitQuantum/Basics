/* Update the message digest with the contents
 * of INBUF with length INLEN.
 */
static void
sha1_write( void *context, const void *inbuf_arg, size_t inlen)
{
  const unsigned char *inbuf = inbuf_arg;
  SHA1_CONTEXT *hd = context;
  size_t nblocks;

  if (hd->count == 64)  /* Flush the buffer. */
    {
      TRANSFORM( hd, hd->buf, 1 );
      _gcry_burn_stack (88+4*sizeof(void*));
      hd->count = 0;
      hd->nblocks++;
    }
  if (!inbuf)
    return;

  if (hd->count)
    {
      for (; inlen && hd->count < 64; inlen--)
        hd->buf[hd->count++] = *inbuf++;
      sha1_write (hd, NULL, 0);
      if (!inlen)
        return;
    }

  nblocks = inlen / 64;
  if (nblocks)
    {
      TRANSFORM (hd, inbuf, nblocks);
      hd->count = 0;
      hd->nblocks += nblocks;
      inlen -= nblocks * 64;
      inbuf += nblocks * 64;
    }
  _gcry_burn_stack (88+4*sizeof(void*));

  /* Save remaining bytes.  */
  for (; inlen && hd->count < 64; inlen--)
    hd->buf[hd->count++] = *inbuf++;
}