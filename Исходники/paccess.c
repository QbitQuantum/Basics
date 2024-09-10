USHORT MNetAccessEnum (
    const CHAR	     FAR * pszServer,
    CHAR	     FAR * pszBasePath,
    USHORT	     fsRecursive,
    SHORT	     Level,
    CHAR FAR **      ppBuffer,
    USHORT     FAR * pcEntriesRead ) {

    USHORT				       usReturnCode,
					       cbTotalAvail;
    SEL 				       sel;

    // get a 4K buffer
    *ppBuffer = MGetBuffer(BIG_BUFFER_SIZE);
    if (*ppBuffer == NULL)
    {
	return(ERROR_NOT_ENOUGH_MEMORY);
    }

    usReturnCode = NetAccessEnum(pszServer, pszBasePath, fsRecursive, Level,
	    *ppBuffer, BIG_BUFFER_SIZE, pcEntriesRead, & cbTotalAvail);
		
    // is there more data? if so, allocate a big enough buffer to get it
    if(usReturnCode == ERROR_MORE_DATA || usReturnCode == NERR_BufTooSmall)
    {
	NetApiBufferFree(*ppBuffer);

	if (DEBUGALLOC(FULL_SEG_BUFFER_SIZE, & sel, SEG_NONSHARED))
	{
	    return(ERROR_NOT_ENOUGH_MEMORY);
	}
	*ppBuffer = MAKEP(sel, 0);
	usReturnCode = NetAccessEnum(pszServer, pszBasePath, fsRecursive, Level,
	    *ppBuffer, FULL_SEG_BUFFER_SIZE, pcEntriesRead, & cbTotalAvail);
    }

    // If we're returning an error that's not moredata, or there are no
    // entries to return, free the buffer first

    if ((usReturnCode && usReturnCode != ERROR_MORE_DATA &&
	usReturnCode != NERR_BufTooSmall) || *pcEntriesRead == 0) {
	    NetApiBufferFree(*ppBuffer);
    }

    return (usReturnCode);

}