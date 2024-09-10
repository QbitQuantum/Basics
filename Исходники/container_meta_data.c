/**
 * Try to compress the given block of data.
 *
 * @param data block to compress; if compression
 *        resulted in a smaller block, the first
 *        bytes of data are updated to the compressed
 *        data
 * @param oldSize number of bytes in data
 * @param result set to the compressed data
 * @param newSize set to size of result
 * @return GNUNET_YES if compression reduce the size,
 *         GNUNET_NO if compression did not help
 */
static int
try_compression (const char *data, size_t oldSize, char **result,
                 size_t * newSize)
{
  char *tmp;
  uLongf dlen;

#ifdef compressBound
  dlen = compressBound (oldSize);
#else
  dlen = oldSize + (oldSize / 100) + 20;
  /* documentation says 100.1% oldSize + 12 bytes, but we
   * should be able to overshoot by more to be safe */
#endif
  tmp = GNUNET_malloc (dlen);
  if (Z_OK ==
      compress2 ((Bytef *) tmp, &dlen, (const Bytef *) data, oldSize, 9))
  {
    if (dlen < oldSize)
    {
      *result = tmp;
      *newSize = dlen;
      return GNUNET_YES;
    }
  }
  GNUNET_free (tmp);
  return GNUNET_NO;
}