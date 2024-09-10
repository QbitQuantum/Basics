KOKKOS_FORCEINLINE_FUNCTION
void memory_fence()
{
#if defined( KOKKOS_ATOMICS_USE_CUDA )
  __threadfence();
#elif defined( KOKKOS_ATOMICS_USE_GCC ) || \
      ( defined( KOKKOS_COMPILER_NVCC ) && defined( KOKKOS_ATOMICS_USE_INTEL ) )
  __sync_synchronize();
#elif defined( KOKKOS_ATOMICS_USE_INTEL )
  _mm_mfence();
#elif defined( KOKKOS_ATOMICS_USE_OMP31 )
  #pragma omp flush

#else
 #error "Error: memory_fence() not defined"
#endif
}