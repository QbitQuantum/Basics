int
helo(thread_pool_t *info, thread_ctx_t *thread_ctx, edict_t *edict)
{
    chkresult_t *result;
    struct hostent *host, *reversehost;
    grey_tuple_t *request;
    const char *helostr;
    const char *client_address;
    char addrstrbuf[INET_ADDRSTRLEN];
    const char *ptr;
    mseconds_t timelimit;

    request = (grey_tuple_t *)edict->job;
    helostr = request->helo_name;
    client_address = request->client_address;
    assert(helostr);
    assert(client_address);

    result = (chkresult_t *)Malloc(sizeof(chkresult_t));
    memset(result, 0, sizeof(*result));
    result->judgment = J_UNDEFINED;
    result->checkname = "helo";

    timelimit = edict->timelimit;

    /* check the validity of helo string */
    if (check_helo(helostr)) {
        logstr(GLOG_DEBUG, "Syntactically suspicious helo name");
        /* one for invalid helo string AND one for not matching the client ip */
        result->weight += 2; /* FIXME */
        /* no point in doing dns queries as invalid helo wouldn't match the client ip */
        goto FINISH;
    }

    /* check if helo resolves to client ip */
    host = Gethostbyname(helostr, timelimit);
    if (host) {
        ptr = inet_ntop(AF_INET, host->h_addr_list[0], addrstrbuf, INET_ADDRSTRLEN);
        if (NULL == ptr) {
            /* this should never happen */
            logstr(GLOG_ERROR, "helo_name resolved to an invalid ip");
            goto FINISH;
        }
        logstr(GLOG_INSANE, "client_address (%s), helo (%s)",
               client_address, addrstrbuf); /* FIXME */
        if (strcmp(addrstrbuf, client_address)) {
            logstr(GLOG_DEBUG, "helo name (%s) does not resolve to client address (%s)",
                   helostr, client_address);
            result->weight += 1; /* FIXME */
        }
    } else {
        logstr(GLOG_DEBUG, "helo_name not resolvable");
        result->weight += 1; /* FIXME */
    }

    /* check if client's PTR record match helo */
    reversehost = Gethostbyaddr_str(client_address, timelimit);
    if (reversehost) {
        logstr(GLOG_INSANE, "client_address (%s) has a PTR record (%s)",
               client_address, reversehost->h_name);
        if (strcmp(reversehost->h_name, helostr)) {
            logstr(GLOG_DEBUG, "PTR for client_address (%s) differs from helo_name (%s)",
                   reversehost->h_name, helostr);
            result->weight += 1; /* FIXME */
        }
    } else {
        logstr(GLOG_INSANE, "client_address (%s) does not have a PTR record");
        result->weight += 1; /* FIXME */
    }

FINISH:
    if (result->weight > 0)
        result->judgment = J_SUSPICIOUS;
    send_result(edict, result);
    logstr(GLOG_DEBUG, "helo returning");
    request_unlink(request);

    return 0;
}