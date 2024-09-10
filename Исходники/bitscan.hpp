BOOST_FORCEINLINE unsigned find_msb(Unsigned mask, const mpl::int_<2>&)
{
   unsigned long result;
   _BitScanReverse64(&result, mask);
   return result;
}