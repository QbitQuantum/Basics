int
isc_win32os_versioncheck(unsigned int major, unsigned int minor,
			 unsigned int spmajor, unsigned int spminor)
{
	OSVERSIONINFOEX osVer;
	DWORD typeMask;
	ULONGLONG conditionMask;

	memset(&osVer, 0, sizeof(OSVERSIONINFOEX));
	osVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	typeMask = 0;
	conditionMask = 0;

	/* Optimistic: likely greater */
	osVer.dwMajorVersion = major;
	typeMask |= VER_MAJORVERSION;
	conditionMask = VerSetConditionMask(conditionMask,
					    VER_MAJORVERSION,
					    VER_GREATER);
	osVer.dwMinorVersion = minor;
	typeMask |= VER_MINORVERSION;
	conditionMask = VerSetConditionMask(conditionMask,
					    VER_MINORVERSION,
					    VER_GREATER);
	osVer.wServicePackMajor = spmajor;
	typeMask |= VER_SERVICEPACKMAJOR;
	conditionMask = VerSetConditionMask(conditionMask,
					    VER_SERVICEPACKMAJOR,
					    VER_GREATER);
	osVer.wServicePackMinor = spminor;
	typeMask |= VER_SERVICEPACKMINOR;
	conditionMask = VerSetConditionMask(conditionMask,
					    VER_SERVICEPACKMINOR,
					    VER_GREATER);
	if (VerifyVersionInfo(&osVer, typeMask, conditionMask))
		return (1);

	/* Failed: retry with equal */
	conditionMask = 0;
	conditionMask = VerSetConditionMask(conditionMask,
					    VER_MAJORVERSION,
					    VER_EQUAL);
	conditionMask = VerSetConditionMask(conditionMask,
					    VER_MINORVERSION,
					    VER_EQUAL);
	conditionMask = VerSetConditionMask(conditionMask,
					    VER_SERVICEPACKMAJOR,
					    VER_EQUAL);
	conditionMask = VerSetConditionMask(conditionMask,
					    VER_SERVICEPACKMINOR,
					    VER_EQUAL);
	if (VerifyVersionInfo(&osVer, typeMask, conditionMask))
		return (0);
	else
		return (-1);
}