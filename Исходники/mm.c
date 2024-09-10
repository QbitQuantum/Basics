/**
 * mm_init - Initialize the malloc package.
 */
int mm_init(void)
{
	TRACE(">>>Entering mm_init()\n");
	mem_init();

	#ifdef DO_MM_CHECK
		/* initialize the ENTIRE heap provided by memlib to 0x00 */
		memset(mem_heap_lo(), 0, MAX_HEAP);
	#endif

	/*Each element in free_lists starts off as the empty head of a linked list*/
	memset(free_lists, (int)NULL, sizeof(free_lists));

	/* Initialize write-once variables */
	PAGE_SIZE = mem_pagesize();
	ADJUSTED_PAGESIZE = ADJUST_BYTESIZE((PAGE_SIZE*2));

	/* Initially allocate 1 page of memory plus room for
		the prologue and epilogue blocks and free block header */
	if((heap_start = mem_sbrk(ADJUSTED_PAGESIZE + (4 * WSIZE))) == NULL)
		return -1;

	heap_end = mem_heap_hi();

	/* Alignment word */
	PUTW(heap_start, 0x8BADF00D);

	/* Prologue header */
	PUTW(heap_start + (1 * WSIZE), PACK(DSIZE, THISALLOC | PREVALLOC));
	PUTW(heap_start + (2 * WSIZE), PACK(DSIZE, THISALLOC | PREVALLOC));

	/* Epilogue header */
	PUTW(heap_start + ADJUSTED_PAGESIZE + 3	* WSIZE, PACK(0xEA7F00D0, THISALLOC));

	/* Setup initial free block */
	PUTW(heap_start + (3 * WSIZE), PACK(ADJUSTED_PAGESIZE, PREVALLOC));
	PUTW((heap_end - WSIZE + 1) - WSIZE, PACK(ADJUSTED_PAGESIZE, PREVALLOC));
	add_to_list(heap_start + (4 * WSIZE), calc_list_index(ADJUSTED_PAGESIZE));

	RUN_MM_CHECK();
	TRACE("<<<---Leaving mm_init()\n");
	return 0;
}