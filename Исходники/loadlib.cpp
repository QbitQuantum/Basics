	RKT_API Proc getProcAddress(void* moduleHandle, const char* procName)
	{
		return reinterpret_cast<Proc>(GetProcAddress((HMODULE)moduleHandle, procName));
	}