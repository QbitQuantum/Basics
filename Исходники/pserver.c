APIERR MNetServerDiskEnum(
	const TCHAR FAR	 * pszServer,
	UINT		   Level,
	BYTE FAR	** ppbBuffer,
	UINT FAR	 * pcEntriesRead )
{
    DWORD cTotalEntries;
    return (APIERR)NetServerDiskEnum( (TCHAR *)pszServer,
    				  Level,
				  ppbBuffer,
				  MAXPREFERREDLENGTH,
				  (LPDWORD)pcEntriesRead,
				  &cTotalEntries,
				  NULL );

}   // MNetServerDiskEnum