 INLINE void operator() (First first, Rest... rest) {
   enabled[first] = true;
   operator() (rest...);
 }