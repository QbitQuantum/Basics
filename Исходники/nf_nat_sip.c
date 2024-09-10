/* So, this packet has hit the connection tracking matching code.
   Mangle it, and change the expectation to match the new version. */
static unsigned int ip_nat_sdp_media(struct sk_buff *skb, unsigned int dataoff,
				     const char **dptr, unsigned int *datalen,
				     struct nf_conntrack_expect *rtp_exp,
				     struct nf_conntrack_expect *rtcp_exp,
				     unsigned int mediaoff,
				     unsigned int medialen,
				     union nf_inet_addr *rtp_addr)
{
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	enum ip_conntrack_dir dir = CTINFO2DIR(ctinfo);
	u_int16_t port;

	/* Connection will come from reply */
	if (ct->tuplehash[dir].tuple.src.u3.ip ==
	    ct->tuplehash[!dir].tuple.dst.u3.ip)
		rtp_addr->ip = rtp_exp->tuple.dst.u3.ip;
	else
		rtp_addr->ip = ct->tuplehash[!dir].tuple.dst.u3.ip;

	rtp_exp->saved_ip = rtp_exp->tuple.dst.u3.ip;
	rtp_exp->tuple.dst.u3.ip = rtp_addr->ip;
	rtp_exp->saved_proto.udp.port = rtp_exp->tuple.dst.u.udp.port;
	rtp_exp->dir = !dir;
	rtp_exp->expectfn = ip_nat_sip_expected;

	rtcp_exp->saved_ip = rtcp_exp->tuple.dst.u3.ip;
	rtcp_exp->tuple.dst.u3.ip = rtp_addr->ip;
	rtcp_exp->saved_proto.udp.port = rtcp_exp->tuple.dst.u.udp.port;
	rtcp_exp->dir = !dir;
	rtcp_exp->expectfn = ip_nat_sip_expected;

	/* Try to get same pair of ports: if not, try to change them. */
	for (port = ntohs(rtp_exp->tuple.dst.u.udp.port);
	     port != 0; port += 2) {
		int ret;

		rtp_exp->tuple.dst.u.udp.port = htons(port);
		ret = nf_ct_expect_related(rtp_exp);
		if (ret == -EBUSY)
			continue;
		else if (ret < 0) {
			port = 0;
			break;
		}
		rtcp_exp->tuple.dst.u.udp.port = htons(port + 1);
		ret = nf_ct_expect_related(rtcp_exp);
		if (ret == 0)
			break;
		else if (ret == -EBUSY) {
			nf_ct_unexpect_related(rtp_exp);
			continue;
		} else if (ret < 0) {
			nf_ct_unexpect_related(rtp_exp);
			port = 0;
			break;
		}
	}

	if (port == 0)
		goto err1;

	/* Update media port. */
	if (rtp_exp->tuple.dst.u.udp.port != rtp_exp->saved_proto.udp.port &&
	    !ip_nat_sdp_port(skb, dataoff, dptr, datalen,
			     mediaoff, medialen, port))
		goto err2;

	return NF_ACCEPT;

err2:
	nf_ct_unexpect_related(rtp_exp);
	nf_ct_unexpect_related(rtcp_exp);
err1:
	return NF_DROP;
}