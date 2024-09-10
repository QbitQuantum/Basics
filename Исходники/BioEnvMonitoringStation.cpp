int doClientTask (const char *pszRemoteHost, unsigned short usRemotePort, bool bUseMockets)
{
    int rc;
    static char buf [1024];
    static bool bBufInitialized;

    if (!bBufInitialized) {
        srand (1234);
        for (int i = 0; i < sizeof (buf); i++) {
            buf[i] = (char) rand();
        }
        bBufInitialized = true;
    }

    if (bUseMockets) {
        Mocket *pm = new Mocket();
        pm->registerPeerUnreachableWarningCallback (unreachablePeerCallback, NULL);

        puts ("doClientTask: Using Mockets:Before connect");
        if (0 != (rc = pm->connect (pszRemoteHost, usRemotePort))) {
            fprintf (stderr, "doClientTask: failed to connect using Mockets to remote host %s on port %d; rc = %d\n",
                     pszRemoteHost, usRemotePort, rc);
            puts ("doClientTask: Unable to connect");
            delete pm;
            return -11;
        }
        
        MessageSender rlsq = pm->getSender (true, true);
        MessageSender ursq = pm->getSender (false, true);

        // open stats file
        FILE *file = fopen (CLIENT_STATS_FILENAME, "a");
        if (file == NULL) {
            fprintf (stderr, "failed to append to file %s\n", CLIENT_STATS_FILENAME);
            return -12;
        }

        // mockets client code
        for (int i = 0; continue_flag; ++i) {
            // write sequence number in the first 4 bytes
            *((uint32*)buf) = EndianHelper::htonl ((uint32)i); 
            if (0 == (i % PACKET_PER_SEC)) {
                // send one reliable sequenced packet per second
                rlsq.send (buf, sizeof (buf));
            } else {
                // send an unreliable sequenced packet
                ursq.send (buf, sizeof (buf));
            }            
            sleepForMilliseconds (20);
        }

        fclose (file);
        pm->close();
        delete pm;
    } else {
        TCPSocket socket;
        puts ("doClientTask: Using Sockets:Before connect");
        if (0 != (rc = socket.connect (pszRemoteHost, usRemotePort))) {
            fprintf (stderr, "doClientTask: failed to connect using sockets to remote host %s on port %d; rc = %d\n",
                     pszRemoteHost, usRemotePort, rc);
            puts ("doClientTask: Unable to connect");
            return -11;
        }

        // open stats file
        FILE *file = fopen (CLIENT_STATS_FILENAME, "a");
        if (file == NULL) {
            fprintf (stderr, "failed to append to file %s\n", CLIENT_STATS_FILENAME);
            return -12;
        }

        // sockets client code
        for (int i = 0; continue_flag; ++i) {
            // write sequence number in the first 4 bytes
            *((uint32*)buf) = EndianHelper::htonl ((uint32)i); 
            socket.send (buf, sizeof (buf));
            sleepForMilliseconds (20);
        }

        fclose (file);
        socket.disconnect();
    }

    return 0;
}