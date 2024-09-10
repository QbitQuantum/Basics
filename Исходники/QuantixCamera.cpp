std::string QuantixCamera::createFilePath()
{
	std::string filePathStem = "\\\\epsrv1\\EP\\data\\";
	std::string year;
	std::string month;
	std::string day;

	struct tm localTime;
	__int64 rawTime;
	errno_t err;

	_time64( &rawTime );

	// Obtain coordinated universal time: 
	err = _localtime64_s( &localTime, &rawTime );
	if (err)
	{
		std::cerr << "Invalid Argument to _gmtime64_s." << std::endl;
	}

	year = STI::Utils::valueToString(localTime.tm_year + 1900);
	month = STI::Utils::valueToString(localTime.tm_mon + 1);
	day = STI::Utils::valueToString(localTime.tm_mday);


	return filePathStem + year + "\\" + month + "\\" + day + "\\data\\";
}