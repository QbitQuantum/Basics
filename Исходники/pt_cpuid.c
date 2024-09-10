extern void pt_cpuid(uint32_t leaf, uint32_t *eax, uint32_t *ebx,
		     uint32_t *ecx, uint32_t *edx)
{
	int cpu_info[4];

	__cpuid(cpu_info, leaf);
	*eax = cpu_info[0];
	*ebx = cpu_info[1];
	*ecx = cpu_info[2];
	*edx = cpu_info[3];
}