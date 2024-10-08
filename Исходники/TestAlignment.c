int TestAlignment(int argc, char* argv[])
{
	void* ptr;
	size_t alignment;
	size_t offset;

	/* Alignment should be 2^N where N is a positive integer */

	alignment = 16;
	offset = 5;

	/* _aligned_malloc */

	ptr = _aligned_malloc(100, alignment);

	if (ptr == NULL)
	{
		printf("Error allocating aligned memory.\n");
		return -1;
	}

	if (((size_t) ptr % alignment) != 0)
	{
		printf("This pointer, %d, is not aligned on %d\n", ptr, alignment);
		return -1;
	}

	/* _aligned_realloc */
	
	ptr = _aligned_realloc(ptr, 200, alignment);
	
	if (((size_t) ptr % alignment) != 0)
	{
		printf("This pointer, %d, is not aligned on %d\n", ptr, alignment);
		return -1;
	}
	
	_aligned_free(ptr);

	/* _aligned_offset_malloc */

	ptr = _aligned_offset_malloc(200, alignment, offset);

	if (ptr == NULL)
	{
		printf("Error reallocating aligned offset memory.");
		return -1;
	}

	if (((((size_t) ptr) + offset) % alignment) != 0)
	{
		printf("This pointer, %d, does not satisfy offset %d and alignment %d\n", ptr, offset, alignment);
		return -1;
	}

	/* _aligned_offset_realloc */

	ptr = _aligned_offset_realloc(ptr, 200, alignment, offset);
	
	if (ptr == NULL)
	{
		printf("Error reallocating aligned offset memory.");
		return -1;
	}

	if (((((size_t) ptr) + offset) % alignment) != 0)
	{
		printf("This pointer, %d, does not satisfy offset %d and alignment %d\n", ptr, offset, alignment);
		return -1;
	}

	/* _aligned_free works for both _aligned_malloc and _aligned_offset_malloc. free() should not be used. */
	_aligned_free(ptr);

	return 0;
}