//
// This is the wait function used to keep track of events
//
int DoWait(WSAEVENT *Handles, Socklist *socklist)
{

    DWORD wait_rc = 0;
    WSAEVENT hTemp = WSA_INVALID_EVENT;
    Socklist socklTemp;

    int i = 0;

    //
    // Rotate the array, beginning at index 1, by one element.
    // This ensures that all handles get a fair chance to be serviced.
    //
    // There is no way to detect how many handles were signalled when
    // WSAWaitForMultipleObjects() returns. We simply pick the first one and 
    // come back to this function later
    // Without the rotation below, this has the potential for starving
    // connections accepted later.
    //
    // Index 0 is avoided, since it is our listening socket. 
    //
    for ( i = 1; i < curr_size-1; i++ )
    {
        hTemp = Handles[i+1];
        Handles[i+1] = Handles[i];
        Handles[i] = hTemp;

        socklTemp = socklist[i+1];
        socklist[i+1] = socklist[i];
        socklist[i] = socklTemp;
    }

    if(WSA_WAIT_FAILED == (wait_rc = WSAWaitForMultipleEvents(curr_size,
                                                              Handles,
                                                              FALSE,
                                                              WSA_INFINITE, 
                                                              FALSE
                                                              )))
    {
        ERR("WSAWaitForMultipleEvents()");
        return -1;
    }

    return(wait_rc - WSA_WAIT_EVENT_0);
}