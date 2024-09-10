void cpuID(unsigned i, int regs[4]) {
#ifdef _WIN32
    __cpuid((int *)regs, (int)i);

#else
    asm volatile
            ("cpuid" : "=a" (regs[0]), "=b" (regs[1]), "=c" (regs[2]), "=d" (regs[3])
        : "a" (i), "c" (0));
    // ECX is set to zero for CPUID function 4
#endif
}