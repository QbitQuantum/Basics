static void rs_packet_process(uint64_t count, rs_event_t *event, struct pcap_pkthdr const *header, uint8_t const *data)
{
	rs_stats_t		*stats = event->stats;
	struct timeval		elapsed;
	struct timeval		latency;

	/*
	 *	Pointers into the packet data we just received
	 */
	size_t len;
	uint8_t const		*p = data;
	struct ip_header const	*ip = NULL;	/* The IP header */
	struct ip_header6 const	*ip6 = NULL;	/* The IPv6 header */
	struct udp_header const	*udp;		/* The UDP header */
	uint8_t			version;	/* IP header version */
	bool			response;	/* Was it a response code */

	decode_fail_t		reason;		/* Why we failed decoding the packet */
	static uint64_t		captured = 0;

	RADIUS_PACKET *current;			/* Current packet were processing */
	rs_request_t *original;

	if (!start_pcap.tv_sec) {
		start_pcap = header->ts;
	}

	if (header->caplen <= 5) {
		INFO("Packet too small, captured %i bytes", header->caplen);
		return;
	}

	/*
	 *	Loopback header
	 */
	if ((p[0] == 2) && (p[1] == 0) && (p[2] == 0) && (p[3] == 0)) {
		p += 4;
	/*
	 *	Ethernet header
	 */
	} else {
		p += sizeof(struct ethernet_header);
	}

	version = (p[0] & 0xf0) >> 4;
	switch (version) {
	case 4:
		ip = (struct ip_header const *)p;
		len = (0x0f & ip->ip_vhl) * 4;	/* ip_hl specifies length in 32bit words */
		p += len;
		break;

	case 6:
		ip6 = (struct ip_header6 const *)p;
		p += sizeof(struct ip_header6);

		break;

	default:
		DEBUG("IP version invalid %i", version);
		return;
	}

	/*
	 *	End of variable length bits, do basic check now to see if packet looks long enough
	 */
	len = (p - data) + sizeof(struct udp_header) + (sizeof(radius_packet_t) - 1);	/* length value */
	if (len > header->caplen) {
		DEBUG("Packet too small, we require at least %zu bytes, captured %i bytes",
		      (size_t) len, header->caplen);
		return;
	}

	udp = (struct udp_header const *)p;
	p += sizeof(struct udp_header);

	/*
	 *	With artificial talloc memory limits there's a good chance we can
	 *	recover once some requests timeout, so make an effort to deal
	 *	with allocation failures gracefully.
	 */
	current = rad_alloc(conf, 0);
	if (!current) {
		ERROR("Failed allocating memory to hold decoded packet");
		rs_tv_add_ms(&header->ts, conf->stats.timeout, &stats->quiet);
		return;
	}
	current->timestamp = header->ts;
	current->data_len = header->caplen - (p - data);
	memcpy(&current->data, &p, sizeof(current->data));

	/*
	 *	Populate IP/UDP fields from PCAP data
	 */
	if (ip) {
		current->src_ipaddr.af = AF_INET;
		current->src_ipaddr.ipaddr.ip4addr.s_addr = ip->ip_src.s_addr;

		current->dst_ipaddr.af = AF_INET;
		current->dst_ipaddr.ipaddr.ip4addr.s_addr = ip->ip_dst.s_addr;
	} else {
		current->src_ipaddr.af = AF_INET6;
		memcpy(&current->src_ipaddr.ipaddr.ip6addr.s6_addr, &ip6->ip_src.s6_addr,
		       sizeof(current->src_ipaddr.ipaddr.ip6addr.s6_addr));

		current->dst_ipaddr.af = AF_INET6;
		memcpy(&current->dst_ipaddr.ipaddr.ip6addr.s6_addr, &ip6->ip_dst.s6_addr,
		       sizeof(current->dst_ipaddr.ipaddr.ip6addr.s6_addr));
	}

	current->src_port = ntohs(udp->udp_sport);
	current->dst_port = ntohs(udp->udp_dport);

	if (!rad_packet_ok(current, 0, &reason)) {
		RIDEBUG("(%" PRIu64 ") ** %s **", count, fr_strerror());
		RIDEBUG("(%" PRIu64 ") %s Id %i %s:%s:%d -> %s:%d\t+%u.%03u", count,
			fr_packet_codes[current->code], current->id,
			event->in->name,
			fr_inet_ntop(current->src_ipaddr.af, &current->src_ipaddr.ipaddr), current->src_port,
			fr_inet_ntop(current->dst_ipaddr.af, &current->dst_ipaddr.ipaddr), current->dst_port,
			(unsigned int) elapsed.tv_sec, ((unsigned int) elapsed.tv_usec / 1000));

		rad_free(&current);
		return;
	}

	switch (current->code) {
	case PW_CODE_ACCOUNTING_RESPONSE:
	case PW_CODE_AUTHENTICATION_REJECT:
	case PW_CODE_AUTHENTICATION_ACK:
	case PW_CODE_COA_NAK:
	case PW_CODE_COA_ACK:
	case PW_CODE_DISCONNECT_NAK:
	case PW_CODE_DISCONNECT_ACK:
	case PW_CODE_STATUS_CLIENT:
		{
			rs_request_t search;
			struct timeval when;

			rs_tv_add_ms(&header->ts, conf->stats.timeout, &when);

			/* look for a matching request and use it for decoding */
			search.packet = current;
			original = rbtree_finddata(request_tree, &search);

			/*
			 *	Only decode attributes if we want to print them or filter on them
			 *	rad_packet_ok does checks to verify the packet is actually valid.
			 */
			if (filter_vps || conf->print_packet) {
				if (rad_decode(current, original ? original->packet : NULL,
					       conf->radius_secret) != 0) {
					rad_free(&current);
					fr_perror("decode");
					return;
				}
			}

			/*
			 *	Check if we've managed to link it to a request
			 */
			if (original) {
				/*
				 *	Is this a retransmit?
				 */
				if (!original->linked) {
					original->stats_rsp = &stats->exchange[current->code];
				} else {
					RDEBUG("(%" PRIu64 ") ** RETRANSMISSION **", count);
					original->rt_rsp++;

					rad_free(&original->linked);
					fr_event_delete(event->list, &original->event);
				}

				original->linked = talloc_steal(original, current);

				/*
				 *	Some RADIUS servers and proxy servers may not cache
				 *	Accounting-Responses (and possibly other code),
				 *	and may immediately re-use a RADIUS packet src
				 *	port/id combination on receipt of a response.
				 */
				if (conf->dequeue[current->code]) {
					fr_event_delete(event->list, &original->event);
					rbtree_deletebydata(request_tree, original);
				} else {
					if (!fr_event_insert(event->list, rs_packet_cleanup, original, &when,
						    	     &original->event)) {
						ERROR("Failed inserting new event");
						/*
						 *	Delete the original request/event, it's no longer valid
						 *	for statistics.
						 */
						original->forced_cleanup = true;
						fr_event_delete(event->list, &original->event);
						rbtree_deletebydata(request_tree, original);

						return;
					}
				}
			/*
			 *	No request seen, or request was dropped by attribute filter
			 */
			} else {
				/*
				 *	If filter_vps are set assume the original request was dropped,
				 *	the alternative is maintaining another 'filter', but that adds
				 *	complexity, reduces max capture rate, and is generally a PITA.
				 */
				if (filter_vps) {
					rad_free(&current);
					RDEBUG2("(%" PRIu64 ") Dropped by attribute filter", count);
					return;
				}

				RDEBUG("(%" PRIu64 ") ** UNLINKED **", count);
				stats->exchange[current->code].interval.unlinked_total++;
			}

			response = true;
		}
			break;
	case PW_CODE_ACCOUNTING_REQUEST:
	case PW_CODE_AUTHENTICATION_REQUEST:
	case PW_CODE_COA_REQUEST:
	case PW_CODE_DISCONNECT_REQUEST:
	case PW_CODE_STATUS_SERVER:
		{
			rs_request_t search;
			struct timeval when;

			/*
			 *	Only decode attributes if we want to print them or filter on them
			 *	rad_packet_ok does checks to verify the packet is actually valid.
			 */
			if (filter_vps || conf->print_packet) {
				if (rad_decode(current, NULL, conf->radius_secret) != 0) {
					rad_free(&current);
					fr_perror("decode");
					return;
				}
			}

			/*
			 *	Now verify the packet passes the attribute filter
			 */
			if (filter_vps && !pairvalidate_relaxed(filter_vps, current->vps)) {
				rad_free(&current);
				RDEBUG2("(%" PRIu64 ") Dropped by attribute filter", count);
				return;
			}

			/*
			 *	save the request for later matching
			 */
			search.packet = rad_alloc_reply(conf, current);
			if (!search.packet) {
				ERROR("Failed allocating memory to hold expected reply");
				rs_tv_add_ms(&header->ts, conf->stats.timeout, &stats->quiet);
				rad_free(&current);
				return;
			}
			search.packet->code = current->code;

			rs_tv_add_ms(&header->ts, conf->stats.timeout, &when);

			original = rbtree_finddata(request_tree, &search);

			/*
			 *	Upstream device re-used src/dst ip/port id without waiting
			 *	for the timeout period to expire, or a response.
			 */
			if (original && memcmp(original->packet->vector, current->vector,
					       sizeof(original->packet->vector) != 0)) {
				RDEBUG2("(%" PRIu64 ") ** PREMATURE ID RE-USE **", count);
				stats->exchange[current->code].interval.reused_total++;
				original->forced_cleanup = true;

				fr_event_delete(event->list, &original->event);
				rbtree_deletebydata(request_tree, original);
				original = NULL;
			}

			if (original) {
				RDEBUG("(%" PRIu64 ") ** RETRANSMISSION **", count);
				original->rt_req++;

				rad_free(&original->packet);
				original->packet = talloc_steal(original, search.packet);

				/* We may of seen the response, but it may of been lost upstream */
				rad_free(&original->linked);
				fr_event_delete(event->list, &original->event);
			} else {
				original = talloc_zero(conf, rs_request_t);
				talloc_set_destructor(original, _request_free);

				original->id = count;
				original->in = event->in;
				original->stats_req = &stats->exchange[current->code];
				original->packet = talloc_steal(original, search.packet);

				rbtree_insert(request_tree, original);
			}

			/* update the timestamp in either case */
			original->packet->timestamp = header->ts;

			if (!fr_event_insert(event->list, rs_packet_cleanup, original, &when, &original->event)) {
				ERROR("Failed inserting new event");
				rbtree_deletebydata(request_tree, original);

				return;
			}
			response = false;
		}
			break;
		default:
			RDEBUG("** Unsupported code %i **", current->code);
			rad_free(&current);

			return;
	}

	if (event->out) {
		pcap_dump((void *) (event->out->dumper), header, data);
	}

	rs_tv_sub(&header->ts, &start_pcap, &elapsed);

	/*
	 *	Increase received count
	 */
	stats->exchange[current->code].interval.received_total++;

	/*
	 *	It's a linked response
	 */
	if (original && original->linked) {
		rs_tv_sub(&current->timestamp, &original->packet->timestamp, &latency);

		/*
		 *	Update stats for both the request and response types.
		 *
		 *	This isn't useful for things like Access-Requests, but will be useful for
		 *	CoA and Disconnect Messages, as we get the average latency across both
		 *	response types.
		 *
		 *	It also justifies allocating 255 instances rs_latency_t.
		 */
		rs_stats_update_latency(&stats->exchange[current->code], &latency);
		rs_stats_update_latency(&stats->exchange[original->packet->code], &latency);


		/*
		 *	Print info about the request/response.
		 */
		RIDEBUG("(%" PRIu64 ") %s Id %i %s:%s:%d %s %s:%d\t+%u.%03u\t+%u.%03u", count,
			fr_packet_codes[current->code], current->id,
			event->in->name,
			fr_inet_ntop(current->src_ipaddr.af, &current->src_ipaddr.ipaddr), current->src_port,
			response ? "<-" : "->",
			fr_inet_ntop(current->dst_ipaddr.af, &current->dst_ipaddr.ipaddr), current->dst_port,
			(unsigned int) elapsed.tv_sec, ((unsigned int) elapsed.tv_usec / 1000),
			(unsigned int) latency.tv_sec, ((unsigned int) latency.tv_usec / 1000));
	/*
	 *	It's the original request
	 */
	} else {
		/*
		 *	Print info about the request
		 */
		RIDEBUG("(%" PRIu64 ") %s Id %i %s:%s:%d %s %s:%d\t+%u.%03u", count,
			fr_packet_codes[current->code], current->id,
			event->in->name,
			fr_inet_ntop(current->src_ipaddr.af, &current->src_ipaddr.ipaddr), current->src_port,
			response ? "<-" : "->",
			fr_inet_ntop(current->dst_ipaddr.af, &current->dst_ipaddr.ipaddr), current->dst_port,
			(unsigned int) elapsed.tv_sec, ((unsigned int) elapsed.tv_usec / 1000));
	}

	if (conf->print_packet && (fr_debug_flag > 1) && current->vps) {
		pairsort(&current->vps, true);
		vp_printlist(log_dst, current->vps);
		pairfree(&current->vps);
	}

	if (!conf->to_stdout && (fr_debug_flag > 4)) {
		rad_print_hex(current);
	}

	fflush(log_dst);

	/*
	 *	If it's a request, a duplicate of the packet will of already been stored.
	 *	If it's a unlinked response, we need to free it explicitly, as it will
	 *	not be done by the event queue.
	 */
	if (!response || !original) {
		rad_free(&current);
	}

	captured++;
	/*
	 *	We've hit our capture limit, break out of the event loop
	 */
	if ((conf->limit > 0) && (captured >= conf->limit)) {
		INFO("Captured %" PRIu64 " packets, exiting...", captured);
		fr_event_loop_exit(events, 1);
	}
}