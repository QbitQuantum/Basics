void GetCPUId(DWORD type, DWORD* EAX, DWORD* EBX, DWORD* ECX, DWORD* EDX)
{
	int CPUInfo[4];

	__cpuid(CPUInfo, type);

	*EAX = CPUInfo[0];
	*EBX = CPUInfo[1];
	*ECX = CPUInfo[2];
	*EDX = CPUInfo[3];
}