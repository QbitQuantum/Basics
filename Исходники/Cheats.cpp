	bool attachProcess(const std::string& sName, bool bBlock)
	{
		do
		{
			std::this_thread::sleep_for(std::chrono::seconds(2));
			unsigned int procID = getPID(sName);

			ProcessName = sName;
			Process = OpenProcess(PROCESS_ALL_ACCESS, false, procID);

		}while (bBlock && Process == NULL);

		return Process != NULL;
	}