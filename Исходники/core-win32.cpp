SAMPGDK_EXPORT void *SAMPGDK_CALL sampgdk_get_plugin_handle(void *symbol) {
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery(symbol, &mbi, sizeof(mbi));
	return (void*)mbi.AllocationBase;
}