static int
nflog_read_linux(pcap_t *handle, int max_packets, pcap_handler callback, u_char *user)
{
	const unsigned char *buf;
	int count = 0;
	int len;

	/* ignore interrupt system call error */
	do {
		len = recv(handle->fd, handle->buffer, handle->bufsize, 0);
		if (handle->break_loop) {
			handle->break_loop = 0;
			return -2;
		}
	} while ((len == -1) && (errno == EINTR));

	if (len < 0) {
		snprintf(handle->errbuf, PCAP_ERRBUF_SIZE, "Can't receive packet %d:%s", errno, pcap_strerror(errno));
		return -1;
	}

	buf = handle->buffer;
	while (len >= NLMSG_SPACE(0)) {
		const struct nlmsghdr *nlh = (const struct nlmsghdr *) buf;
		u_int32_t msg_len;

		if (nlh->nlmsg_len < sizeof(struct nlmsghdr) || len < nlh->nlmsg_len) {
			snprintf(handle->errbuf, PCAP_ERRBUF_SIZE, "Message truncated: (got: %d) (nlmsg_len: %u)", len, nlh->nlmsg_len);
			return -1;
		}

		if (NFNL_SUBSYS_ID(nlh->nlmsg_type) == NFNL_SUBSYS_ULOG && 
			NFNL_MSG_TYPE(nlh->nlmsg_type) == NFULNL_MSG_PACKET) 
		{
			const unsigned char *payload = NULL;
			struct pcap_pkthdr pkth;

			if (handle->linktype != DLT_NFLOG) {
				const struct nfattr *payload_attr = NULL;

				if (nlh->nlmsg_len < HDR_LENGTH) {
					snprintf(handle->errbuf, PCAP_ERRBUF_SIZE, "Malformed message: (nlmsg_len: %u)", nlh->nlmsg_len);
					return -1;
				}

				if (nlh->nlmsg_len > HDR_LENGTH) {
					struct nfattr *attr = NFM_NFA(NLMSG_DATA(nlh));
					int attr_len = nlh->nlmsg_len - NLMSG_ALIGN(HDR_LENGTH);

					while (NFA_OK(attr, attr_len)) {
						switch (NFA_TYPE(attr)) {
							case NFULA_PAYLOAD:
								payload_attr = attr;
								break;
						}
						attr = NFA_NEXT(attr, attr_len);
					}
				}

				if (payload_attr) {
					payload = NFA_DATA(payload_attr);
					pkth.len = pkth.caplen = NFA_PAYLOAD(payload_attr);
				}

			} else {
				payload = NLMSG_DATA(nlh);
				pkth.caplen = pkth.len = nlh->nlmsg_len-NLMSG_ALIGN(sizeof(struct nlmsghdr));
			}

			if (payload) {
				/* pkth.caplen = min (payload_len, handle->snapshot); */

				gettimeofday(&pkth.ts, NULL);
				if (handle->fcode.bf_insns == NULL ||
						bpf_filter(handle->fcode.bf_insns, payload, pkth.len, pkth.caplen)) 
				{
					handle->md.packets_read++;
					callback(user, &pkth, payload);
					count++;
				}
			}
		}

		msg_len = NLMSG_ALIGN(nlh->nlmsg_len);
		if (msg_len > len)
			msg_len = len;

		len -= msg_len;
		buf += msg_len;
	}
	return count;
}