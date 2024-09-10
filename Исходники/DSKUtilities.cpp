std::string DSKUtilities::format(std::string format, ...) {
	va_list arguments;
	va_start(arguments, format);
	int bufferSize = 200;
	char* buffer = new char[bufferSize];
	vsprintf_s(buffer, bufferSize, format.c_str(), arguments);
	va_end(arguments);
	std::string formatted = std::string(buffer);
	delete[] buffer;
	return formatted;
}