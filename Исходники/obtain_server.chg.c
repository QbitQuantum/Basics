bool_t
search_1_svc(query_req *argp, query_rec *result, struct svc_req *rqstp)
{
	bool_t retval = TRUE;
	b_query_req *query;
    query_node_t *node;
    char *p;
	char fname[MAXPATHLEN];
    char peer[MAXHOSTNAME+2];
	int i, fd;
    FILE *fh;
	peers_t resp;
    int ret;
    struct timeval now;
    struct timespec timeout;

#ifdef DEBUG
    printf("search_1_svc() %s  : Received request for file : %s\n", localhostname, argp->fname);
#endif

    /*
     * Build the b_query_req for this request.
     */
    if ((query = (b_query_req *) malloc(sizeof(b_query_req))) == NULL) {
        printf("Failed to allocate memory !\n");
        printf("Hoping the reaper thread will free some memory !\n");
        goto send_result;
    }

	query->id.hostid = gethostid();
	query->id.seqno = getseqno(); 
    query->ttl = MAXTTL;
    strcpy(query->uphost, localhostname);
    strcpy(query->fname, argp->fname);

    /*
     * Now propagate the query to the peers.
     */
    node = b_query_propagate(query, LOCKED);

    /*
     * If we propagated to some peers then we should wait for some time for the
     * results to arrive and send the results.
     */
    if (node) { 
        if (node->sent) {
            /*
             * We now wait for a max of WAITTIME (1 second) on the CV (allhome_cv).
             * And the b_hitquery_reply() signals the CV when all the
             * peers that we had queried have reponded back. However, if no one
             * responds back we bail out in 1 secs.
             *
             * NOTE : This timeout may be short for large number of nodes.
             * However, for the current set up of upto to 12 nodes this is
             * reasonable.
             */
            gettimeofday(&now, NULL);
            timeout.tv_sec = now.tv_sec + WAITTIME;
            timeout.tv_nsec = now.tv_usec *1000;

            pthread_cond_timedwait(&node->allhome_cv, &node->node_lock, &timeout);
        }
        pthread_mutex_unlock(&node->node_lock);
    }

send_result:
    /*
     * At this point we should have received results from our peers and their
     * peers and the local cache should have been updated. So we now send our
     * hits from the local cache.
     */
    sprintf(fname, "%s/%s", SERVER_DIR, argp->fname);

    fh = fopen(fname, "r");
    if (fh == NULL) {
        printf("search_1_svc:Failed to open filename %s : errno = %d\n", fname, errno);
        result->count = 0;
        return retval;
    }

    fd = fileno(fh);
    flock(fd, LOCK_SH);

    strcpy(result->fname, argp->fname);
    result->count = 0;
    p = result->peers; 
    
    while (fgets(p, MAXHOSTNAME, fh) != NULL) {
        p[strlen(p) - 1] = '\0';
        result->count++;
        /* 
         * We have filled up the response with MAXCOUNT results.
         * Send it back.
         */
        if (result->count == MAXCOUNT) {
            flock(fd, LOCK_UN);
            fclose(fh);
            close(fd);
            result->eof = 0;
            return retval;
        }
        p += MAXHOSTNAME;
    }

    printf("p = %s\n", p);
    /*
    if (*p) {
        result->count++;
    }
    */

    flock(fd, LOCK_UN);
    fclose(fh);
    close(fd);
    result->eof = 1;
#ifdef DEBUG
    printf("search_1_svc: Done. count = %d\n", result->count);
#endif
	return retval;
}