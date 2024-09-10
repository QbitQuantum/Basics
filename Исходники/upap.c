/*
 * upap_sauthreq - Send an Authenticate-Request.
 */
static void upap_sauthreq(ppp_pcb *pcb) {
    struct pbuf *p;
    u_char *outp;
    int outlen;

    outlen = UPAP_HEADERLEN + 2 * sizeof (u_char) +
             pcb->upap.us_userlen + pcb->upap.us_passwdlen;
    p = pbuf_alloc(PBUF_RAW, (u16_t)(PPP_HDRLEN +outlen), PPP_CTRL_PBUF_TYPE);
    if(NULL == p)
        return;
    if(p->tot_len != p->len) {
        pbuf_free(p);
        return;
    }

    outp = (u_char*)p->payload;
    MAKEHEADER(outp, PPP_PAP);

    PUTCHAR(UPAP_AUTHREQ, outp);
    PUTCHAR(++pcb->upap.us_id, outp);
    PUTSHORT(outlen, outp);
    PUTCHAR(pcb->upap.us_userlen, outp);
    MEMCPY(outp, pcb->upap.us_user, pcb->upap.us_userlen);
    INCPTR(pcb->upap.us_userlen, outp);
    PUTCHAR(pcb->upap.us_passwdlen, outp);
    MEMCPY(outp, pcb->upap.us_passwd, pcb->upap.us_passwdlen);

    ppp_write(pcb, p);

    TIMEOUT(upap_timeout, pcb, pcb->settings.pap_timeout_time);
    ++pcb->upap.us_transmits;
    pcb->upap.us_clientstate = UPAPCS_AUTHREQ;
}