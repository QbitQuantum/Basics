static inline void get_cpuid2(int *array, int info_type, int ecx)
{
#if defined(_MSC_VER)
    __cpuidex(array, info_type, ecx);
#else
    __cpuid_count(info_type, ecx, array[0], array[1], array[2], array[3]);
#endif
}