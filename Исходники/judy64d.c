void vfree (void *what, uint size)
{
	VirtualFree(what, 0, MEM_RELEASE);
}