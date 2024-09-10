static CURLcode ldap_connecting(struct connectdata *conn, bool *done)
{
  ldapconninfo *li = conn->proto.generic;
  struct SessionHandle *data = conn->data;
  LDAPMessage *msg = NULL;
  struct timeval tv = {0, 1}, *tvp;
  int rc, err;
  char *info = NULL;

#ifdef USE_SSL
  if(conn->handler->flags & PROTOPT_SSL) {
    /* Is the SSL handshake complete yet? */
    if(!li->ssldone) {
      CURLcode result = Curl_ssl_connect_nonblocking(conn, FIRSTSOCKET,
                                                     &li->ssldone);
      if(result || !li->ssldone)
        return result;
    }

    /* Have we installed the libcurl SSL handlers into the sockbuf yet? */
    if(!li->sslinst) {
      Sockbuf *sb;
      ldap_get_option(li->ld, LDAP_OPT_SOCKBUF, &sb);
      ber_sockbuf_add_io(sb, &ldapsb_tls, LBER_SBIOD_LEVEL_TRANSPORT, conn);
      li->sslinst = TRUE;
      li->recv = conn->recv[FIRSTSOCKET];
      li->send = conn->send[FIRSTSOCKET];
    }
  }
#endif

  tvp = &tv;

retry:
  if(!li->didbind) {
    char *binddn;
    struct berval passwd;

    if(conn->bits.user_passwd) {
      binddn = conn->user;
      passwd.bv_val = conn->passwd;
      passwd.bv_len = strlen(passwd.bv_val);
    }
    else {
      binddn = NULL;
      passwd.bv_val = NULL;
      passwd.bv_len = 0;
    }
    rc = ldap_sasl_bind(li->ld, binddn, LDAP_SASL_SIMPLE, &passwd,
                        NULL, NULL, &li->msgid);
    if(rc)
      return CURLE_LDAP_CANNOT_BIND;
    li->didbind = TRUE;
    if(tvp)
      return CURLE_OK;
  }

  rc = ldap_result(li->ld, li->msgid, LDAP_MSG_ONE, tvp, &msg);
  if(rc < 0) {
    failf(data, "LDAP local: bind ldap_result %s", ldap_err2string(rc));
    return CURLE_LDAP_CANNOT_BIND;
  }
  if(rc == 0) {
    /* timed out */
    return CURLE_OK;
  }

  rc = ldap_parse_result(li->ld, msg, &err, NULL, &info, NULL, NULL, 1);
  if(rc) {
    failf(data, "LDAP local: bind ldap_parse_result %s", ldap_err2string(rc));
    return CURLE_LDAP_CANNOT_BIND;
  }

  /* Try to fallback to LDAPv2? */
  if(err == LDAP_PROTOCOL_ERROR) {
    int proto;
    ldap_get_option(li->ld, LDAP_OPT_PROTOCOL_VERSION, &proto);
    if(proto == LDAP_VERSION3) {
      if(info) {
        ldap_memfree(info);
        info = NULL;
      }
      proto = LDAP_VERSION2;
      ldap_set_option(li->ld, LDAP_OPT_PROTOCOL_VERSION, &proto);
      li->didbind = FALSE;
      goto retry;
    }
  }

  if(err) {
    failf(data, "LDAP remote: bind failed %s %s", ldap_err2string(rc),
          info ? info : "");
    if(info)
      ldap_memfree(info);
    return CURLE_LOGIN_DENIED;
  }

  if(info)
    ldap_memfree(info);
  conn->recv[FIRSTSOCKET] = ldap_recv;
  *done = TRUE;

  return CURLE_OK;
}