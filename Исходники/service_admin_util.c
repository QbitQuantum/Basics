AXIS2_EXTERN axis2_char_t* AXIS2_CALL
service_admin_util_get_uname(axutil_env_t *env,char mode)
{
	char *unameval;
	char tmp_uname[256];
#ifdef WIN32
	DWORD dwBuild=0;
	DWORD dwVersion = GetVersion();
	DWORD dwWindowsMajorVersion =  (DWORD)(LOBYTE(LOWORD(dwVersion)));
	DWORD dwWindowsMinorVersion =  (DWORD)(HIBYTE(LOWORD(dwVersion)));
	DWORD dwSize = MAX_COMPUTERNAME_LENGTH + 1;
	TCHAR ComputerName[MAX_COMPUTERNAME_LENGTH + 1];
	SYSTEM_INFO SysInfo;

	GetComputerName(ComputerName, &dwSize);
	GetSystemInfo(&SysInfo);

	if (mode == 's') {
		if (dwVersion < 0x80000000) {
			unameval = "Windows NT";
		} else {
			unameval = "Windows 9x";
		}
	} else if (mode == 'r') {
		snprintf(tmp_uname, sizeof(tmp_uname), "%d.%d", dwWindowsMajorVersion, dwWindowsMinorVersion);
		unameval = tmp_uname;
	} else if (mode == 'n') {
		unameval = ComputerName;
	} else if (mode == 'v') {
		dwBuild = (DWORD)(HIWORD(dwVersion));
		snprintf(tmp_uname, sizeof(tmp_uname), "build %d", dwBuild);
		unameval = tmp_uname;
	} else if (mode == 'm') {
		switch (SysInfo.wProcessorArchitecture) {
			case PROCESSOR_ARCHITECTURE_INTEL :
				snprintf(tmp_uname, sizeof(tmp_uname), "i%d", SysInfo.dwProcessorType);
				unameval = tmp_uname;
				break;
			case PROCESSOR_ARCHITECTURE_MIPS :
				snprintf(tmp_uname, sizeof(tmp_uname), "MIPS R%d000", SysInfo.wProcessorLevel);
				unameval = tmp_uname;
				break;
			case PROCESSOR_ARCHITECTURE_ALPHA :
				snprintf(tmp_uname, sizeof(tmp_uname), "Alpha %d", SysInfo.wProcessorLevel);
				unameval = tmp_uname;
				break;
			case PROCESSOR_ARCHITECTURE_PPC :
				snprintf(tmp_uname, sizeof(tmp_uname), "PPC 6%02d", SysInfo.wProcessorLevel);
				unameval = tmp_uname;
				break;
			case PROCESSOR_ARCHITECTURE_IA64 :
				unameval = "IA64";
				break;
#if defined(PROCESSOR_ARCHITECTURE_IA32_ON_WIN64)
			case PROCESSOR_ARCHITECTURE_IA32_ON_WIN64 :
				unameval = "IA32";
				break;
#endif
#if defined(PROCESSOR_ARCHITECTURE_AMD64)
			case PROCESSOR_ARCHITECTURE_AMD64 :
				unameval = "AMD64";
				break;
#endif
			case PROCESSOR_ARCHITECTURE_UNKNOWN :
			default :
				unameval = "Unknown";
				break;
		}
	} else { /* assume mode == 'a' */
		/* Get build numbers for Windows NT or Win95 */
		if (dwVersion < 0x80000000){
			dwBuild = (DWORD)(HIWORD(dwVersion));
			snprintf(tmp_uname, sizeof(tmp_uname), "%s %d.%d build %d",
					 "Windows NT", 
					 dwWindowsMajorVersion, dwWindowsMinorVersion, dwBuild);
		} else {
			snprintf(tmp_uname, sizeof(tmp_uname), "%s %s %d.%d",
					 "Windows 9x",
					 dwWindowsMajorVersion, dwWindowsMinorVersion);
		}
		unameval = tmp_uname;
	}
#else
#ifdef HAVE_SYS_UTSNAME_H
	struct utsname buf;
	if (uname((struct utsname *)&buf) == -1) {
		unameval = "Linux";
	} else {
		if (mode == 's') {
			unameval = buf.sysname;
		} else if (mode == 'r') {
			unameval = buf.release;
		} else if (mode == 'n') {
			unameval = buf.nodename;
		} else if (mode == 'v') {
			unameval = buf.version;
		} else if (mode == 'm') {
			unameval = buf.machine;
		} else { /* assume mode == 'a' */
			snprintf(tmp_uname, sizeof(tmp_uname), "%s %s %s %s %s",
					 buf.sysname, buf.nodename, buf.release, buf.version,
					 buf.machine);
			unameval = tmp_uname;
		}

	}
#endif
#endif
	return axutil_strdup(env,unameval);

}