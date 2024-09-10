static void getSSELevelSupport(int* hasSSE2_out, int* hasSSE3_out)
{
    int nIds = 0;
    int cpuInfo[4] = { 0, 0, 0, 0 };
    int hasSSE2 = FALSE;
    int hasSSE3 = FALSE;

    __cpuid(cpuInfo, 0);
    nIds = cpuInfo[0];

    if (nIds >= 1)
    {
        __cpuid(cpuInfo, 1);
        hasSSE2 = !!(cpuInfo[3] & bit_SSE2);
        hasSSE3 = !!(cpuInfo[2] & bit_SSE3);
    }

    *hasSSE2_out = hasSSE2;
    *hasSSE3_out = hasSSE3;
}