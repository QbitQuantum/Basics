 forceinline RelTest
 rtest_gr(View x, View y) {
   if (x.max() <= y.min()) return RT_FALSE;
   if (x.min() >  y.max()) return RT_TRUE;
   return RT_MAYBE;
 }