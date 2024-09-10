 CMT_INLINE vec<vec<T, 2>, N> process(const vec<vec<T, 2>, N>& x, csizes_t<indices...>) const
 {
     return vec<vec<T, 2>, N>(hadd(transpose(x[indices] * matrix))...);
 }