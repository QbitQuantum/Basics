int doClientTask (const char *pszRemoteHost, unsigned short usRemotePort, bool bUseMockets, Stats *pStats)
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
        StreamMocket mocket;
        if (0 != (rc = mocket.connect (pszRemoteHost, usRemotePort))) {
            fprintf (stderr, "doClientTask: failed to connect using mockets to remote host %s on port %d; rc = %d\n",
                     pszRemoteHost, usRemotePort, rc);
            return -1;
        }
        mocket.registerPeerUnreachableWarningCallback (unreachablePeerCallback, NULL);

        int iDataSize = 1024*1024;
        int iBytesSent = 0;
        int64 i64StartTime = getTimeInMilliseconds();
        mocket.send (&iDataSize, sizeof (iDataSize));
        while (iBytesSent < iDataSize) {
            mocket.send (buf, sizeof (buf));
            iBytesSent += sizeof (buf);
        }
        char chReply = 0;
        mocket.receive (&chReply, 1);
        if (chReply != '.') {
            fprintf (stderr, "doClientTask: failed to receive . from remote host\n");
            return -2;
        }
        int64 i64EndTime = getTimeInMilliseconds();
        int iTime = (int) (getTimeInMilliseconds() - i64StartTime);

        pStats->update ((double) (i64EndTime - i64StartTime));
        // Save results to a file
        FILE *file = fopen ("stats-client-streamMockets-cpp.txt", "a");
        if (file == NULL) {
            fprintf (stderr, "failed to append to file stats-mockets-cpp.txt\n");
            return -3;
        }
        fprintf (file, "[%lu]\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", (unsigned long) (getTimeInMilliseconds()/1000), iTime, 
                 mocket.getStatistics()->getSentPacketCount(),
                 mocket.getStatistics()->getSentByteCount(),
                 mocket.getStatistics()->getReceivedPacketCount(),
                 mocket.getStatistics()->getReceivedByteCount(),
                 mocket.getStatistics()->getRetransmitCount(),
                 mocket.getStatistics()->getDuplicatedDiscardedPacketCount(),
                 mocket.getStatistics()->getNoRoomDiscardedPacketCount());
                 /*mocket.getStatistics()->getDiscardedPacketCounts()._iBelowWindow,
                 mocket.getStatistics()->getDiscardedPacketCounts()._iNoRoom,
                 mocket.getStatistics()->getDiscardedPacketCounts()._iOverlap,
                 mocket.getStatistics()->getTransmitterWaitCounts()._iPacketQueueFull,
                 mocket.getStatistics()->getTransmitterWaitCounts()._iRemoteWindowFull);*/

        fclose (file);

        mocket.close();
    }
    else {
        TCPSocket socket;
        if (0 != (rc = socket.connect (pszRemoteHost, usRemotePort))) {
            fprintf (stderr, "doClientTask: failed to connect using sockets to remote host %s on port %d; rc = %d\n",
                     pszRemoteHost, usRemotePort, rc);
            return -3;
        }

        int iDataSize = 1024*1024;
        int iBytesSent = 0;
        int64 i64StartTime = getTimeInMilliseconds();
        socket.send (&iDataSize, sizeof (iDataSize));
        while (iBytesSent < iDataSize) {
            socket.send (buf, sizeof (buf));
            iBytesSent += sizeof (buf);
        }
        char chReply = 0;
        socket.receive (&chReply, 1);
        if (chReply != '.') {
            fprintf (stderr, "doClientTask: failed to receive . from remote host\n");
            return -4;
        }
        int64 i64EndTime = getTimeInMilliseconds();
        int iTime = (int) (getTimeInMilliseconds() - i64StartTime);

        pStats->update ((double) (i64EndTime - i64StartTime));

        // Save results to a file
        FILE *socfile = fopen ("statsSM-client-sockets-cpp.txt", "a");
        if (socfile == NULL) {
            fprintf (stderr, "failed to append to file statsSM-mockets-cpp.txt\n");
            return -3;
        }
    	fprintf (socfile, "[%lu]\t%d\t\n", (unsigned long) (getTimeInMilliseconds()/1000), iTime);

        fclose (socfile);

        socket.disconnect();
    }
    return 0;
}