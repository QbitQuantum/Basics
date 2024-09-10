static void
udp6_send(netmsg_t msg)
{
	struct socket *so = msg->send.base.nm_so;
	struct mbuf *m = msg->send.nm_m;
	struct sockaddr *addr = msg->send.nm_addr;
	struct mbuf *control = msg->send.nm_control;
	struct thread *td = msg->send.nm_td;
	struct inpcb *inp;
	int error = 0;

	inp = so->so_pcb;
	if (inp == NULL) {
		error = EINVAL;
		goto bad;
	}

	if (addr) {
		struct sockaddr_in6 *sin6;

		if (addr->sa_len != sizeof(struct sockaddr_in6)) {
			error = EINVAL;
			goto bad;
		}
		if (addr->sa_family != AF_INET6) {
			error = EAFNOSUPPORT;
			goto bad;
		}

		sin6 = (struct sockaddr_in6 *)addr;
		if (IN6_IS_ADDR_V4MAPPED(&sin6->sin6_addr)) {
			error = EADDRNOTAVAIL;
			goto bad;
		}
	}

	error = udp6_output(inp, m, addr, control, td);
	lwkt_replymsg(&msg->send.base.lmsg, error);
	return;
bad:
	m_freem(m);
	lwkt_replymsg(&msg->send.base.lmsg, error);
}