tcp_socket_t *
tcp_accept (tcp_socket_t *s)
{
	tcp_socket_t *ns;
	buf_t *p;
	ip_hdr_t *iph;
	tcp_hdr_t *h;
	unsigned long optdata;
again:
	mutex_lock (&s->lock);
	for (;;) {
		if (s->state != LISTEN) {
			mutex_unlock (&s->lock);
			tcp_debug ("tcp_accept: called in invalid state\n");
			return 0;
		}
		if (! tcp_queue_is_empty (s)) {
			p = tcp_queue_get (s);
			break;
		}
		mutex_wait (&s->lock);
	}
	mutex_unlock (&s->lock);

	/* Create a new PCB, and respond with a SYN|ACK.
	 * If a new PCB could not be created (probably due to lack of memory),
	 * we don't do anything, but rely on the sender will retransmit
	 * the SYN at a time when we have more memory available. */
	mutex_lock (&s->ip->lock);
	ns = tcp_alloc (s->ip);
	if (ns == 0) {
		tcp_debug ("tcp_accept: could not allocate PCB\n");
		++s->ip->tcp_in_discards;
		mutex_unlock (&s->ip->lock);
		buf_free (p);
		goto again;
	}
	h = (tcp_hdr_t*) p->payload;
	iph = ((ip_hdr_t*) p->payload) - 1;

	/* Set up the new PCB. */
	memcpy (ns->local_ip, iph->dest, 4);
	ns->local_port = s->local_port;
	memcpy (ns->remote_ip, iph->src, 4);
	ns->remote_port = h->src;
	ns->state = SYN_RCVD;
	ns->rcv_nxt = s->ip->tcp_input_seqno + 1;
	ns->snd_wnd = h->wnd;
	ns->ssthresh = ns->snd_wnd;
	ns->snd_wl1 = s->ip->tcp_input_seqno;
	ns->ip = s->ip;

	/* Register the new PCB so that we can begin receiving
	 * segments for it. */
	tcp_list_add (&s->ip->tcp_sockets, ns);

	/* Parse any options in the SYN. */
	tcp_parseopt (ns, h);

	/* Build an MSS option. */
	optdata = HTONL (((unsigned long)2 << 24) | ((unsigned long)4 << 16) |
		(((unsigned long)ns->mss / 256) << 8) | (ns->mss & 255));
	buf_free (p);

	/* Send a SYN|ACK together with the MSS option. */
	tcp_enqueue (ns, 0, 0, TCP_SYN | TCP_ACK, (unsigned char*) &optdata, 4);
	tcp_output (ns);
	mutex_unlock (&s->ip->lock);
	return ns;
}