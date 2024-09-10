long long int
__llrintf (float x)
{
  float rx = __rintf (x);
  if (HAVE_PPC_FCTIDZ || rx != x)
    return (long long int) rx;
  else
    {
      float arx = fabsf (rx);
      /* Avoid incorrect exceptions from libgcc conversions (as of GCC
	 5): <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=59412>.  */
      if (arx < 0x1p31f)
	return (long long int) (long int) rx;
      else if (!(arx < 0x1p55f))
	return (long long int) (long int) (rx * 0x1p-32f) << 32;
      uint32_t i0;
      GET_FLOAT_WORD (i0, rx);
      int exponent = ((i0 >> 23) & 0xff) - 0x7f;
      unsigned long long int mant = (i0 & 0x7fffff) | 0x800000;
      mant <<= exponent - 23;
      return (long long int) ((i0 & 0x80000000) != 0 ? -mant : mant);
    }
}