void *malloc(size_t size) {
	LOG("someone called malloc()\n");
	return shalloc(size);
}