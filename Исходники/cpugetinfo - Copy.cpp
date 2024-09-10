inline static void cpuid (int output[4], int aa, int cc = 0) {	
    __cpuidex(output, aa, cc);
}