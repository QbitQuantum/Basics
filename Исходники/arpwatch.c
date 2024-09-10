void
process_fddi(register u_char *u, register const struct pcap_pkthdr *h,
    register const u_char *p)
{
	register struct fddi_header *fh;
	register struct ether_arp *ea;
	register u_char *sea, *sha;
	register time_t t;
	u_int32_t sia;

	fh = (struct fddi_header *)p;
	ea = (struct ether_arp *)(fh + 1);

	if (!swapped) {
		bit_reverse(fh->src, 6);
		bit_reverse(fh->dst, 6);
	}
	if (!sanity_fddi(fh, ea, h->caplen))
		return;

	/* Source MAC hardware ethernet address */
	sea = (u_char *)fh->src;

	/* Source ARP ethernet address */
	sha = (u_char *)SHA(ea);

	/* Source ARP ip address */
	BCOPY(SPA(ea), &sia, 4);

	/* Watch for bogons */
	if (isbogon(sia)) {
		dosyslog(LOG_INFO, "bogon", sia, sea, sha);
		return;
	}

	/* Watch for ethernet broadcast */
	if (MEMCMP(sea, zero, 6) == 0 || MEMCMP(sea, allones, 6) == 0 ||
	    MEMCMP(sha, zero, 6) == 0 || MEMCMP(sha, allones, 6) == 0) {
		dosyslog(LOG_INFO, "ethernet broadcast", sia, sea, sha);
		return;
	}

	/* Double check ethernet addresses */
	if (MEMCMP(sea, sha, 6) != 0) {
		dosyslog(LOG_INFO, "ethernet mismatch", sia, sea, sha);
		return;
	}

	/* Got a live one */
	t = h->ts.tv_sec;
	can_checkpoint = 0;
	if (!ent_add(sia, sea, t, NULL))
		syslog(LOG_ERR, "ent_add(%s, %s, %ld) failed",
		    intoa(sia), e2str(sea), t);
	can_checkpoint = 1;
}