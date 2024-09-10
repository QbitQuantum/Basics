void* inmem_malloc(size_t size)
{
	void *ptr = malloc(size);
	if (ptr == NULL)
	{
		printf("inmem_malloc failed!\n");
		exit(1);
	}
	VirtualLock(ptr, size);
	return ptr;
}