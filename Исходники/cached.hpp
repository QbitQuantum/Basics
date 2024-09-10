 void
 CachedView<View>::initCache(Space& home, const IntSet& s) {
   _firstRange = NULL;
   for (int i=s.ranges(); i--;) {
     _firstRange = new (home) RangeList(s.min(i),s.max(i),_firstRange);
     if (i==s.ranges()-1)
       _lastRange = _firstRange;
   }
   _size = s.size();
 }