ULONG
route_ip(ULONG remote_ip)
{
	ULONG size, i, bestmetric, result;
	MIB_IPFORWARDTABLE *buf;
	
	// get route table
	
	size = 0;
	if (GetIpForwardTable(NULL, &size, FALSE) != ERROR_INSUFFICIENT_BUFFER)
		return (ULONG)-1;

	buf = (MIB_IPFORWARDTABLE *)malloc(size);
	if (buf == NULL)
		return (ULONG)-1;

	if (GetIpForwardTable(buf, &size, FALSE) != NO_ERROR) {
		free(buf);
		return (ULONG)-1;
	}

	// find optimal route

	bestmetric = (ULONG)-1;
	result = (ULONG)-1;

	for (i = 0; i < buf->dwNumEntries; i++) {
		if ((remote_ip & buf->table[i].dwForwardMask) ==
			(buf->table[i].dwForwardDest & buf->table[i].dwForwardMask)) {

			if (bestmetric == (ULONG)-1 || buf->table[i].dwForwardMetric1 > bestmetric) {
				bestmetric = buf->table[i].dwForwardMetric1;
				result = buf->table[i].dwForwardIfIndex;
			}

		}
	}

	free(buf);
	return result;
}