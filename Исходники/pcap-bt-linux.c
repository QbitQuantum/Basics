static int
bt_read_linux(pcap_t *handle, int max_packets, pcap_handler callback, u_char *user)
{
	struct cmsghdr *cmsg;
	struct msghdr msg;
	struct iovec  iv;
	ssize_t ret;
	struct pcap_pkthdr pkth;
	pcap_bluetooth_h4_header* bthdr;

	bthdr = (pcap_bluetooth_h4_header*) &handle->buffer[handle->offset];
	iv.iov_base = &handle->buffer[handle->offset+sizeof(pcap_bluetooth_h4_header)];
	iv.iov_len  = handle->snapshot;
	
	memset(&msg, 0, sizeof(msg));
	msg.msg_iov = &iv;
	msg.msg_iovlen = 1;
	msg.msg_control = handle->buffer;
	msg.msg_controllen = handle->offset;

	/* ignore interrupt system call error */
	do {
		ret = recvmsg(handle->fd, &msg, 0);
		if (handle->break_loop)
		{
			handle->break_loop = 0;
			return -2;
		}
	} while ((ret == -1) && (errno == EINTR));

	if (ret < 0) {
		snprintf(handle->errbuf, PCAP_ERRBUF_SIZE,
		    "Can't receive packet: %s", strerror(errno));
		return -1;
	}

	pkth.caplen = ret;

	/* get direction and timestamp*/ 
	cmsg = CMSG_FIRSTHDR(&msg);
	int in=0;
	while (cmsg) {
		switch (cmsg->cmsg_type) {
			case HCI_CMSG_DIR:
				memcpy(&in, CMSG_DATA(cmsg), sizeof in);
				break;
                      	case HCI_CMSG_TSTAMP:
                      		memcpy(&pkth.ts, CMSG_DATA(cmsg),
                      		    sizeof pkth.ts);
				break;
		}
		cmsg = CMSG_NXTHDR(&msg, cmsg);
	}
	if ((in && (handle->direction == PCAP_D_OUT)) || 
				((!in) && (handle->direction == PCAP_D_IN)))
		return 0;

	bthdr->direction = htonl(in != 0);
	pkth.caplen+=sizeof(pcap_bluetooth_h4_header);
	pkth.len = pkth.caplen;
	if (handle->fcode.bf_insns == NULL ||
	    bpf_filter(handle->fcode.bf_insns, &handle->buffer[handle->offset],
	      pkth.len, pkth.caplen)) {
		callback(user, &pkth, &handle->buffer[handle->offset]);
		return 1;
	}
	return 0;	/* didn't pass filter */
}