static bool is_sse4_2_supported(void)
{
#if defined(__SSE42__) && (defined(__i386__) || defined(__x86_64__))
	unsigned int eax, ebx, ecx, edx;
#ifdef __APPLE__
	__get_cpuid(1, &eax, &ebx, &ecx, &edx);
#else
	__cpuid(1, eax, ebx, ecx, edx);
#endif
	return ecx & 0x00080000; // SSE4.2
#else
	return false;
#endif
}