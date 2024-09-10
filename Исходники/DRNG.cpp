DRNG::DRNG(void)
{
	int info[4];

	if (_drng_support != DRNG_SUPPORT_UNKNOWN) return;
	
	_drng_support= DRNG_SUPPORT_NONE;

	// Check our feature support

	__cpuid(info, 0);

	if ( memcmp(&(info[1]), "Genu", 4) ||
		memcmp(&(info[3]), "ineI", 4) ||
		memcmp(&(info[2]), "ntel", 4) ) return;

	__cpuidex(info, 1, 0);

	if ( ((UINT) info[2]) & (1<<30) ) _drng_support|= DRNG_SUPPORT_RDRAND;

#ifdef COMPILER_HAS_RDSEED_SUPPORT
	__cpuidex(info, 7, 0);

	if ( ((UINT) info[1]) & (1<<18) ) _drng_support|= DRNG_SUPPORT_RDSEED;
#endif
}