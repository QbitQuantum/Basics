bool	DumpRunner::DumpProcess(Dumper* dumper, DumpLevel level, const char* processName)
{
	bool result = false;

	EnumProcess enumProcess;
	if (enumProcess.open() == true)
	{
		DWORD processId = 0;
		std::string enumProcessName = enumProcess.getFirst();
		while (enumProcessName.empty() == false)
		{
			if (::_stricmp(processName, enumProcessName.c_str()) == 0)
			{
				processId = enumProcess.getProcessID();
				break;
			}

			enumProcessName = enumProcess.getNext();
		}

		enumProcess.close();

		if (processId != 0)
		{
			result = DumpProcess(dumper, level, processId);
		}
	}

	return result;
}