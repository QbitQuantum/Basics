  void prefetch(void const* pointer)
  {
#ifdef BOOST_SIMD_ARCH_X86
    #ifdef __GNUC__
      __builtin_prefetch(pointer, 0, 0);
    #elif defined( BOOST_SIMD_HAS_SSE_SUPPORT )
      _mm_prefetch( static_cast<char const *>(pointer), Strategy);
    #endif
#endif
  }