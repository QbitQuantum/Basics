int server (void)
{
    pLogFile = fopen ("unreliable_data_test.log", "a");
    if (pLogFile == NULL) {
        printf ("error creating the logfile\n");
        exit(1);
    }

    int rc;
    if ( (rc = msgServerMocket.listen (MOCKETS_PORT_NUM)) < 0 ) {
        printf ("server:: error on msgServerMocket.listen(). rc = %d\n", rc);
        return -1;
    }
    if (0 != (rc = dgSocket.init (UDP_PORT_NUM))) {
        fprintf (stderr, "failed to bind datagram socket to port %d; rc = %d\n", UDP_PORT_NUM, rc);
        return -2;
    }

    //printf ("server():: before mocketServerThread()\n");
    OSThread mocketServerThread;
    mocketServerThread.start (serverMocket, NULL);

    rc = udpServer();

    return rc;
}