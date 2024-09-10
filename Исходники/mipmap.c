static void cpuid(int32_t out[4], int32_t x) {
    __cpuidex(out,x,0);
}