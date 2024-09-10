SMTP_SESSION *smtp_session_alloc(VSTREAM *stream, SMTP_ITERATOR *iter,
				         time_t start, int flags)
{
    SMTP_SESSION *session;
    const char *host = STR(iter->host);
    const char *addr = STR(iter->addr);
    unsigned port = iter->port;

    session = (SMTP_SESSION *) mymalloc(sizeof(*session));
    session->stream = stream;
    session->iterator = iter;
    session->namaddr = concatenate(host, "[", addr, "]", (char *) 0);
    session->helo = 0;
    session->port = port;
    session->features = 0;

    session->size_limit = 0;
    session->error_mask = 0;
    session->buffer = vstring_alloc(100);
    session->scratch = vstring_alloc(100);
    session->scratch2 = vstring_alloc(100);
    smtp_chat_init(session);
    session->mime_state = 0;

    if (session->port) {
	vstring_sprintf(session->buffer, "%s:%d",
			session->namaddr, ntohs(session->port));
	session->namaddrport = mystrdup(STR(session->buffer));
    } else
	session->namaddrport = mystrdup(session->namaddr);

    session->send_proto_helo = 0;

    if (flags & SMTP_MISC_FLAG_CONN_STORE)
	CACHE_THIS_SESSION_UNTIL(start + var_smtp_reuse_time);
    else
	DONT_CACHE_THIS_SESSION;
    session->reuse_count = 0;
    USE_NEWBORN_SESSION;			/* He's not dead Jim! */

#ifdef USE_SASL_AUTH
    smtp_sasl_connect(session);
#endif

#ifdef USE_TLS
    session->tls_context = 0;
    session->tls_retry_plain = 0;
    session->tls_nexthop = 0;
#endif
    session->state = 0;
    debug_peer_check(host, addr);
    return (session);
}