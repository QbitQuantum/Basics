/*-
 * ssl_get_prev attempts to find an SSL_SESSION to be used to resume this
 * connection. It is only called by servers.
 *
 *   hello: The parsed ClientHello data
 *
 * Returns:
 *   -1: fatal error
 *    0: no session found
 *    1: a session may have been found.
 *
 * Side effects:
 *   - If a session is found then s->session is pointed at it (after freeing an
 *     existing session if need be) and s->verify_result is set from the session.
 *   - Both for new and resumed sessions, s->ext.ticket_expected is set to 1
 *     if the server should issue a new session ticket (to 0 otherwise).
 */
int ssl_get_prev_session(SSL *s, CLIENTHELLO_MSG *hello)
{
    /* This is used only by servers. */

    SSL_SESSION *ret = NULL;
    int fatal = 0, discard;
    int try_session_cache = 0;
    TICKET_RETURN r;

    if (SSL_IS_TLS13(s)) {
        if (!tls_parse_extension(s, TLSEXT_IDX_psk_kex_modes,
                                 SSL_EXT_CLIENT_HELLO, hello->pre_proc_exts,
                                 NULL, 0)
                || !tls_parse_extension(s, TLSEXT_IDX_psk, SSL_EXT_CLIENT_HELLO,
                                        hello->pre_proc_exts, NULL, 0))
            return -1;

        ret = s->session;
    } else {
        /* sets s->ext.ticket_expected */
        r = tls_get_ticket_from_client(s, hello, &ret);
        switch (r) {
        case TICKET_FATAL_ERR_MALLOC:
        case TICKET_FATAL_ERR_OTHER:
            fatal = 1;
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GET_PREV_SESSION,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        case TICKET_NONE:
        case TICKET_EMPTY:
            if (hello->session_id_len > 0)
                try_session_cache = 1;
            break;
        case TICKET_NO_DECRYPT:
        case TICKET_SUCCESS:
        case TICKET_SUCCESS_RENEW:
            break;
        }
    }

    if (try_session_cache &&
        ret == NULL &&
        !(s->session_ctx->session_cache_mode &
          SSL_SESS_CACHE_NO_INTERNAL_LOOKUP)) {
        SSL_SESSION data;

        data.ssl_version = s->version;
        memcpy(data.session_id, hello->session_id, hello->session_id_len);
        data.session_id_length = hello->session_id_len;

        CRYPTO_THREAD_read_lock(s->session_ctx->lock);
        ret = lh_SSL_SESSION_retrieve(s->session_ctx->sessions, &data);
        if (ret != NULL) {
            /* don't allow other threads to steal it: */
            SSL_SESSION_up_ref(ret);
        }
        CRYPTO_THREAD_unlock(s->session_ctx->lock);
        if (ret == NULL)
            CRYPTO_atomic_add(&s->session_ctx->stats.sess_miss, 1, &discard,
                              s->session_ctx->lock);
    }

    if (try_session_cache &&
        ret == NULL && s->session_ctx->get_session_cb != NULL) {
        int copy = 1;

        ret = s->session_ctx->get_session_cb(s, hello->session_id,
                                             hello->session_id_len,
                                             &copy);

        if (ret != NULL) {
            CRYPTO_atomic_add(&s->session_ctx->stats.sess_cb_hit, 1, &discard,
                              s->session_ctx->lock);

            /*
             * Increment reference count now if the session callback asks us
             * to do so (note that if the session structures returned by the
             * callback are shared between threads, it must handle the
             * reference count itself [i.e. copy == 0], or things won't be
             * thread-safe).
             */
            if (copy)
                SSL_SESSION_up_ref(ret);

            /*
             * Add the externally cached session to the internal cache as
             * well if and only if we are supposed to.
             */
            if (!
                (s->session_ctx->session_cache_mode &
                 SSL_SESS_CACHE_NO_INTERNAL_STORE)) {
                /*
                 * Either return value of SSL_CTX_add_session should not
                 * interrupt the session resumption process. The return
                 * value is intentionally ignored.
                 */
                SSL_CTX_add_session(s->session_ctx, ret);
            }
        }
    }

    if (ret == NULL)
        goto err;

    /* Now ret is non-NULL and we own one of its reference counts. */

    /* Check TLS version consistency */
    if (ret->ssl_version != s->version)
        goto err;

    if (ret->sid_ctx_length != s->sid_ctx_length
        || memcmp(ret->sid_ctx, s->sid_ctx, ret->sid_ctx_length)) {
        /*
         * We have the session requested by the client, but we don't want to
         * use it in this context.
         */
        goto err;               /* treat like cache miss */
    }

    if ((s->verify_mode & SSL_VERIFY_PEER) && s->sid_ctx_length == 0) {
        /*
         * We can't be sure if this session is being used out of context,
         * which is especially important for SSL_VERIFY_PEER. The application
         * should have used SSL[_CTX]_set_session_id_context. For this error
         * case, we generate an error instead of treating the event like a
         * cache miss (otherwise it would be easy for applications to
         * effectively disable the session cache by accident without anyone
         * noticing).
         */

        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GET_PREV_SESSION,
                 SSL_R_SESSION_ID_CONTEXT_UNINITIALIZED);
        fatal = 1;
        goto err;
    }

    if (ret->timeout < (long)(time(NULL) - ret->time)) { /* timeout */
        CRYPTO_atomic_add(&s->session_ctx->stats.sess_timeout, 1, &discard,
                          s->session_ctx->lock);
        if (try_session_cache) {
            /* session was from the cache, so remove it */
            SSL_CTX_remove_session(s->session_ctx, ret);
        }
        goto err;
    }

    /* Check extended master secret extension consistency */
    if (ret->flags & SSL_SESS_FLAG_EXTMS) {
        /* If old session includes extms, but new does not: abort handshake */
        if (!(s->s3->flags & TLS1_FLAGS_RECEIVED_EXTMS)) {
            SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_SSL_GET_PREV_SESSION,
                     SSL_R_INCONSISTENT_EXTMS);
            fatal = 1;
            goto err;
        }
    } else if (s->s3->flags & TLS1_FLAGS_RECEIVED_EXTMS) {
        /* If new session includes extms, but old does not: do not resume */
        goto err;
    }

    if (!SSL_IS_TLS13(s)) {
        /* We already did this for TLS1.3 */
        SSL_SESSION_free(s->session);
        s->session = ret;
    }

    CRYPTO_atomic_add(&s->session_ctx->stats.sess_hit, 1, &discard,
                      s->session_ctx->lock);
    s->verify_result = s->session->verify_result;
    return 1;

 err:
    if (ret != NULL) {
        SSL_SESSION_free(ret);
        /* In TLSv1.3 s->session was already set to ret, so we NULL it out */
        if (SSL_IS_TLS13(s))
            s->session = NULL;

        if (!try_session_cache) {
            /*
             * The session was from a ticket, so we should issue a ticket for
             * the new session
             */
            s->ext.ticket_expected = 1;
        }
    }
    if (fatal)
        return -1;

    return 0;
}