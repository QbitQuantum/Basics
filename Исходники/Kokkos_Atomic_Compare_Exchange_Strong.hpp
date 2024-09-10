inline
long atomic_compare_exchange( volatile long * const dest, const long compare, const long val )
{ 
#if defined( KOKKOS_ENABLE_RFO_PREFETCH )
  _mm_prefetch( (const char*) dest, _MM_HINT_ET0 );
#endif
  return __sync_val_compare_and_swap(dest,compare,val);
}