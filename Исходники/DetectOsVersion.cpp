/*
 * Determine the *real* Windows version
 */
bool get_real_os_version(unsigned int *const major, unsigned int *const minor, unsigned int *const spack, bool *const pbOverride)
{
	static const DWORD MAX_VALUE = 1024;

	*major = *minor = *spack = 0;
	*pbOverride = false;
	
	//Initialize local variables
	OSVERSIONINFOEXW osvi;
	memset(&osvi, 0, sizeof(OSVERSIONINFOEXW));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);

	//Try GetVersionEx() first
	if(GetVersionExW((LPOSVERSIONINFOW)&osvi) == FALSE)
	{
		if(g_bStdUtilsVerbose)
		{
			MessageBox(0, T("GetVersionEx() has failed, cannot detect Windows version!"), T("StdUtils::get_real_os_version"), MB_ICONERROR|MB_TOPMOST);
		}
		return false;
	}

	//Make sure we are running on NT
	if(osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		*major = osvi.dwMajorVersion;
		*minor = osvi.dwMinorVersion;
		*spack = osvi.wServicePackMajor;
	}
	else
	{
		//Workaround for Windows 9x comaptibility mode
		if(verify_os_version(4, 0, 0))
		{
			*pbOverride = true;
			*major = 4;
		}
		else
		{
			//Really not running on Windows NT
			return false;
		}
	}

	//Determine the real *major* version first
	for(DWORD nextMajor = (*major) + 1; nextMajor <= MAX_VALUE; nextMajor++)
	{
		if(verify_os_version(nextMajor, 0, 0))
		{
			*major = nextMajor;
			*minor = *spack = 0;
			*pbOverride = true;
			continue;
		}
		break;
	}

	//Now also determine the real *minor* version
	for(DWORD nextMinor = (*minor) + 1; nextMinor <= MAX_VALUE; nextMinor++)
	{
		if(verify_os_version((*major), nextMinor, 0))
		{
			*minor = nextMinor;
			*spack = 0;
			*pbOverride = true;
			continue;
		}
		break;
	}

	//Finally determine the real *servicepack* version
	for(WORD nextSpack = (*spack) + 1; nextSpack <= MAX_VALUE; nextSpack++)
	{
		if(verify_os_version((*major), (*minor), nextSpack))
		{
			*spack = nextSpack;
			*pbOverride = true;
			continue;
		}
		break;
	}

	//Workaround for the mess that is sometimes referred to as "Windows 10"
	if(((*major) > 6) || (((*major) == 6) && ((*minor) >= 2)))
	{
		DWORD kernel32_version[2];
		if(read_file_version(T("kernel32"), &kernel32_version[0], &kernel32_version[1]))
		{
			const DWORD kernel32_major = (kernel32_version[0] & DWORD(0xFFFF0000)) >> 0x10;
			const DWORD kernel32_minor = (kernel32_version[0] & DWORD(0x0000FFFF)) >> 0x00;
			if((kernel32_major > (*major)) || ((kernel32_major == (*major)) && (kernel32_minor > (*minor))))
			{
				*major = kernel32_major;
				*minor = kernel32_minor;
				*spack = 0;
				*pbOverride = true;
			}
		}
	}