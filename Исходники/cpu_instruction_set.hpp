 static bool internal_cpuid(int32_t out[4], int32_t x)
 {
   #if defined __GNUC__
   __cpuid_count(x, 0, out[0], out[1], out[2], out[3]);
   return true;
   #endif
   #if defined _MSC_VER
   __cpuidex(out, x, 0);
   return true;
   #endif
   return false;
 }