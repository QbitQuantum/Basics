GenericRoutingTable::ROUTING_TABLE GenericRoutingTable::detail::getRoutingTableWin32 ()
{
	ROUTING_TABLE retTable;

#ifdef WIN32

	PMIB_IPFORWARDTABLE table	= NULL;
	ULONG				size	= 0;
	DWORD				ret		= 0;
	BOOL				order	= TRUE;

	do {
		if (size > 0) {
			if (table != NULL) free (table);
			table = (PMIB_IPFORWARDTABLE) malloc (size);
		}

		ret = GetIpForwardTable (table, &size, order);
	
	} while (ret == ERROR_INSUFFICIENT_BUFFER);

	if (ret != NO_ERROR) return retTable;
	if (table == NULL)	 return retTable;
	
	for (DWORD i = 0; i<table->dwNumEntries; i++) {

		MIB_IPFORWARDROW item = table->table[i];
		IP_ADDR			 addr (item.dwForwardDest);
		IP_ADDR			 mask (item.dwForwardMask); 

		retTable.push_back (ROUTING_ENTRY (addr, mask));
	}

	free (table);

#endif // WIN32

	return retTable;
}