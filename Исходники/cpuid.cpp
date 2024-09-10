CPUInfo __stdcall cpuid(int InfoType)
{
	int results[4];
	__cpuid(results, InfoType);

	CPUInfo i;
	i.Part1 = results[0];
	i.Part2 = results[1];
	i.Part3 = results[2];
	i.Part4 = results[3];

	return i;
}