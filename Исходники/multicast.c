int php_if_index_to_addr4(unsigned if_index, php_socket *php_sock, struct in_addr *out_addr)
{
	MIB_IPADDRTABLE *addr_table;
    ULONG size;
    DWORD retval;
	DWORD i;

	(void) php_sock; /* not necessary */

	if (if_index == 0) {
		out_addr->s_addr = INADDR_ANY;
		return SUCCESS;
	}

	size = 4 * (sizeof *addr_table);
	addr_table = emalloc(size);
retry:
	retval = GetIpAddrTable(addr_table, &size, 0);
	if (retval == ERROR_INSUFFICIENT_BUFFER) {
		efree(addr_table);
		addr_table = emalloc(size);
		goto retry;
	}
	if (retval != NO_ERROR) {
		php_error_docref(NULL, E_WARNING,
			"GetIpAddrTable failed with error %lu", retval);
		return FAILURE;
	}
	for (i = 0; i < addr_table->dwNumEntries; i++) {
		MIB_IPADDRROW r = addr_table->table[i];
		if (r.dwIndex == if_index) {
			out_addr->s_addr = r.dwAddr;
			return SUCCESS;
		}
	}
	php_error_docref(NULL, E_WARNING,
		"No interface with index %u was found", if_index);
	return FAILURE;
}