/*Chech&set the instruction set of CPU*/
void set_CPU_instruction()
{
	unsigned int cpuid_results[4];
	__cpuid(cpuid_results,7);

	if(cpuid_results[1] &(1 << 16))
	{
#define RTE_MACHINE_CPUFLAG_AVX512F //comes from  DPDK ^^	
		log_info("CPU Instruction set:AVX512F");
		return;
	}
	if(cpuid_results[1] & (1 << 5))
	{
#define RTE_MACHINE_CPUFLAG_AVX2
		log_info("CPU Instruction set:AVX2");
		return;
	}
	__cpuid(cpuid_results,1);
	if(cpuid_results[3] & (1 << 25))
		log_info("CPU Instruction set:SSE");
}