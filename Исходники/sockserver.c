void dtcmr_free(int fd)
{
	if (judgefd(fd, 2)) {
		return ;
	}
	dtcmr_shotdown(fd, FREE_SERVER);
	dtcmr_shotdown(fd, FREE_CLINT);

	freeresource(fd);
	return ;
}