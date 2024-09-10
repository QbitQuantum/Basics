void
ethr_x86_cpuid__(int *eax, int *ebx, int *ecx, int *edx)
{
    int CPUInfo[4];

    __cpuid(CPUInfo, *eax);

    *eax = CPUInfo[0];
    *ebx = CPUInfo[1];
    *ecx = CPUInfo[2];
    *edx = CPUInfo[3];
}