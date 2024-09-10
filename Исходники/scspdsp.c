static INLINE unsigned clz(u32 v)
{
#if defined(__GNUC__) || defined(__clang__) || defined(__ICC) || defined(__INTEL_COMPILER)
  return __builtin_clz(v);
#elif defined(_MSC_VER)
  unsigned long idx;

  _BitScanReverse(&idx, v);

  return 31 ^ idx;
#else
  unsigned ret = 0;
  unsigned tmp;

  tmp = !(v & 0xFFFF0000) << 4; v <<= tmp; ret += tmp;
  tmp = !(v & 0xFF000000) << 3; v <<= tmp; ret += tmp;
  tmp = !(v & 0xF0000000) << 2; v <<= tmp; ret += tmp;
  tmp = !(v & 0xC0000000) << 1; v <<= tmp; ret += tmp;
  tmp = !(v & 0x80000000) << 0;            ret += tmp;

  return(ret);
#endif
}