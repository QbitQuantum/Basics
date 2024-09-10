/**
 * Checks the SSE2 feature bit returned by the CPUID instruction
 * @return Does the CPU support SSE2?
 */
bool Zoom::haveSSE2()
{
#ifdef __GNUC__
	unsigned int CPUInfo[4] = {0, 0, 0, 0};
	__get_cpuid(1, CPUInfo, CPUInfo+1, CPUInfo+2, CPUInfo+3);
#elif _WIN32
	int CPUInfo[4];
	__cpuid(CPUInfo, 1);
#else
	unsigned int CPUInfo[4] = {0, 0, 0, 0};
#endif

	return (CPUInfo[3] & 0x04000000) ? true : false;
}