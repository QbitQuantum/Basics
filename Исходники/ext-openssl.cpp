static void *OpenSslMallocFun(size_t size, const char *file, int line) {
	return Malloc(size);
}