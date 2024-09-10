void	*MIONet_Open (char *pmOpenString)
{
    NetRecord	*myNetRecord;
    char	myNetAddr[256];
    char	myDoc [256];
    int		myPort;

    if (!stMDNetInitialized)
    {
	ABORT_WITH_ERRNO (E_NET_INIT_FAILED);
	// Never reaches here
    }

    // Allocate the NetRecord
    myNetRecord = (NetRecord *) malloc (sizeof (NetRecord));
    if (myNetRecord == NULL) 
    {
	SET_ERRNO (E_INSUFFICIENT_MEMORY);
	return NULL;
    }

    // Initialize the entire record to zeroes
    memset (myNetRecord, 0, sizeof (NetRecord));

    // Allocate the socket
    myNetRecord -> socket = MDIONet_CreateSocket ();
    if (myNetRecord -> socket == NULL) 
    {
	free (myNetRecord);
	return NULL;
    }

    // Allocate the socket address
    myNetRecord -> sockAddr = MDIO_AllocateSockAddr ();
    if (myNetRecord -> sockAddr == NULL)
    {
	free (myNetRecord);
	return NULL;
    }

    // Allocate the buffer
    myNetRecord -> buf = (BYTE *) malloc(BUFFER_SIZE);
    if (myNetRecord -> buf == NULL) 
    {
	MDIONet_CloseSocket (myNetRecord -> socket);
	free (myNetRecord);
	SET_ERRNO (E_INSUFFICIENT_MEMORY);
	return NULL;
    }
    memset (myNetRecord -> buf, 128, BUFFER_SIZE);

    switch (pmOpenString[0])
    {
	case 'C':
	    // Connect to arbitrary port
	    if (MyDoConnect (myNetRecord, pmOpenString + 2, &myPort, 
			     myNetAddr)) 
	    {
		MDIO_sprintf (stLastOpenDescription,
		    "Connect to port %d on %s", &myPort, myNetAddr);
		stLastStreamOpened = myNetRecord;
		return myNetRecord;
	    }
	    break;
	
	case 'A':
	    // Open for accepting a connection on a port
	    if (MyDoOpenForAccept (myNetRecord, pmOpenString + 2, &myPort)) 
	    {
		MDIO_sprintf (stLastOpenDescription,
		    "Accepted connection on port %d", &myPort);
		stLastStreamOpened = myNetRecord;
		return myNetRecord;
	    }
	    break;

	case 'U':
	    // Open a URL for read
	    {
		if (MyGetURLAddressAndDocument (myNetAddr, myDoc, 
					        pmOpenString + 2)) 
		{
		    if (MyDoConnect (myNetRecord, myNetAddr, &myPort, NULL)) 
		    {
			MySendURLGet (myNetRecord, myDoc);
			if (myPort == 80)
			{
			    MDIO_sprintf (stLastOpenDescription,
				"Connect to URL %s", myNetAddr);
			}
			else
			{
			    MDIO_sprintf (stLastOpenDescription,
				"Connect to URL %s (port %d)", myNetAddr, 
				myPort);
			}
			stLastStreamOpened = myNetRecord;
			return myNetRecord;
		    }
		}
	    }
	    break;
    }

    MDIONet_CloseSocket (myNetRecord -> socket);
    if (myNetRecord -> sockAddr != NULL)
    {
	free (myNetRecord -> sockAddr);
    }
    free (myNetRecord -> buf);
    free (myNetRecord);
    stLastStreamOpened = NULL;
    return NULL;
} // MIONet_Open