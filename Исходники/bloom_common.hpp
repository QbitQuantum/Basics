 static size_t opt_m(const double fp, const size_t n) {
   return n * (size_t)lrint(-log(fp) / LOG2_SQ);
 }