int lp_do_bind(BerElement *ber, lp_connection_t *c, ber_int_t msgid)
{
    TRACE();
    ber_tag_t tag;
    ber_len_t len;
    ber_tag_t method;
    ber_int_t version;
    //char *name = NULL;
    int ret;

    if ((tag = ber_peek_tag(ber, &len)) == LBER_ERROR) {
        lp_log_error("ber_peek_tag returns 0x%lx", tag);
        return LP_ERR;
    }
    lp_assert(tag == LDAP_REQ_BIND);

    //tag = ber_scanf(ber, "{iat", &version, &name, &method);
    tag = ber_scanf(ber, "{it", &version, &method);
    if (tag == LBER_ERROR) {
        lp_log_error("ber_scanf failed!");
        return LP_ERR;
    }
    //lp_log_debug("vesrion: %d,\tname: %s, method: 0x%lx",
    //              version, name, method);
    //ber_memfree(name);

    ret = lp_response_bind(c, msgid);

    return ret;
}