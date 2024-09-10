void cpuid(int level, unsigned int* a, unsigned int* b,
           unsigned int* c, unsigned int* d)
{
    unsigned int eax, ebx, ecx, edx;
    
    __cpuid(level, eax, ebx, ecx, edx);

    *a = eax;
    *b = ebx;
    *c = ecx;
    *d = edx;
}