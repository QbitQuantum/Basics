/*
 * upap_sauthreq - Send an Authenticate-Request.
 */
static void
upap_sauthreq(upap_state *u)
{
  u_char *outp;
  int outlen;

  outlen = UPAP_HEADERLEN + 2 * sizeof (u_char) 
         + u->us_userlen + u->us_passwdlen;
  outp = outpacket_buf[u->us_unit];

  MAKEHEADER(outp, PPP_PAP);

  PUTCHAR(UPAP_AUTHREQ, outp);
  PUTCHAR(++u->us_id, outp);
  PUTSHORT(outlen, outp);
  PUTCHAR(u->us_userlen, outp);
  BCOPY(u->us_user, outp, u->us_userlen);
  INCPTR(u->us_userlen, outp);
  PUTCHAR(u->us_passwdlen, outp);
  BCOPY(u->us_passwd, outp, u->us_passwdlen);

  pppWrite(u->us_unit, outpacket_buf[u->us_unit], outlen + PPP_HDRLEN);

  UPAPDEBUG((LOG_INFO, "pap_sauth: Sent id %d\n", u->us_id));

  TIMEOUT(upap_timeout, u, u->us_timeouttime);
  ++u->us_transmits;
  u->us_clientstate = UPAPCS_AUTHREQ;
}