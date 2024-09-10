 forceinline TakesStatus
 takes(const View& x, const IntSet& s) {
   if ((x.max() < s.min()) || (x.min() > s.max()))
     return TS_NO;
   ViewRanges<View> ix(x);
   IntSetRanges is(s);
   switch (Iter::Ranges::compare(ix,is)) {
   case Iter::Ranges::CS_SUBSET: return TS_YES;
   case Iter::Ranges::CS_DISJOINT: return TS_NO;
   case Iter::Ranges::CS_NONE: return TS_MAYBE;
   default: GECODE_NEVER;
   }
   return TS_MAYBE;
 }