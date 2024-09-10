/**
 * Fetches the contents of the fpstate (mxcsr on x86) register.
 *
 * On platforms without support for it just returns 0.
 */
unsigned
util_fpstate_get(void)
{
   unsigned mxcsr = 0;

#if defined(PIPE_ARCH_SSE)
   if (util_cpu_caps.has_sse) {
      mxcsr = _mm_getcsr();
   }
#endif

   return mxcsr;
}