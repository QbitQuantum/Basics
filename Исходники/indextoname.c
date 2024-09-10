PGM_GNUC_INTERNAL
char*
pgm_if_indextoname (
	unsigned int		ifindex,
	char*			ifname
        )
{
#if !defined( _WIN32 )
/* Vista+ implements if_indextoname for IPv6 */
	return if_indextoname (ifindex, ifname);
#else
/* Windows maintains a few different numbers for each interface, the
 * number returned by GetIfEntry has shown to be the same as that 
 * determined by GetAdaptersAddresses and GetAdaptersInfo.
 */
	pgm_return_val_if_fail (NULL != ifname, NULL);

	MIB_IFROW ifRow = { .dwIndex = ifindex };
	const DWORD dwRetval = GetIfEntry (&ifRow);
	if (NO_ERROR != dwRetval)
		return NULL;
	strcpy (ifname, (char*)ifRow.wszName);
	return ifname;
#endif /* _WIN32 */
}