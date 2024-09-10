static GFINLINE void my_large_gf_free(void *ptr) {
	if (ptr) VirtualFree(ptr, 0, MEM_RELEASE);
}