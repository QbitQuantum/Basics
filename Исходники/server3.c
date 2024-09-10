void *hczmq(void *ptr) {
    struct host_connection hc;
    char port[6], timestamp[16], info[25];
    struct tm *tm;
    int idx;
    int rc;

    struct request req[1];
    zmsg_t *msg;

    printf("message from main thread: %s\n", (char *)ptr);

    // setup zmq server
    zsock_t *sock = zsock_new_rep(HCZMQ_SOCK);

    while(1) {
        // recv
        rc = get_request(sock, req);
        if (rc < 0) {
            // bad request
            continue;
        }
        strftime(timestamp, 16, "%Y%m%d%H%M%S", localtime(&req->timestamp));
        printf("ip: %s, timestamp: %s\n", INET_NTOA(req->ip), timestamp);

        // retrieve host connection by ip and timestamp
        pthread_mutex_lock(&mutex);
        msg = zmsg_new();
        for (idx = 0; idx < 3; idx++) {
            sprintf(port, "%d", ghc->conns[idx].port);
            tm = localtime(&ghc->conns[idx].timestamp);
            strftime(timestamp, 16, "%Y%m%d%H%M%S", tm);
            sprintf(info, "%s:%s", port, timestamp);
            printf("  %s\n", info);
            zmsg_addmem(msg, info, strlen(info));
        }
        pthread_mutex_unlock(&mutex);

        // send
        zmsg_send(&msg, sock);
    }

    pthread_exit((void*)123);
}