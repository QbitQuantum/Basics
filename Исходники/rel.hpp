 forceinline RelTest
 holds(VX x, const IntSet& y) {
   if ((x.max() < y.min()) || (y.max() < x.min()))
     return RT_FALSE;
   ViewRanges<VX> rx(x);
   IntSetRanges ry(y);
   switch (Iter::Ranges::compare(rx,ry)) {
   case Iter::Ranges::CS_SUBSET:
     return RT_TRUE;
   case Iter::Ranges::CS_DISJOINT:
     return RT_FALSE;
   case Iter::Ranges::CS_NONE:
     return RT_MAYBE;
   default:
     GECODE_NEVER;
   }
   GECODE_NEVER;
   return RT_MAYBE;
 }