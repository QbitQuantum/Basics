string intToStr(integer value)
{
	char buffer[64];
	_i64toa_s(value, buffer, sizeof(buffer), 10);
	return buffer;
}