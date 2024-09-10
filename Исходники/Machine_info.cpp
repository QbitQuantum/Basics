void MachineInfo::make_info()
{
	//FunctionHooks* FH = new FunctionHooks;
	
	DWORD size;
	size = MAX_COMPUTERNAME_LENGTH + 1;
	
	GetComputerNameA(this->PC_Name, &size); // Wpisanie nazwy komputera

	size = UNLEN + 1;

	GetUserNameA(this->Username, &size); // Wpisanie nazwy u¿ytkownika

	
	/*----------------Wpisanie informacji o maksymalnym taktowaniu CPU--------------------*/
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	size = sysInfo.dwNumberOfProcessors * sizeof(PROCESSOR_POWER_INFORMATION);
	LPBYTE buf = new BYTE[size];
	CallNtPowerInformation(ProcessorInformation, NULL, 0, buf, size);
	PPROCESSOR_POWER_INFORMATION cpuinfo = (PPROCESSOR_POWER_INFORMATION)buf;
	std::string full_cpu_ratio = intToStr(cpuinfo->MaxMhz) + "GHz";
	full_cpu_ratio.erase(3, 1);
	full_cpu_ratio.insert(1, ".");
	memcpy(this->CPU_clock, full_cpu_ratio.c_str(), sizeof(full_cpu_ratio));
	/*------------------------------------------------------------------------------------*/


	/*-----------------------Sprawdzenie wersji systemu Windows---------------------------*/
	if (IsWindows8Point1OrGreater())memcpy(this->OS, "Windows 8.1", sizeof("Windows 8.1"));
	else
	if (IsWindows7OrGreater())memcpy(this->OS, "Windows 7", sizeof("Windows 7"));
	else
	if (IsWindowsVistaOrGreater())memcpy(this->OS, "Windows Vista", sizeof("Windows Vista"));
	else
	if (IsWindowsXPOrGreater())memcpy(this->OS, "Windows XP", sizeof("Windows XP"));
	/*------------------------------------------------------------------------------------*/

}