	void Logs::EMERGENCY_LOG(const char* file, int line, const char* function, const char* format, ...)
	{
		if (!Settings::getInstance()->IsLogEnabled)
			return;

		char buffer[2048];
		memset(buffer, 0x00, sizeof(buffer));
		va_list args;
		va_start (args, format);
#if defined(__unix__)
		vsnprintf(buffer, sizeof(buffer) - 1, format, args);
#else
		_vsnprintf_s(buffer, sizeof(buffer) - 1, format, args);
#endif
		log_EMERGENCY(processLog(file, line, function, buffer));
		va_end(args); 
	}