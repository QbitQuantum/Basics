static int
pcap_activate_nit(pcap_t *p)
{
	int fd;
	struct sockaddr_nit snit;

	if (p->opt.rfmon) {
		/*
		 * No monitor mode on SunOS 3.x or earlier (no
		 * Wi-Fi *devices* for the hardware that supported
		 * them!).
		 */
		return (PCAP_ERROR_RFMON_NOTSUP);
	}

	if (p->snapshot < 96)
		/*
		 * NIT requires a snapshot length of at least 96.
		 */
		p->snapshot = 96;

	memset(p, 0, sizeof(*p));
	p->fd = fd = socket(AF_NIT, SOCK_RAW, NITPROTO_RAW);
	if (fd < 0) {
		snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "socket: %s", pcap_strerror(errno));
		goto bad;
	}
	snit.snit_family = AF_NIT;
	(void)strncpy(snit.snit_ifname, p->opt.source, NITIFSIZ);

	if (bind(fd, (struct sockaddr *)&snit, sizeof(snit))) {
		snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "bind: %s: %s", snit.snit_ifname, pcap_strerror(errno));
		goto bad;
	}
	if (nit_setflags(p) < 0)
		goto bad;

	/*
	 * NIT supports only ethernets.
	 */
	p->linktype = DLT_EN10MB;

	p->bufsize = BUFSPACE;
	p->buffer = (u_char *)malloc(p->bufsize);
	if (p->buffer == NULL) {
		strlcpy(p->errbuf, pcap_strerror(errno), PCAP_ERRBUF_SIZE);
		goto bad;
	}

	/*
	 * "p->fd" is a socket, so "select()" should work on it.
	 */
	p->selectable_fd = p->fd;

	/*
	 * This is (presumably) a real Ethernet capture; give it a
	 * link-layer-type list with DLT_EN10MB and DLT_DOCSIS, so
	 * that an application can let you choose it, in case you're
	 * capturing DOCSIS traffic that a Cisco Cable Modem
	 * Termination System is putting out onto an Ethernet (it
	 * doesn't put an Ethernet header onto the wire, it puts raw
	 * DOCSIS frames out on the wire inside the low-level
	 * Ethernet framing).
	 */
	p->dlt_list = (u_int *) malloc(sizeof(u_int) * 2);
	/*
	 * If that fails, just leave the list empty.
	 */
	if (p->dlt_list != NULL) {
		p->dlt_list[0] = DLT_EN10MB;
		p->dlt_list[1] = DLT_DOCSIS;
		p->dlt_count = 2;
	}

	p->read_op = pcap_read_nit;
	p->inject_op = pcap_inject_nit;
	p->setfilter_op = install_bpf_program;	/* no kernel filtering */
	p->setdirection_op = NULL;	/* Not implemented. */
	p->set_datalink_op = NULL;	/* can't change data link type */
	p->getnonblock_op = pcap_getnonblock_fd;
	p->setnonblock_op = pcap_setnonblock_fd;
	p->stats_op = pcap_stats_nit;

	return (0);
 bad:
	pcap_cleanup_live_common(p);
	return (PCAP_ERROR);
}