 inline void
 Limits::check(const IntSet& s, const char* l) {
   if ((s.size() > 0) &&
       ((s.min() < min) || (s.max() > max) ||
        (s.min() > max) || (s.max() < min)))
     throw OutOfLimits(l);
 }