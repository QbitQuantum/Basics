int _declspec(noinline) _stdcall xts_aes_ni_available()
{
	int           CPUInfo[4], res = 0;
	__m128i       enc;
#ifdef _M_IX86
	unsigned char fpustate[32];
#endif

	// check for AES-NI support via CPUID.01H:ECX.AES[bit 25]
	__cpuid(CPUInfo, 1);
	if ( CPUInfo[2] & 0x02000000 ) return 1;

	// Special workaround for AES-NI on Hyper-V server and virtual machines
	if ( (CPUInfo[2] & 0x80000000) == 0 ) return 0;
	__cpuid(CPUInfo, 0x40000000);
	if ( CPUInfo[1] != 'rciM' || CPUInfo[2] != 'foso' || CPUInfo[3] != 'vH t' ) return 0;

#ifdef _M_IX86
	if (save_fpu_state(fpustate) >= 0)
	{
#endif
		__try {
			enc = _mm_aesenc_si128(_mm_set_epi32(0,1,2,3), _mm_set_epi32(4,5,6,7));
			res = enc.m128i_u64[0] == 0x5f77774d4b7b7b54 && enc.m128i_u64[1] == 0x63636367427c7c58;
		}
		__except(EXCEPTION_EXECUTE_HANDLER) {
			res = 0;
		}
#ifdef _M_IX86
		load_fpu_state(fpustate);
	}