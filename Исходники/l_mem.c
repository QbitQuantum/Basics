//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
int MemorySize(void *ptr)
{
#if defined(WIN32) || defined(_WIN32)
	#ifdef __WATCOMC__
		//Intel 32 bits memory addressing, 16 bytes aligned
	return (_msize(ptr) + 15) >> 4 << 4;
	#else
	return _msize(ptr);
	#endif
#else
	return 0;
#endif
} //end of the function MemorySize