 KOKKOS_INLINE_FUNCTION
   T atomic_compare_exchange(volatile T * const dest, const T & compare,
   typename Kokkos::Impl::enable_if< sizeof(T) == sizeof(Impl::cas128_t), const T & >::type val)
 {
   union U {
     Impl::cas128_t i;
     T t;
     KOKKOS_INLINE_FUNCTION U() {};
   } tmp, newval;
   newval.t = val;
   tmp.i = _InterlockedCompareExchange128((LONGLONG*)dest, newval.i.upper, newval.i.lower, *((LONGLONG*)&compare));
   return tmp.t;
 }