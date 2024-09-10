	std::string TimeString::GetTimeString()
	{
		auto t = std::time(nullptr);
		char buffer[1024];
		struct tm newtime;
		localtime_s(&newtime, &t);
		asctime_s(buffer, &newtime);
		return std::string(buffer);
	}