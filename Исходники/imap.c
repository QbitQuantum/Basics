static void
search_cb(LDAP *ld, LDAPMessage *msg, void *priv)
{
    struct imap_context *ctx = priv;
    struct bufferevent *server_bev;
    struct evbuffer *out;
    BerValue **servername = NULL;

    out = bufferevent_get_output(ctx->client_bev);
    if (msg) {
        servername = ldap_get_values_len(ld, msg, "mailhost");
    }

    // user not provisioned
    if (!servername || !*servername) {
        /*FIXME: need the full request to have somethng to send */
        evbuffer_add_printf(out, "some_tag " AUTH_FAILED_MSG CRLF);
        bufferevent_enable(ctx->client_bev, EV_READ);
        return;
    }

    server_bev = bufferevent_socket_new(ctx->driver->base, -1, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_enable(server_bev, EV_READ|EV_WRITE);
    bufferevent_socket_connect_hostname(server_bev, ctx->driver->dnsbase, AF_UNSPEC, servername[0]->bv_val, ctx->driver->config->default_port);
    bufferevent_setcb(server_bev, NULL, NULL, server_connect_cb, ctx);

    /*
    // copy over client data, CRLF in request has been skipped, so append that
    bufferevent_write(server_bev, req->line.bv_val, req->line.bv_len);
    bufferevent_write(server_bev, CRLF, 2);
    */

    ctx->server_bev = server_bev;
    ldap_value_free_len(servername);
}