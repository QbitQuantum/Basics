/**
 * Returns 1 if retried, 0 if the command should fail, -1 for an internal
 * error
 */
static int handle_not_my_vbucket(lcb_server_t *c,
                                 protocol_binary_request_header *oldreq,
                                 struct lcb_command_data_st *oldct)
{
    int idx;
    char *body;
    lcb_size_t nbody, nr;
    lcb_server_t *new_srv;
    struct lcb_command_data_st ct;
    protocol_binary_request_header req;
    hrtime_t now;

    if (c->instance->compat.type == LCB_CACHED_CONFIG) {
        lcb_schedule_config_cache_refresh(c->instance);
    }

    /* re-schedule command to new server */
    idx = vbucket_found_incorrect_master(c->instance->vbucket_config,
                                         ntohs(oldreq->request.vbucket),
                                         (int)c->index);

    if (idx == -1) {
        return 0;
    }

    now = gethrtime();

    if (oldct->real_start) {
        hrtime_t min_ok = now - (c->connection.timeout.usec * 1000);
        if (oldct->real_start < min_ok) {
            /** Timed out in a 'natural' manner */
            return 0;
        }
    }

    req = *oldreq;

    lcb_assert((lcb_size_t)idx < c->instance->nservers);
    new_srv = c->instance->servers + idx;

    nr = lcb_ringbuffer_read(&c->cmd_log, req.bytes, sizeof(req));
    lcb_assert(nr == sizeof(req));

    req.request.opaque = ++c->instance->seqno;
    nbody = ntohl(req.request.bodylen);
    body = malloc(nbody);
    if (body == NULL) {
        lcb_error_handler(c->instance, LCB_CLIENT_ENOMEM, NULL);
        return -1;
    }
    nr = lcb_ringbuffer_read(&c->cmd_log, body, nbody);
    lcb_assert(nr == nbody);
    nr = lcb_ringbuffer_read(&c->output_cookies, &ct, sizeof(ct));
    lcb_assert(nr == sizeof(ct));

    /* Preserve the cookie and reset timestamp for the command. This
     * means that the library will retry the command until it will
     * get code different from LCB_NOT_MY_VBUCKET */
    if (!ct.real_start) {
        ct.real_start = ct.start;
    }
    ct.start = now;

    lcb_server_retry_packet(new_srv, &ct, &req, sizeof(req));
    /* FIXME dtrace instrumentation */
    lcb_server_write_packet(new_srv, body, nbody);
    lcb_server_end_packet(new_srv);
    lcb_server_send_packets(new_srv);
    free(body);

    return 1;
}