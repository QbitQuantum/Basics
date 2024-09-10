static THREAD_RETURN returnChannelMain(void *args) {
    struct returnChannel *returnChannel = (struct returnChannel *) args;
    fd_set read_set;
    int r=0;
    FD_ZERO(&read_set);

    while(1) {
        struct sockaddr_in from;
        int clNo;
        int pos = pc_getConsumerPosition(returnChannel->freeSpace);
        pc_consumeAny(returnChannel->freeSpace);
        do {
            struct timeval tv;
            if(returnChannel->stopIt)
                return 0;
            FD_SET(returnChannel->rcvSock,&read_set);
            tv.tv_sec=0;
            tv.tv_usec=100;
            r = select(returnChannel->rcvSock+1,
                       &read_set, NULL, NULL, &tv);
        } while(r==0);

        RECV(returnChannel->rcvSock, 
             returnChannel->q[pos].msg, from,
             returnChannel->config->portBase);
        clNo = udpc_lookupParticipant(returnChannel->participantsDb, &from);
        if (clNo < 0) { 
            /* packet from unknown provenance */
            continue;
        }
        returnChannel->q[pos].clNo = clNo;
        pc_consumed(returnChannel->freeSpace, 1);
        pc_produce(returnChannel->incoming, 1);
    }
}