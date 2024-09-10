 inline
 JLBasis::Index
 JLBasis::last_generator(const int j) const
 {
   assert(j >= j0());
   return JLIndex(j, 0, 1, 1<<j);
 }