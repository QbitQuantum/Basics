  inline void cpuidex(register_type pRegisters[4], int function, int subfunction) {
#if defined(BOOST_SIMD_CPUID_HEADER)
    __cpuid_count ( function, subfunction
                  , pRegisters[eax], pRegisters[ebx], pRegisters[ecx], pRegisters[edx]
                  );
#else
  __cpuidex(pRegisters, function, subfunction);
#endif
  }