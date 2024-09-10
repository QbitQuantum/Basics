char* getlogin()
{
/*! @todo make this reentrant!*/
	size_t size = sizeof(getlogin_buf);
	*getlogin_buf = 0;
	if (!GetUserNameA(getlogin_buf, (LPDWORD)&size))
		return 0;
	return getlogin_buf;
}