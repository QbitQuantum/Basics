/*
    Windows unnamed pipe emulation, used to enable select()
    on a Windows machine for the CALLBACK (pipe-based) transport domain.
*/
int create_winpipe_transport (int *pipefds)
{
    SOCKET socketpair[2];

    struct sockaddr_in socketaddress[2];

    struct timeval waittime = { 0, 200000 };
    fd_set readset;

    if (InitUPDSocket (&socketpair[0], &socketaddress[0]))
    {
        CloseUDPSocketPair (socketpair);
        return -1;
    }
    if (InitUPDSocket (&socketpair[1], &socketaddress[1]))
    {
        CloseUDPSocketPair (socketpair);
        return -1;
    }

    /*
       I have two UDP sockets - now lets connect them to each other.
     */

    if (ConnectUDPSocket (&socketpair[0], &socketaddress[0], &socketpair[1]))
    {
        CloseUDPSocketPair (socketpair);
        return -1;
    }
    if (ConnectUDPSocket (&socketpair[1], &socketaddress[1], &socketpair[0]))
    {
        CloseUDPSocketPair (socketpair);
        return -1;
    }

    /*
       The two sockets are connected to each other, now lets test the connection
       by sending the own port number.
     */
    if (TestUDPSend (&socketpair[0], &socketaddress[0]))
    {
        CloseUDPSocketPair (socketpair);
        return -1;
    }
    if (TestUDPSend (&socketpair[1], &socketaddress[1]))
    {
        CloseUDPSocketPair (socketpair);
        return -1;
    }

    /*
       Port numbers sent, now lets select() on the socketpair and check that 
       both messages got through
     */
    FD_ZERO (&readset);
    FD_SET (socketpair[0], &readset);
    FD_SET (socketpair[1], &readset);

    /*
       For some unknown reason the timeout setting in the select call does not have
       the desired effect, and for yet another unknown reason a Sleep(1) solves this
       problem.
     */
    Sleep (1);
    if (select (0, &readset, NULL, NULL, &waittime) != 2 || !FD_ISSET (socketpair[0], &readset)
        || !FD_ISSET (socketpair[1], &readset))
    {
        CloseUDPSocketPair (socketpair);
        return -1;
    }

    /*
       Check if the packets I receive were really sent by me, and nobody else
       tried to sneak.
     */
    if (TestUDPReceive (&socketpair[0], &socketpair[1], &socketaddress[1]))
    {
        CloseUDPSocketPair (socketpair);
        return -1;
    }
    if (TestUDPReceive (&socketpair[1], &socketpair[0], &socketaddress[0]))
    {
        CloseUDPSocketPair (socketpair);
        return -1;
    }

    /*
       All sanity checks passed, I can return a "UDP pipe"
     */
    pipefds[0] = (int) socketpair[0];
    pipefds[1] = (int) socketpair[1];

    return 0;
}