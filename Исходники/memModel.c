void *memSbrk(int incr)
{
	char *oldBrk = memBrk;
	if ((incr < 0)||((memBrk + incr) > memMaxAddr))
	{
		errno = ENOMEM;
		fprintf_s(stderr,"错误：memSbrk失败，内存空间不足...\n");
		return (void*)-1;
	}
	memBrk += incr;

	return (void*)oldBrk;
}