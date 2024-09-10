/* This handshake handler waits a PROXY protocol header at the beginning of the
 * raw data stream. The header looks like this :
 *
 *   "PROXY" <SP> PROTO <SP> SRC3 <SP> DST3 <SP> SRC4 <SP> <DST4> "\r\n"
 *
 * There must be exactly one space between each field. Fields are :
 *  - PROTO : layer 4 protocol, which must be "TCP4" or "TCP6".
 *  - SRC3  : layer 3 (eg: IP) source address in standard text form
 *  - DST3  : layer 3 (eg: IP) destination address in standard text form
 *  - SRC4  : layer 4 (eg: TCP port) source address in standard text form
 *  - DST4  : layer 4 (eg: TCP port) destination address in standard text form
 *
 * This line MUST be at the beginning of the buffer and MUST NOT wrap.
 *
 * The header line is small and in all cases smaller than the smallest normal
 * TCP MSS. So it MUST always be delivered as one segment, which ensures we
 * can safely use MSG_PEEK and avoid buffering.
 *
 * Once the data is fetched, the values are set in the connection's address
 * fields, and data are removed from the socket's buffer. The function returns
 * zero if it needs to wait for more data or if it fails, or 1 if it completed
 * and removed itself.
 */
int conn_recv_proxy(struct connection *conn, int flag)
{
	char *line, *end;
	struct proxy_hdr_v2 *hdr_v2;
	const char v2sig[] = PP2_SIGNATURE;
	int tlv_length = 0;
	int tlv_offset = 0;

	/* we might have been called just after an asynchronous shutr */
	if (conn->flags & CO_FL_SOCK_RD_SH)
		goto fail;

	if (!conn_ctrl_ready(conn))
		goto fail;

	if (!fd_recv_ready(conn->t.sock.fd))
		return 0;

	do {
		trash.len = recv(conn->t.sock.fd, trash.str, trash.size, MSG_PEEK);
		if (trash.len < 0) {
			if (errno == EINTR)
				continue;
			if (errno == EAGAIN) {
				fd_cant_recv(conn->t.sock.fd);
				return 0;
			}
			goto recv_abort;
		}
	} while (0);

	if (!trash.len) {
		/* client shutdown */
		conn->err_code = CO_ER_PRX_EMPTY;
		goto fail;
	}

	if (trash.len < 6)
		goto missing;

	line = trash.str;
	end = trash.str + trash.len;

	/* Decode a possible proxy request, fail early if it does not match */
	if (strncmp(line, "PROXY ", 6) != 0)
		goto not_v1;

	line += 6;
	if (trash.len < 9) /* shortest possible line */
		goto missing;

	if (memcmp(line, "TCP4 ", 5) == 0) {
		u32 src3, dst3, sport, dport;

		line += 5;

		src3 = inetaddr_host_lim_ret(line, end, &line);
		if (line == end)
			goto missing;
		if (*line++ != ' ')
			goto bad_header;

		dst3 = inetaddr_host_lim_ret(line, end, &line);
		if (line == end)
			goto missing;
		if (*line++ != ' ')
			goto bad_header;

		sport = read_uint((const char **)&line, end);
		if (line == end)
			goto missing;
		if (*line++ != ' ')
			goto bad_header;

		dport = read_uint((const char **)&line, end);
		if (line > end - 2)
			goto missing;
		if (*line++ != '\r')
			goto bad_header;
		if (*line++ != '\n')
			goto bad_header;

		/* update the session's addresses and mark them set */
		((struct sockaddr_in *)&conn->addr.from)->sin_family      = AF_INET;
		((struct sockaddr_in *)&conn->addr.from)->sin_addr.s_addr = htonl(src3);
		((struct sockaddr_in *)&conn->addr.from)->sin_port        = htons(sport);

		((struct sockaddr_in *)&conn->addr.to)->sin_family        = AF_INET;
		((struct sockaddr_in *)&conn->addr.to)->sin_addr.s_addr   = htonl(dst3);
		((struct sockaddr_in *)&conn->addr.to)->sin_port          = htons(dport);
		conn->flags |= CO_FL_ADDR_FROM_SET | CO_FL_ADDR_TO_SET;
	}
	else if (memcmp(line, "TCP6 ", 5) == 0) {
		u32 sport, dport;
		char *src_s;
		char *dst_s, *sport_s, *dport_s;
		struct in6_addr src3, dst3;

		line += 5;

		src_s = line;
		dst_s = sport_s = dport_s = NULL;
		while (1) {
			if (line > end - 2) {
				goto missing;
			}
			else if (*line == '\r') {
				*line = 0;
				line++;
				if (*line++ != '\n')
					goto bad_header;
				break;
			}

			if (*line == ' ') {
				*line = 0;
				if (!dst_s)
					dst_s = line + 1;
				else if (!sport_s)
					sport_s = line + 1;
				else if (!dport_s)
					dport_s = line + 1;
			}
			line++;
		}

		if (!dst_s || !sport_s || !dport_s)
			goto bad_header;

		sport = read_uint((const char **)&sport_s,dport_s - 1);
		if (*sport_s != 0)
			goto bad_header;

		dport = read_uint((const char **)&dport_s,line - 2);
		if (*dport_s != 0)
			goto bad_header;

		if (inet_pton(AF_INET6, src_s, (void *)&src3) != 1)
			goto bad_header;

		if (inet_pton(AF_INET6, dst_s, (void *)&dst3) != 1)
			goto bad_header;

		/* update the session's addresses and mark them set */
		((struct sockaddr_in6 *)&conn->addr.from)->sin6_family      = AF_INET6;
		memcpy(&((struct sockaddr_in6 *)&conn->addr.from)->sin6_addr, &src3, sizeof(struct in6_addr));
		((struct sockaddr_in6 *)&conn->addr.from)->sin6_port        = htons(sport);

		((struct sockaddr_in6 *)&conn->addr.to)->sin6_family        = AF_INET6;
		memcpy(&((struct sockaddr_in6 *)&conn->addr.to)->sin6_addr, &dst3, sizeof(struct in6_addr));
		((struct sockaddr_in6 *)&conn->addr.to)->sin6_port          = htons(dport);
		conn->flags |= CO_FL_ADDR_FROM_SET | CO_FL_ADDR_TO_SET;
	}
	else if (memcmp(line, "UNKNOWN\r\n", 9) == 0) {
		/* This can be a UNIX socket forwarded by an haproxy upstream */
		line += 9;
	}
	else {
		/* The protocol does not match something known (TCP4/TCP6/UNKNOWN) */
		conn->err_code = CO_ER_PRX_BAD_PROTO;
		goto fail;
	}

	trash.len = line - trash.str;
	goto eat_header;

 not_v1:
	/* try PPv2 */
	if (trash.len < PP2_HEADER_LEN)
		goto missing;

	hdr_v2 = (struct proxy_hdr_v2 *)trash.str;

	if (memcmp(hdr_v2->sig, v2sig, PP2_SIGNATURE_LEN) != 0 ||
	    (hdr_v2->ver_cmd & PP2_VERSION_MASK) != PP2_VERSION) {
		conn->err_code = CO_ER_PRX_NOT_HDR;
		goto fail;
	}

	if (trash.len < PP2_HEADER_LEN + ntohs(hdr_v2->len))
		goto missing;

	switch (hdr_v2->ver_cmd & PP2_CMD_MASK) {
	case 0x01: /* PROXY command */
		switch (hdr_v2->fam) {
		case 0x11:  /* TCPv4 */
			if (ntohs(hdr_v2->len) < PP2_ADDR_LEN_INET)
				goto bad_header;

			((struct sockaddr_in *)&conn->addr.from)->sin_family = AF_INET;
			((struct sockaddr_in *)&conn->addr.from)->sin_addr.s_addr = hdr_v2->addr.ip4.src_addr;
			((struct sockaddr_in *)&conn->addr.from)->sin_port = hdr_v2->addr.ip4.src_port;
			((struct sockaddr_in *)&conn->addr.to)->sin_family = AF_INET;
			((struct sockaddr_in *)&conn->addr.to)->sin_addr.s_addr = hdr_v2->addr.ip4.dst_addr;
			((struct sockaddr_in *)&conn->addr.to)->sin_port = hdr_v2->addr.ip4.dst_port;
			conn->flags |= CO_FL_ADDR_FROM_SET | CO_FL_ADDR_TO_SET;
			tlv_offset = PP2_HEADER_LEN + PP2_ADDR_LEN_INET;
			tlv_length = ntohs(hdr_v2->len) - PP2_ADDR_LEN_INET;
			break;
		case 0x21:  /* TCPv6 */
			if (ntohs(hdr_v2->len) < PP2_ADDR_LEN_INET6)
				goto bad_header;

			((struct sockaddr_in6 *)&conn->addr.from)->sin6_family = AF_INET6;
			memcpy(&((struct sockaddr_in6 *)&conn->addr.from)->sin6_addr, hdr_v2->addr.ip6.src_addr, 16);
			((struct sockaddr_in6 *)&conn->addr.from)->sin6_port = hdr_v2->addr.ip6.src_port;
			((struct sockaddr_in6 *)&conn->addr.to)->sin6_family = AF_INET6;
			memcpy(&((struct sockaddr_in6 *)&conn->addr.to)->sin6_addr, hdr_v2->addr.ip6.dst_addr, 16);
			((struct sockaddr_in6 *)&conn->addr.to)->sin6_port = hdr_v2->addr.ip6.dst_port;
			conn->flags |= CO_FL_ADDR_FROM_SET | CO_FL_ADDR_TO_SET;
			tlv_offset = PP2_HEADER_LEN + PP2_ADDR_LEN_INET6;
			tlv_length = ntohs(hdr_v2->len) - PP2_ADDR_LEN_INET6;
			break;
		}

		/* TLV parsing */
		if (tlv_length > 0) {
			while (tlv_offset + TLV_HEADER_SIZE <= trash.len) {
				const struct tlv *tlv_packet = (struct tlv *) &trash.str[tlv_offset];
				const int tlv_len = get_tlv_length(tlv_packet);
				tlv_offset += tlv_len + TLV_HEADER_SIZE;

				switch (tlv_packet->type) {
#ifdef CONFIG_HAP_NS
				case PP2_TYPE_NETNS: {
					const struct netns_entry *ns;
					ns = netns_store_lookup((char*)tlv_packet->value, tlv_len);
					if (ns)
						conn->proxy_netns = ns;
					break;
				}
#endif
				default:
					break;
				}
			}
		}

		/* unsupported protocol, keep local connection address */
		break;
	case 0x00: /* LOCAL command */
		/* keep local connection address for LOCAL */
		break;
	default:
		goto bad_header; /* not a supported command */
	}

	trash.len = PP2_HEADER_LEN + ntohs(hdr_v2->len);
	goto eat_header;

 eat_header:
	/* remove the PROXY line from the request. For this we re-read the
	 * exact line at once. If we don't get the exact same result, we
	 * fail.
	 */
	do {
		int len2 = recv(conn->t.sock.fd, trash.str, trash.len, 0);
		if (len2 < 0 && errno == EINTR)
			continue;
		if (len2 != trash.len)
			goto recv_abort;
	} while (0);

	conn->flags &= ~flag;
	return 1;

 missing:
	/* Missing data. Since we're using MSG_PEEK, we can only poll again if
	 * we have not read anything. Otherwise we need to fail because we won't
	 * be able to poll anymore.
	 */
	conn->err_code = CO_ER_PRX_TRUNCATED;
	goto fail;

 bad_header:
	/* This is not a valid proxy protocol header */
	conn->err_code = CO_ER_PRX_BAD_HDR;
	goto fail;

 recv_abort:
	conn->err_code = CO_ER_PRX_ABORT;
	conn->flags |= CO_FL_SOCK_RD_SH | CO_FL_SOCK_WR_SH;
	goto fail;

 fail:
	__conn_sock_stop_both(conn);
	conn->flags |= CO_FL_ERROR;
	return 0;
}