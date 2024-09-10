/*
 * check validity of a router renumbering command packet
 * return 0 on success, 1 on failure
 */
static int
rr_command_check(int len, struct icmp6_router_renum *rr, struct in6_addr *from,
		 struct in6_addr *dst)
{
	char ntopbuf[INET6_ADDRSTRLEN];

	/* omit rr minimal length check. hope kernel have done it. */
	/* rr_command length check */
	if (len < (sizeof(struct icmp6_router_renum) +
		   sizeof(struct rr_pco_match))) {
		syslog(LOG_ERR,	"<%s> rr_command len %d is too short",
		       __func__, len);
		return 1;
	}

	/* destination check. only for multicast. omit unicast check. */
	if (IN6_IS_ADDR_MULTICAST(dst) && !IN6_IS_ADDR_MC_LINKLOCAL(dst) &&
	    !IN6_IS_ADDR_MC_SITELOCAL(dst)) {
		syslog(LOG_ERR,	"<%s> dst mcast addr %s is illegal",
		       __func__,
		       inet_ntop(AF_INET6, dst, ntopbuf, INET6_ADDRSTRLEN));
		return 1;
	}

	/* seqnum and segnum check */
	if (rro.rro_seqnum > rr->rr_seqnum) {
		syslog(LOG_WARNING,
		       "<%s> rcvd old seqnum %d from %s",
		       __func__, (u_int32_t)ntohl(rr->rr_seqnum),
		       inet_ntop(AF_INET6, from, ntopbuf, INET6_ADDRSTRLEN));
		return 1;
	}
	if (rro.rro_seqnum == rr->rr_seqnum &&
	    (rr->rr_flags & ICMP6_RR_FLAGS_TEST) == 0 &&
	    RR_ISSET_SEGNUM(rro.rro_segnum_bits, rr->rr_segnum)) {
		if ((rr->rr_flags & ICMP6_RR_FLAGS_REQRESULT) != 0)
			syslog(LOG_WARNING,
			       "<%s> rcvd duped segnum %d from %s",
			       __func__, rr->rr_segnum,
			       inet_ntop(AF_INET6, from, ntopbuf,
					 INET6_ADDRSTRLEN));
		return 0;
	}

	/* update seqnum */
	if (rro.rro_seqnum != rr->rr_seqnum) {
		/* then must be "<" */

		/* init rro_segnum_bits */
		memset(rro.rro_segnum_bits, 0,
		       sizeof(rro.rro_segnum_bits));
	}
	rro.rro_seqnum = rr->rr_seqnum;

	return 0;
}