void dbt_cpuid(int eax, int ecx, struct cpuid_t *cpuid)
{
	int cpuinfo[4];
	__cpuidex(cpuinfo, eax, ecx);
	cpuid->eax = cpuinfo[0];
	cpuid->ebx = cpuinfo[1];
	cpuid->ecx = cpuinfo[2];
	cpuid->edx = cpuinfo[3];
	/* Mangle cpu feature bits, omit unsupported features  */
	if (eax == 0x01)
	{
		/* Feature information */
		cpuid->edx &= (0
			| FEATURE_FPU
			| FEATURE_VME
			| FEATURE_DE
			| FEATURE_PSE
			| FEATURE_TSC
			| FEATURE_MSR
			| FEATURE_PAE
			| FEATURE_MCE
			| FEATURE_CX8
			| FEATURE_APIC
			//| FEATURE_SEP
			| FEATURE_MTRR
			| FEATURE_PGE
			| FEATURE_MCA
			| FEATURE_CMOV
			| FEATURE_PAT
			| FEATURE_PSE_36
			| FEATURE_PSN
			| FEATURE_CLFSH
			| FEATURE_DS
			| FEATURE_ACPI
			| FEATURE_MMX
			| FEATURE_FXSR
			| FEATURE_SSE
			| FEATURE_SSE2
			| FEATURE_SS
			| FEATURE_HTT
			| FEATURE_TM
			| FEATURE_IA64
			| FEATURE_PBE
			);
		cpuid->ecx &= (0
			| FEATURE_SSE3
			//| FEATURE_PCLMULQDQ
			| FEATURE_DTES64
			| FEATURE_MONITOR
			| FEATURE_DS_CPL
			| FEATURE_VMX
			| FEATURE_SMX
			| FEATURE_EST
			| FEATURE_TM2
			| FEATURE_SSSE3
			| FEATURE_CNXT_ID
			//| FEATURE_FMA
			//| FEATURE_CMPXCHG16B
			| FEATURE_XTPR
			| FEATURE_PDCM
			| FEATURE_PCID
			| FEATURE_DCA
			| FEATURE_SSE41
			| FEATURE_SSE42
			| FEATURE_X2APIC
			| FEATURE_MOVBE
			| FEATURE_POPCNT
			| FEATURE_TSC_DEADLINE
			//| FEATURE_AES
			//| FEATURE_XSAVE
			//| FEATURE_OSXSAVE
			//| FEATURE_AVX
			//| FEATURE_F16C
			//| FEATURE_RDRAND
			| FEATURE_HYPERVISOR
			);
	}
	else if (eax == 0x80000001)
	{
		/* Extended function */
		cpuid->edx &= (0
			| FEATURE_SYSCALL
			| FEATURE_NX
			//| FEATURE_MMXEXT
			//| FEATURE_FXSR_OPT
			| FEATURE_GPAGE
			//| FEATURE_RDTSCP
			| FEATURE_64
			//| FEATURE_3DNOWEXT
			//| FEATURE_3DNOW
			);
		/* AMD extensions */
		cpuid->ecx &= (0
			| FEATURE_LAHF
			//| FEATURE_CMP_LEGACY
			//| FEATURE_SVM
			//| FEATURE_EXTAPIC
			//| FEATURE_CR8_LEGACY
			//| FEATURE_ABM
			//| FEATURE_SSE4A
			//| FEATURE_MISALIGNSSE
			//| FEATURE_3DNOWPREFETCH
			//| FEATURE_OSVW
			//| FEATURE_IBS
			//| FEATURE_XOP
			//| FEATURE_SKINIT
			//| FEATURE_WDT
			//| FEATURE_LWP
			//| FEATURE_FMA4
			//| FEATURE_TCE
			//| FEATURE_NODEID_MSR
			//| FEATURE_TBM
			//| FEATURE_TOPOEXT
			//| FEATURE_PERFCTR_CORE
			//| FEATURE_PERFCTR_NB
			//| FEATURE_BPEXT
			//| FEATURE_PERFCTR_L2
			);
	}
	else if (eax == 0x07)
	{
		/* Structured extended feature flags */
		if (ecx == 0x00)
		{
			cpuid->eax = 0;
			cpuid->ebx &= (0
				//| FEATURE_FSGSBASE
				| FEATURE_TSC_ADJUST
				//| FEATURE_BMI1
				//| FEATURE_HLE
				//| FEATURE_AVX2
				| FEATURE_SMEP
				//| FEATURE_BMI2
				| FEATURE_ERMS
				//| FEATURE_INVPCID
				//| FEATURE_RTM
				//| FEATURE_MPX
				//| FEATURE_AVX512F
				//| FEATURE_RDSEED
				//| FEATURE_ADX
				//| FEATURE_SMAP
				//| FEATURE_CLFLUSHOPT
				//| FEATURE_AVX512PF
				//| FEATURE_AVX512ER
				//| FEATURE_AVX512CD
				);
			cpuid->ecx = 0;
			cpuid->edx = 0;
		}
		else
			cpuid->eax = cpuid->ebx = cpuid->ecx = cpuid->edx = 0;
	}
}