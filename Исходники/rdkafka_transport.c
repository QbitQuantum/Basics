int rd_kafka_transport_poll(rd_kafka_transport_t *rktrans, int tmout) {
#ifndef _MSC_VER
	int r;

	r = poll(&rktrans->rktrans_pfd, 1, tmout);
	if (r <= 0)
		return r;
	return rktrans->rktrans_pfd.revents;
#else
	int r;

	r = WSAPoll(&rktrans->rktrans_pfd, 1, tmout);
	if (r == 0) {
		/* Workaround for broken WSAPoll() while connecting:
		 * failed connection attempts are not indicated at all by WSAPoll()
		 * so we need to check the socket error when Poll returns 0.
		 * Issue #525 */
		r = ECONNRESET;
		if (unlikely(rktrans->rktrans_rkb->rkb_state ==
			     RD_KAFKA_BROKER_STATE_CONNECT &&
			     (rd_kafka_transport_get_socket_error(rktrans,
								  &r) == -1 ||
			      r != 0))) {
			char errstr[512];
			errno = r;
			rd_snprintf(errstr, sizeof(errstr),
				    "Connect to %s failed: %s",
				    rd_sockaddr2str(rktrans->rktrans_rkb->
						    rkb_addr_last,
						    RD_SOCKADDR2STR_F_PORT |
                                                    RD_SOCKADDR2STR_F_FAMILY),
                                    socket_strerror(r));
			rd_kafka_transport_connect_done(rktrans, errstr);
			return -1;
		} else
			return 0;
	} else if (r == SOCKET_ERROR)
		return -1;
	return rktrans->rktrans_pfd.revents;
#endif
}