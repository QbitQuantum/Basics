	long long unsigned int getFreePhysicalMemory()
	{
		#ifdef _WIN32
			MEMORYSTATUSEX status;
			status.dwLength = sizeof(status);
			GlobalMemoryStatusEx(&status);
			return status.ullTotalPhys;
		#elif __APPLE__
			int mib[2]; 
			uint64_t physical_memory; 
			size_t length; 
			// Get the Physical memory size 
			mib[0] = CTL_HW; 
			mib[1] = HW_USERMEM; // HW_MEMSIZE -> physical memory 
			length = sizeof(uint64_t); 
			sysctl(mib, 2, &physical_memory, &length, NULL, 0); 
			return physical_memory;
		#elif __GNUC__
			return get_avphys_pages() * getpagesize();
		#endif
	}