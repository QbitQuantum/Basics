/* Create a YAML file describing the image encoded into a null terminated
   string. Caller will own the memory.
   */
char *store_metadata_(struct PmemMemoryInfo *info)
{
	SYSTEM_INFO sys_info;
	struct tm newtime;
	__time32_t aclock;

	char time_buffer[32];
	errno_t errNum;
	char *arch = NULL;

	_time32(&aclock);   // Get time in seconds.
	_gmtime32_s(&newtime, &aclock);   // Convert time to struct tm form.

	// Print local time as a string.
	errNum = asctime_s(time_buffer, 32, &newtime);
	if (errNum) {
		time_buffer[0] = 0;
	}

	// Get basic architecture information (Note that we always write ELF64 core
	// dumps - even on 32 bit platforms).
	ZeroMemory(&sys_info, sizeof(sys_info));
	GetNativeSystemInfo(&sys_info);

	switch (sys_info.wProcessorArchitecture) {
	case PROCESSOR_ARCHITECTURE_AMD64:
		arch = "AMD64";
		break;

	case PROCESSOR_ARCHITECTURE_INTEL:
		arch = "I386";
		break;

	default:
		arch = "Unknown";
	}

	char *buffer = (char *)malloc(1000);
	_snprintf_s(buffer, 1000, _TRUNCATE,
		// A YAML File describing metadata about this image.
		"# PMEM\n"
		"---\n"   // The start of the YAML file.
		"acquisition_tool: 'WinPMEM " PMEM_VERSION "'\n"
		"acquisition_timestamp: %s\n"
		"CR3: %#llx\n"
		"NtBuildNumber: %#llx\n"
		"NtBuildNumberAddr: %#llx\n"
		"KernBase: %#llx\n"
		"Arch: %s\n"
		"...\n",  // This is the end of a YAML file.
		time_buffer,
		info->CR3.QuadPart,
		info->NtBuildNumber.QuadPart,
		info->NtBuildNumberAddr.QuadPart,
		info->KernBase.QuadPart,
		arch
	);
	return buffer;
};