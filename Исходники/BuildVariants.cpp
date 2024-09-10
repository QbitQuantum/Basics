bool BuildVariants::HostCan64bits()
{
	#if (MPT_ARCH_BITS == 64)
		return true;
	#else
		#if MPT_OS_WINDOWS
			#if (_WIN32_WINNT >= 0x0501)
				BOOL is64 = FALSE;
				if(IsWow64Process(GetCurrentProcess(), &is64) != 0)
				{
					return is64 ? true : false;
				} else
				{
					return false;
				}
			#else
				return false;
			#endif
		#else
			return false;
		#endif
	#endif
}