int CPUCount( int &logicalNum, int &physicalNum ) {
	int statusFlag;
	SYSTEM_INFO info;

	physicalNum = 1;
	logicalNum = 1;
	statusFlag = HT_NOT_CAPABLE;

	info.dwNumberOfProcessors = 0;
	GetSystemInfo (&info);

	// Number of physical processors in a non-Intel system
	// or in a 32-bit Intel system with Hyper-Threading technology disabled
	physicalNum = info.dwNumberOfProcessors;

	unsigned char HT_Enabled = 0;

	logicalNum = LogicalProcPerPhysicalProc();

	if ( logicalNum >= 1 ) {	// > 1 doesn't mean HT is enabled in the BIOS
		HANDLE hCurrentProcessHandle;
		DWORD  dwProcessAffinity;
		DWORD  dwSystemAffinity;
		DWORD  dwAffinityMask;

		// Calculate the appropriate  shifts and mask based on the
		// number of logical processors.

		unsigned char i = 1, PHY_ID_MASK  = 0xFF, PHY_ID_SHIFT = 0;

		while( i < logicalNum ) {
			i *= 2;
			PHY_ID_MASK  <<= 1;
			PHY_ID_SHIFT++;
		}

		hCurrentProcessHandle = GetCurrentProcess();
		GetProcessAffinityMask( hCurrentProcessHandle, &dwProcessAffinity, &dwSystemAffinity );

		// Check if available process affinity mask is equal to the
		// available system affinity mask
		if ( dwProcessAffinity != dwSystemAffinity ) {
			statusFlag = HT_CANNOT_DETECT;
			physicalNum = -1;
			return statusFlag;
		}

		dwAffinityMask = 1;
		while ( dwAffinityMask != 0 && dwAffinityMask <= dwProcessAffinity ) {
			// Check if this CPU is available
			if ( dwAffinityMask & dwProcessAffinity ) {
				if ( SetProcessAffinityMask( hCurrentProcessHandle, dwAffinityMask ) ) {
					unsigned char APIC_ID, LOG_ID, PHY_ID;

					Sleep( 0 ); // Give OS time to switch CPU

					APIC_ID = GetAPIC_ID();
					LOG_ID  = APIC_ID & ~PHY_ID_MASK;
					PHY_ID  = APIC_ID >> PHY_ID_SHIFT;

					if ( LOG_ID != 0 ) {
						HT_Enabled = 1;
					}
				}
			}
			dwAffinityMask = dwAffinityMask << 1;
		}

		// Reset the processor affinity
		SetProcessAffinityMask( hCurrentProcessHandle, dwProcessAffinity );

		if ( logicalNum == 1 ) {  // Normal P4 : HT is disabled in hardware
			statusFlag = HT_DISABLED;
		} else {
			if ( HT_Enabled ) {
				// Total physical processors in a Hyper-Threading enabled system.
				physicalNum /= logicalNum;
				statusFlag = HT_ENABLED;
			} else {
				statusFlag = HT_SUPPORTED_NOT_ENABLED;
			}
		}
	}