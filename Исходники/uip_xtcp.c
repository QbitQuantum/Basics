/* -----------------------------------------------------------------------------
 * xtcpd_appcall
 *
 * this function is called, when a package comes in for an upper layer
 * application.
 * -------------------------------------------------------------------------- */
void
xtcpd_appcall(void)
{
  xtcpd_state_t *s;

  /* --------------- DHCP (v4)  --------------- */
  if (uip_udpconnection() &&
      (uip_udp_conn->lport == HTONS(DHCPC_CLIENT_PORT) ||
       uip_udp_conn->lport == HTONS(DHCPC_SERVER_PORT))) {
#if UIP_USE_DHCP
    dhcpc_appcall();
#endif
    return;
  }

  /* --------- set up a new connection  ---------- */
  if (uip_udpconnection()){
    s = (xtcpd_state_t *) &(uip_udp_conn->appstate);
    if (uip_newdata()) {
    	// Set remote port to upper layer state
      s->conn.remote_port = HTONS(UDPBUF->srcport);
      uip_ipaddr_copy(s->conn.remote_addr.u8, BUF->srcipaddr.u8);
    }
  } else if (uip_conn == NULL) {
      // dodgy uip_conn
      return;
  } else {
    s = (xtcpd_state_t *) &(uip_conn->appstate);
  }

  /* ------ passing new connection event up to the upper xtcp layer  ---- */
  if (uip_connected()) {
    if (!uip_udpconnection()) {
      init_xtcpd_state(s,
                       XTCP_PROTOCOL_TCP,
                       *((xtcp_ipaddr_t *) (&uip_conn->ripaddr)),
                       uip_conn->lport,
                       uip_conn->rport,
                       uip_conn);
      xtcpd_event(XTCP_NEW_CONNECTION, s);
    } else {
      init_xtcpd_state(s,
                       XTCP_PROTOCOL_UDP,
                       *((xtcp_ipaddr_t *) (&uip_udp_conn->ripaddr)),
                       uip_udp_conn->lport,
                       uip_udp_conn->rport,
                       uip_udp_conn);
      xtcpd_event(XTCP_NEW_CONNECTION, s);
    }
  }

  /* --------------- new data event to deliver  --------------- */
  if (uip_newdata() && uip_len > 0) {
    if (s->linknum != -1) {
      xtcpd_service_clients_until_ready(s->linknum, xtcp_cons.links, xtcp_cons.nr);
      xtcpd_recv(xtcp_cons.links, s->linknum, xtcp_cons.nr,
                 s,
                 uip_appdata,
                 uip_datalen());
      if (!uip_udpconnection() && s->s.ack_recv_mode) {
        uip_stop();
      }
    }
  } else if (uip_aborted()) {
    xtcpd_event(XTCP_ABORTED, s);
    return;
  } else if (uip_timedout()) {
    xtcpd_event(XTCP_TIMED_OUT, s);
    return;
  }

  /* ------------ passing acknowleg event to upper layer  ------------- */
  if (uip_acked()) {
    int len;
    if (s->linknum != -1) {
      len =
        do_xtcpd_send(xtcp_cons.links[s->linknum],
                      XTCP_SENT_DATA,
                      s,
                      uip_appdata,
                      uip_udpconnection() ? XTCP_CLIENT_BUF_SIZE : uip_mss());

      uip_send(uip_appdata, len);
    }
  }

  /* -------------- retransmit the last package  -------------- */
  if (uip_rexmit()) {
    int len;
    if (s->linknum != -1) {
      xtcpd_service_clients_until_ready(s->linknum, xtcp_cons.links, xtcp_cons.nr);
#ifdef XTCP_ENABLE_PARTIAL_PACKET_ACK
      s->conn.outstanding = 0;
#endif
      len = xtcpd_send(xtcp_cons.links[s->linknum],
                       XTCP_RESEND_DATA,
                       s,
                       uip_appdata,
                       uip_udpconnection() ? XTCP_CLIENT_BUF_SIZE : uip_mss());
      if (len != 0)
        uip_send(uip_appdata, len);
    }
  }

  /* --------------- poll a connection --------------- */
  if (uip_poll()) {
    uip_xtcpd_handle_poll(s);
  }

#if XTCP_ENABLE_PUSH_FLAG_NOTIFICATION
  if (uip_tcp_push()) {
    xtcpd_event(XTCP_PUSH_DATA, s);
  }
#endif

  /* ------------- connection close event  ------------ */
  if (uip_closed()) {
    if (!s->s.closed){
      s->s.closed = 1;

      xtcpd_event(XTCP_CLOSED, s);
    }
    return;
  }

}