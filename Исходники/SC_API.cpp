int KSC_GetSIMDWidth()
{
	int CPUInfo[4];
	__cpuid(CPUInfo, 1);

	bool hasSSE = (CPUInfo[3] & (1 << 25));
	const unsigned AVXBits = (1 << 27) | (1 << 28);
	bool HasAVX = ((CPUInfo[2] & AVXBits) == AVXBits);

	return HasAVX ? 8 : (hasSSE ? 4 : 1);
}