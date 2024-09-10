static void* zend_mm_mem_alloc(zend_mm_storage *storage, size_t size, size_t alignment) {

	if (EXPECTED(size == PHPDBG_SIGSAFE_MEM_SIZE && !PHPDBG_G(sigsafe_mem).allocated)) {
		PHPDBG_G(sigsafe_mem).allocated = 1;
		return PHPDBG_G(sigsafe_mem).mem;
	}

	write(PHPDBG_G(io)[PHPDBG_STDERR].fd, ZEND_STRL("Tried to allocate more than " EXP_STR(PHPDBG_SIGSAFE_MEM_SIZE) " bytes from stack memory in signal handler ... bailing out of signal handler\n"));

	if (*EG(bailout)) {
		LONGJMP(*EG(bailout), FAILURE);
	}

	write(PHPDBG_G(io)[PHPDBG_STDERR].fd, ZEND_STRL("Bailed out without a bailout address in signal handler!\n"));

	return NULL;
}