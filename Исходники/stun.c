static int stun_test(const char *server_ip, uint16_t server_port,
		     uint16_t tun_port)
{
	int ret, sock, set = 1;
	uint8_t pkt[256];
	uint8_t rpkt[256];
	size_t len, off, max;
	struct in_addr in;
	struct timeval timeout;
	struct stun_header *hdr, *rhdr;
	struct stun_attrib *attr;
	struct stun_mapped_addr *addr;
	struct sockaddr_in saddr, daddr;
	fd_set fdset;

	if (!server_ip)
		return -EINVAL;

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0)
		panic("Cannot obtain socket!\n");

	ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &set, sizeof(set));
	if (ret)
		panic("Cannot set socket option!\n");

	saddr.sin_family = PF_INET;
	saddr.sin_port = htons(tun_port);
	saddr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sock, (struct sockaddr *) &saddr, sizeof(saddr));
	if (ret)
		panic("Cannot bind udp socket!\n");

	len = REQUEST_LEN;
	hdr = (struct stun_header *) pkt;
	hdr->type = htons(BINDING_REQUEST);
	hdr->len = 0;
	hdr->magic_cookie = ID_COOKIE_FIELD;
	hdr->transid[0] = htonl(rand());
	hdr->transid[1] = htonl(rand());
	hdr->transid[2] = htonl(rand());

	daddr.sin_family = PF_INET;
	daddr.sin_port = htons(server_port);
	daddr.sin_addr.s_addr = inet_addr(server_ip);

	ret = sendto(sock, pkt, len, 0, (struct sockaddr *) &daddr,
		     sizeof(daddr));
	if (ret != len) {
		whine("Error sending request (%s)!\n", strerror(errno));
		return -EIO;
	}

	set_timeout(&timeout, TIMEOUT);

	FD_ZERO(&fdset);
	FD_SET(sock, &fdset);

	ret = select(sock + 1, &fdset, NULL, NULL, &timeout);
	if (ret <= 0) {
		whine("STUN server timeout!\n");
		return -EIO;
	}

	memset(rpkt, 0, sizeof(rpkt));
	len = read(sock, rpkt, sizeof(rpkt));

	close(sock);

	if (len < REQUEST_LEN) {
		whine("Bad STUN response (%s)!\n", strerror(errno));
		return -EIO;
	}

	rhdr = (struct stun_header *) rpkt;
	if (ntohs(rhdr->type) != BINDING_RESPONSE) {
		whine("Wrong STUN response type!\n");
		return -EIO;
	}

	if (rhdr->len == 0) {
		whine("No attributes in STUN response!\n");
		return -EIO;
	}

	if (rhdr->magic_cookie != hdr->magic_cookie ||
	    rhdr->transid[0] != hdr->transid[0] ||
	    rhdr->transid[1] != hdr->transid[1] ||
	    rhdr->transid[2] != hdr->transid[2]) {
		whine("Got wrong STUN transaction id!\n");
		return -EIO;
	}

	off = REQUEST_LEN;
	max = ntohs(rhdr->len) + REQUEST_LEN;

	while (off + 8 < max) {
		attr = (struct stun_attrib *) (rpkt + off);
		if (ntohs(attr->type) != MAPPED_ADDRESS)
			goto next;

		addr = (struct stun_mapped_addr *) (rpkt + off + 4);
		if (addr->family != 0x1)
			break;

		in.s_addr = addr->ip;
		info("Public mapping %s:%u!\n", inet_ntoa(in), ntohs(addr->port));
		break;
next:
		off += 4;
		off += ntohs(attr->len);
	}

	return 0;
}