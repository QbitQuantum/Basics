  FlushToZero::FlushToZero()
  {
#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
    _controlfp_s(&previous_state, _MCW_DN, _DN_FLUSH);
#elif defined(__APPLE__)
    fegetenv(&previous_state);
    fesetenv(FE_DFL_DISABLE_SSE_DENORMS_ENV);
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
    previous_state = _mm_getcsr() & _MM_DENORMALS_ZERO_MASK;
    _mm_setcsr(_mm_getcsr() | (_MM_DENORMALS_ZERO_ON));
#endif
  }