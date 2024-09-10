bool MSYS_Compare_And_Swap_Long(long * address, const long oldValToCheckFor, const long newValToWrite)
{
	/* Init vars. */
	bool ret = false;		/* The result of this function. */

#ifdef _MSC_FULL_VER
	/* _InterlockedCompareExchange(long volatile * DESTIONATION, long EXCHANGE, long COMPERAND) */
	if (_InterlockedCompareExchange(address, newValToWrite, oldValToCheckFor) == oldValToCheckFor)
	{
			ret = true;
	}
#endif	/* _MSC_FULL_VER */

	/* Return the result. */
	return ret;
}