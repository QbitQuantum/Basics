static PMIB_IFTABLE win32_get_devices()
{
	PMIB_IFTABLE if_table;
	PMIB_IFTABLE tmp;
	unsigned long dwSize = 0;

	// Allocate memory for pointers
	if_table = sg_malloc(sizeof(MIB_IFTABLE));
	if(if_table == NULL) {
		return NULL;
	}

	// Get necessary size for the buffer
	if(GetIfTable(if_table, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER) {
		tmp = sg_realloc(if_table, dwSize);
		if(tmp == NULL) {
			free(if_table);
			return NULL;
		}
		if_table = tmp;
	}

	// Get the data
	if(GetIfTable(if_table, &dwSize, 0) != NO_ERROR) {
		free(if_table);
		return NULL;
	}
	return if_table;
}