 forceinline Iter::Ranges::CompareStatus
 ValSet::compare(View x) const {
   if (empty() || (x.max() < min()) || (x.min() > max()))
     return Iter::Ranges::CS_DISJOINT;
   ValSet::Ranges vsr(*this);
   ViewRanges<View> xr(x);
   return Iter::Ranges::compare(xr,vsr);
 }