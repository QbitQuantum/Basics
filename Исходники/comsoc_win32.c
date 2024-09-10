int win32_fd_isset(int fd, fd_set *set)
{
	return __WSAFDIsSet(fd, set);
}