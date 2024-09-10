static int
dhcp_get_offer(struct dhcp_context * context, int wait_ticks)
{
    int				error = 0;
    int	 			gather_count = 0;
    const struct in_addr * 	ip;
    int				last_rating = 0;
    int				len;
    int				n;
    int 			rating;
    struct dhcp *		reply;
    struct in_addr		server_id;
    struct socket * 		timer_arg;

    timer_arg = context->so;
    reply = dhcp_context_reply(context);
    timeout((timeout_fcn_t)dhcp_timeout, &timer_arg, wait_ticks);
    while (1) {
	error = receive_packet(context->so, context->reply,
			       sizeof(context->reply), &n);
	if (error == 0) {
	    dhcpol_t		options;

	    dprintf(("\ndhcp: received packet length %d\n", n));
	    if (n < (int)sizeof(struct dhcp)) {
		dprintf(("dhcp: packet is too short %d < %d\n",
			 n, (int)sizeof(struct dhcp)));
		continue;
	    }
	    if (ntohl(reply->dp_xid) != context->xid
		|| reply->dp_yiaddr.s_addr == 0
		|| reply->dp_yiaddr.s_addr == INADDR_BROADCAST
		|| bcmp(reply->dp_chaddr,
			link_address(context->dl_p), 
			link_address_length(context->dl_p)) != 0) {
		/* not for us */
		continue;
	    }
	    (void)dhcpol_parse_packet(&options, reply, n);
	    if (get_dhcp_msgtype(&options) != dhcp_msgtype_offer_e) {
		/* not an offer */
		goto next_packet;
	    }
	    ip = (const struct in_addr *)
		dhcpol_find(&options, 
			    dhcptag_server_identifier_e, &len, NULL);
	    if (ip == NULL || len < (int)sizeof(*ip)) {
		/* missing/invalid server identifier */
		goto next_packet;
	    }
	    printf("dhcp: received OFFER: server " IP_FORMAT
		   " IP address "  IP_FORMAT "\n",
		   IP_LIST(ip), IP_LIST(&reply->dp_yiaddr));
	    server_id = *ip;
	    rating = rate_packet(&options);
	    if (rating > last_rating) {
		context->iaddr = reply->dp_yiaddr;
		ip = (const struct in_addr *)
		    dhcpol_find(&options, 
				dhcptag_subnet_mask_e, &len, NULL);
		if (ip != NULL && len >= (int)sizeof(*ip)) {
		    context->netmask = *ip;
		}
		ip = (const struct in_addr *)
		    dhcpol_find(&options, dhcptag_router_e, &len, NULL);
		if (ip != NULL && len >= (int)sizeof(*ip)) {
		    context->router = *ip;
		}
		context->server_id = server_id;
	    }
	    if (rating >= GOOD_RATING) {
		dhcpol_free(&options);
		/* packet is good enough */
		untimeout((timeout_fcn_t)dhcp_timeout, &timer_arg);
		break;
	    }
	    if (gather_count == 0) {
		untimeout((timeout_fcn_t)dhcp_timeout, &timer_arg);
		timer_arg = context->so;
		timeout((timeout_fcn_t)dhcp_timeout, &timer_arg, 
			hz * GATHER_TIME_SECS);
	    }
	    gather_count = 1;
	next_packet:
	    dhcpol_free(&options);
	}
	else if ((error != EWOULDBLOCK)) {
	    untimeout((timeout_fcn_t)dhcp_timeout, &timer_arg);
	    break;
	}
	else if (timer_arg == NULL) { /* timed out */
	    if (gather_count != 0) {
		dprintf(("dhcp: gathering time has expired\n"));
		error = 0;
	    }
	    break;
	}
	else {
	    socket_lock(context->so, 1);
	    error = sbwait(&context->so->so_rcv);
	    socket_unlock(context->so, 1);
	}
    }
    return (error);
}