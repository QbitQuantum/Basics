internal
void writeFileKeyValue(file_t* file, const char* key, const char* valueFormat, ...)
{
	char value[256];
	char line[512];
	va_list args;
	va_start(args, valueFormat);
	vsnprintf_s(value, sizeof(value), _TRUNCATE, valueFormat, args);
	va_end(args);

	char* write = str_append(line, key);
	*(write++) = '=';
	write = str_append(write, value);
	*(write++) = '\r';
	*(write++) = '\n';
	*(write++) = 0;

	file_write(file, line);
}