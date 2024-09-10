static
unsigned					/* type matching if_nametoindex() */
_pgm_getadaptersaddresses_nametoindex (
	const sa_family_t	iffamily,
	const char*		ifname
        )
{
	pgm_return_val_if_fail (NULL != ifname, 0);

	ULONG ifIndex;
	DWORD dwSize = DEFAULT_BUFFER_SIZE, dwRet;
	IP_ADAPTER_ADDRESSES *pAdapterAddresses = NULL, *adapter;
	char szAdapterName[IF_NAMESIZE];

/* first see if GetAdapterIndex is working,
 */
	pgm_strncpy_s (szAdapterName, sizeof (szAdapterName), ifname, _TRUNCATE);
	dwRet = GetAdapterIndex ((LPWSTR)szAdapterName, &ifIndex);
	if (NO_ERROR == dwRet)
		return ifIndex;

/* fallback to finding index via iterating adapter list */

/* loop to handle interfaces coming online causing a buffer overflow
 * between first call to list buffer length and second call to enumerate.
 */
	for (unsigned i = MAX_TRIES; i; i--)
	{
		pAdapterAddresses = (IP_ADAPTER_ADDRESSES*)_pgm_heap_alloc (dwSize);
		dwRet = GetAdaptersAddresses (AF_UNSPEC,
						GAA_FLAG_SKIP_ANYCAST |
						GAA_FLAG_SKIP_DNS_SERVER |
						GAA_FLAG_SKIP_FRIENDLY_NAME |
						GAA_FLAG_SKIP_MULTICAST,
						NULL,
						pAdapterAddresses,
						&dwSize);
		if (ERROR_BUFFER_OVERFLOW == dwRet) {
			_pgm_heap_free (pAdapterAddresses);
			pAdapterAddresses = NULL;
		} else {
			break;
		}
	}

	switch (dwRet) {
	case ERROR_SUCCESS:
		break;
	case ERROR_BUFFER_OVERFLOW:
		pgm_warn (_("GetAdaptersAddresses repeatedly failed with ERROR_BUFFER_OVERFLOW"));
		if (pAdapterAddresses)
			_pgm_heap_free (pAdapterAddresses);
		return 0;
	default:
		pgm_warn (_("GetAdaptersAddresses failed"));
		if (pAdapterAddresses)
			_pgm_heap_free (pAdapterAddresses);
		return 0;
	}

	for (adapter = pAdapterAddresses;
		adapter;
		adapter = adapter->Next)
	{
		if (0 == strcmp (szAdapterName, adapter->AdapterName)) {
			ifIndex = AF_INET6 == iffamily ? adapter->Ipv6IfIndex : adapter->IfIndex;
			_pgm_heap_free (pAdapterAddresses);
			return ifIndex;
		}
	}

	if (pAdapterAddresses)
		_pgm_heap_free (pAdapterAddresses);
	return 0;
}