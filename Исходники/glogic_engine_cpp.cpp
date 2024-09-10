void GLogicEngineCPP::LogException(const char * msg, ...)
{
	char buffer[4096];
	va_list args;
	va_start(args, msg);
	strcpy(buffer, "LOGIC EXCEPTION: ");
	VSNPRINTF(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), msg, args);
	buffer[sizeof(buffer) - 1] = 0;
	Log(buffer);
}