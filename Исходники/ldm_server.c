hiya_reply_t*
hiya_6_svc(
        prod_class_t *offered,
        struct svc_req *rqstp)
{
    const char* const pqfname = getQueuePath();
    static hiya_reply_t reply;
    SVCXPRT * const xprt = rqstp->rq_xprt;
    struct sockaddr_in *upAddr = (struct sockaddr_in*) svc_getcaller(xprt);
    const char *upName = hostbyaddr(upAddr);
    int error;
    int isPrimary;
    unsigned int maxHereis;
    static prod_class_t *accept;

    /*
     * Open the product-queue for writing.  It will be closed by cleanup()
     * during process termination.
     */
    if (pq) {
        (void) pq_close(pq);
        pq = NULL;
    }
    error = pq_open(pqfname, PQ_DEFAULT, &pq);
    if (error) {
        err_log_and_free(ERR_NEW2(error, NULL,
                "Couldn't open product-queue \"%s\" for writing: %s",
                pqfname,
                PQ_CORRUPT == error
                ? "The product-queue is inconsistent"
                : strerror(error)), ERR_FAILURE);
        svcerr_systemerr(xprt);
        svc_destroy(xprt);
        exit(error);
    }

    /* else */

    error = down6_init(upName, upAddr, pqfname, pq);
    if (error) {
        uerror("Couldn't initialize downstream LDM");
        svcerr_systemerr(xprt);
        svc_destroy(xprt);
        exit(error);
    }
    else {
        uinfo("Downstream LDM initialized");
    }

    /*
     * The previous "accept" is freed here -- rather than freeing the
     * soon-to-be-allocated "accept" at the end of its block -- because it can
     * be used in the reply.
     */
    if (accept) {
        free_prod_class(accept); /* NULL safe */
        accept = NULL;
    }

    error = acl_check_hiya(upName, inet_ntoa(upAddr->sin_addr), offered,
            &accept, &isPrimary);

    maxHereis = isPrimary ? UINT_MAX : 0;

    if (error) {
        serror("Couldn't validate HIYA");
        svcerr_systemerr(xprt);
        svc_destroy(xprt);
        exit(error);
    }
    else {
        if (ulogIsDebug())
            udebug("intersection: %s", s_prod_class(NULL, 0, accept));

        if (accept->psa.psa_len == 0) {
            uwarn("Empty intersection of HIYA offer from %s (%s) and ACCEPT "
                    "entries", upName, s_prod_class(NULL, 0, offered));
            svcerr_weakauth(xprt);
            svc_destroy(xprt);
            exit(0);
        }
        else {
            error = down6_set_prod_class(accept);

            if (error) {
                if (DOWN6_SYSTEM_ERROR == error) {
                    serror("Couldn't set product class: %s",
                            s_prod_class(NULL, 0, accept));
                }
                else {
                    uerror("Couldn't set product class: %s",
                            s_prod_class(NULL, 0, accept));
                }

                svcerr_systemerr(xprt);
                svc_destroy(xprt);
                exit(EXIT_FAILURE);
            }

            /* else */

            if (clss_eq(offered, accept)) {
                unotice("hiya6: %s", s_prod_class(NULL, 0, offered));

                reply.code = OK;
                reply.hiya_reply_t_u.max_hereis = maxHereis;
            }
            else {
                if (ulogIsVerbose()) {
                    char off[512];
                    char acc[512];

                    (void) s_prod_class(off, sizeof(off), offered), (void) s_prod_class(
                            acc, sizeof(acc), accept);

                    uinfo("hiya6: RECLASS: %s -> %s", off, acc);
                }

                reply.code = RECLASS;
                reply.hiya_reply_t_u.feedPar.prod_class = accept;
                reply.hiya_reply_t_u.feedPar.max_hereis = maxHereis;
            }
        } /* product-intersection != empty set */
    } /* successful acl_check_hiya() */

    return &reply;
}