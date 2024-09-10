 void fe_hw_x86_cpuidex(uint32_t leaf, uint32_t subleaf, 
                        uint32_t *eax, uint32_t *ebx, 
                        uint32_t *ecx, uint32_t *edx) {
 #if (defined(__GNUC__) || defined(__clang__))
     __cpuid_count(leaf, subleaf, eax, ebx, ecx, edx);
 #elif defined(_MSC_VER)
     int regs[4];
     __cpuidex(regs, leaf, subleaf);
     *eax = regs[0];
     *ebx = regs[1];
     *ecx = regs[2];
     *edx = regs[3];
 #else
 #error "No cpuid intrinsic for this target !"
 #endif
 }