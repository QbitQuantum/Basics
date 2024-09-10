// getCpuid: Rea CPU instruction id
static AMDTResult getCpuid(AMDTUInt32 fn, AMDTInt32 cpuInfo[4])
{
#if ( defined (_WIN32) || defined (_WIN64) )

    __cpuid(cpuInfo, fn);

#else
    // Linux
#if defined(__i386__) && defined(__PIC__)
    /* %ebx may be the PIC register.  */

#define __cpuid(level, a, b, c, d)              \
    __asm__("xchgl\t%%ebx, %1\n\t"             \
            "cpuid\n\t"                 \
            "xchgl\t%%ebx, %1\n\t"              \
            : "=a" (a), "=r" (b), "=c" (c), "=d" (d)    \
            : "0" (level))
#else
#define __cpuid(level, a, b, c, d)          \
    __asm__("cpuid\n\t"                \
            : "=a" (a), "=b" (b), "=c" (c), "=d" (d)    \
            : "0" (level))
#endif

    AMDTUInt32  eax;
    AMDTUInt32  ebx;
    AMDTUInt32  ecx;
    AMDTUInt32  edx;

    /* CPUID Fn0000_0001_EAX Family, Model, Stepping */
    __cpuid(fn, eax, ebx, ecx, edx);

    cpuInfo[0] = eax;
    cpuInfo[1] = ebx;
    cpuInfo[2] = ecx;
    cpuInfo[3] = edx;
#endif

    return AMDT_STATUS_OK;
}