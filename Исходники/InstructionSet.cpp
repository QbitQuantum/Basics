	__declspec(dllexport) int __cdecl GetPhysicalProcessorCount()
	{
		ULONG p;
		if (GetNumaHighestNodeNumber(&p))
			return (int)p + 1;
		else
			return 1;
	}