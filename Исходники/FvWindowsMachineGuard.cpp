bool UpdateSystemInfoP( FvSystemInfo &kSI )
{
	if ( s_pfImportedGetSystemTimes )
	{
		FILETIME kIdleFileTime, kKernelFileTime, kUserFileTime;
		s_pfImportedGetSystemTimes( &kIdleFileTime, &kKernelFileTime, &kUserFileTime );

		FvUInt64 uiIdleTime = *(FvUInt64*)&kIdleFileTime;
		FvUInt64 uiKernelTime = *(FvUInt64*)&kKernelFileTime;
		FvUInt64 uiUserTime = *(FvUInt64*)&kUserFileTime;

		//gCurMaxCPU = (uiKernelTime + uiKserTime) / gCPUCount;
		//td.curCPU = gCurMaxCPU - uiIdleTime / gCPUCount;
	}

	MEMORYSTATUS kMem;
	GlobalMemoryStatus( &kMem );
	kSI.m_kMem.max.update(kMem.dwTotalPhys);
	kSI.m_kMem.val.update(kMem.dwAvailPhys);

	MIB_IPSTATS kIPStats;
	GetIpStatistics( &kIPStats );
	kSI.m_kPackTotOut.update(kIPStats.dwOutRequests);
	kSI.m_kPackDropOut.update(kIPStats.dwOutDiscards);
	kSI.m_kPackTotIn.update(kIPStats.dwInReceives);
	kSI.m_kPackDropIn.update(kIPStats.dwInDiscards);

	return true;
}