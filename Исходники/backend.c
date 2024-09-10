// Get CPU usage and return as a value from 0 to 255
static byte getCPUUsage()
{
	static unsigned long long last_idleTime;
	static unsigned long long last_kernelTime;
	static unsigned long long last_userTime;

	unsigned long long idleTime;
	unsigned long long kernelTime;
	unsigned long long userTime;
	bool res = GetSystemTimes((LPFILETIME)&idleTime, (LPFILETIME)&kernelTime, (LPFILETIME)&userTime);
	UNREFERENCED_PARAMETER(res);

	unsigned long long idl = idleTime - last_idleTime;
	unsigned long long ker = kernelTime - last_kernelTime;
	unsigned long long usr = userTime - last_userTime;

	unsigned long long sys = ker + usr;

	last_idleTime	= idleTime;
	last_kernelTime	= kernelTime;
	last_userTime	= userTime;

	if(sys == 0)
		return 0;

	return (byte)((sys - idl) * 255 / sys);
}