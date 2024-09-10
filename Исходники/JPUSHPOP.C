static void heapwalker(void)
{
	struct heapinfo hi;

	hi.ptr = NULL;
	while (heapwalk(&hi) == _HEAPOK)
		putz++;
}