// Allocate memory
void* salloc(size_t len)
{
#ifdef SENSITIVE_NON_PAGED
	// Allocate memory on a page boundary
#ifndef _WIN32
	void* ptr = (void*) valloc(len);
#else
	pointer r = (pointer) VirtualAlloc(NULL, n * sizeof(T), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#endif

	if (ptr == NULL)
	{
		ERROR_MSG("Out of memory");

		return NULL;
	}

	// Lock the memory so it doesn't get swapped out
#ifndef _WIN32
	if (mlock((const void*) ptr, len) != 0)
#else
	if (VirtualLock((const void*) r, n * sizeof(T)) == 0)
#endif
	{
		ERROR_MSG("Could not allocate non-paged memory for secure storage");

		// Hmmm... best to not return any allocated space in this case
#ifndef _WIN32
		free(ptr);
#else
		VirtualFree((const void*) pre, MEM_RELEASE);
#endif

		return NULL;
	}

	// Register the memory in the secure memory registry
	SecureMemoryRegistry::i()->add(ptr, len);

	return ptr;
#else
	void* ptr = (void*) malloc(len);

	if (ptr == NULL)
	{
		ERROR_MSG("Out of memory");

		return NULL;
	}

	// Register the memory in the secure memory registry
	SecureMemoryRegistry::i()->add(ptr, len);

	return ptr;
#endif // SENSITIVE_NON_PAGED
}