	std::string ThreadIDString(void) const
	{
		return Poco::format("[%d] ", GetThreadID());
	}