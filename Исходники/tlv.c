static int nsm_resp_post_recv(struct tlv_extra *extra)
{
	struct nsm_resp_tlv_head *head;
	struct TLV *tlv = extra->tlv;
	struct timePropertiesDS *tp;
	struct PortAddress *paddr;
	struct currentDS *cds;
	struct parentDS *pds;
	unsigned char *ptr;
	uint16_t expected;

	if (tlv->length < sizeof(*head) + sizeof(*extra->foot)
	    - sizeof(head->type) - sizeof(head->length)) {
		return -EBADMSG;
	}
	head = (struct nsm_resp_tlv_head *) tlv;
	paddr = &head->parent_addr;
	NTOHS(paddr->networkProtocol);
	NTOHS(paddr->addressLength);

	switch (paddr->networkProtocol) {
	case TRANS_UDP_IPV4:
		expected = 4;
		break;
	case TRANS_UDP_IPV6:
		expected = 16;
		break;
	case TRANS_IEEE_802_3:
		expected = 6;
		break;
	default:
		return -EBADMSG;
	}
	if (paddr->addressLength != expected) {
		return -EBADMSG;
	}
	if (tlv->length != sizeof(*head) + sizeof(*extra->foot) +
	    paddr->addressLength - sizeof(head->type) - sizeof(head->length)) {
		return -EBADMSG;
	}

	ptr = (unsigned char *) tlv;
	ptr += sizeof(*head) + paddr->addressLength;
	extra->foot = (struct nsm_resp_tlv_foot *) ptr;

	pds = &extra->foot->parent;
	cds = &extra->foot->current;
	tp = &extra->foot->timeprop;

	/*
	 * At this point the alignment only 2 bytes worst case.
	 * So we need to be careful with the 64 bit words.
	 */
	NTOHS(pds->parentPortIdentity.portNumber);
	NTOHS(pds->observedParentOffsetScaledLogVariance);
	NTOHL(pds->observedParentClockPhaseChangeRate);
	NTOHS(pds->grandmasterClockQuality.offsetScaledLogVariance);

	NTOHS(cds->stepsRemoved);
	net2host64_unaligned(&cds->offsetFromMaster);
	net2host64_unaligned(&cds->meanPathDelay);

	NTOHS(tp->currentUtcOffset);

	NTOHL(extra->foot->lastsync.seconds_lsb);
	NTOHS(extra->foot->lastsync.seconds_msb);
	NTOHL(extra->foot->lastsync.nanoseconds);

	return 0;
}