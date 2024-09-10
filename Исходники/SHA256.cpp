inline uint32 b2i(const byte *b) // Big endian bytes to integer.
{
#if defined(_MSC_VER)/* && defined(LITTLE_ENDIAN)*/
  return _byteswap_ulong(*(uint32 *)b);
#else
  return uint32(b[0]<<24) | uint32(b[1]<<16) | uint32(b[2]<<8) | b[3];
#endif
}