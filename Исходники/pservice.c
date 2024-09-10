USHORT MNetServiceControl (
    const CHAR FAR * pszServer,
    const CHAR FAR * pszService,
    CHAR	     wpOpCode,
    CHAR	     wpArg,
    CHAR      FAR ** ppBuffer ) {

    USHORT	     usReturnCode;

    // get a small buffer
    *ppBuffer = MGetBuffer(LITTLE_BUFFER_SIZE);
    if (*ppBuffer == NULL)
    {
	return(ERROR_NOT_ENOUGH_MEMORY);
    }

    usReturnCode = NetServiceControl(pszServer, pszService, wpOpCode, wpArg,
	    *ppBuffer, LITTLE_BUFFER_SIZE);

    // If we're returning an error that's not moredata, free the buffer first

    if (usReturnCode && usReturnCode != ERROR_MORE_DATA &&
	usReturnCode != NERR_BufTooSmall) {
	    NetApiBufferFree(*ppBuffer);
    }

    return (usReturnCode);

}