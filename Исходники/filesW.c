static void my_heapchk()
{
	int heapstatus = _heapchk();
	assert(_HEAPOK == heapstatus);
}