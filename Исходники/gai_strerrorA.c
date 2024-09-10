char *gai_strerrorA(int ecode)
{
	static char buff[GAI_STRERROR_BUFFER_SIZE + 1];
	wcstombs(buff, gai_strerrorW(ecode), GAI_STRERROR_BUFFER_SIZE + 1);
	return buff;
}