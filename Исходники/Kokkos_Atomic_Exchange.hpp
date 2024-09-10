__inline__ __device__
T atomic_exchange( volatile T * const dest ,
    typename Kokkos::Impl::enable_if<
                  ( sizeof(T) != 4 )
               && ( sizeof(T) != 8 )
             , const T >::type& val )
{
  T return_val;
  // This is a way to (hopefully) avoid dead lock in a warp
#if defined( KOKKOS_ENABLE_RFO_PREFETCH )
  _mm_prefetch( (const char*) dest, _MM_HINT_ET0 );
#endif

  int done = 0;
  unsigned int active = KOKKOS_IMPL_CUDA_BALLOT(1);
  unsigned int done_active = 0;
  while (active!=done_active) {
    if(!done) {
      if( Impl::lock_address_cuda_space( (void*) dest ) ) {
        return_val = *dest;
        *dest = val;
        Impl::unlock_address_cuda_space( (void*) dest );
        done = 1;
      }
    }
    done_active = KOKKOS_IMPL_CUDA_BALLOT(done);
  }
  return return_val;
}