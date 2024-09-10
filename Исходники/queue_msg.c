int nfnlmsg_queue_msg_parse(struct nlmsghdr *nlh,
			    struct nfnl_queue_msg **result)
{
	struct nfnl_queue_msg *msg;
	struct nlattr *tb[NFQA_MAX+1];
	struct nlattr *attr;
	int err;

	msg = nfnl_queue_msg_alloc();
	if (!msg)
		return -NLE_NOMEM;

	msg->ce_msgtype = nlh->nlmsg_type;

	err = nlmsg_parse(nlh, sizeof(struct nfgenmsg), tb, NFQA_MAX,
			  queue_policy);
	if (err < 0)
		goto errout;

	nfnl_queue_msg_set_group(msg, nfnlmsg_res_id(nlh));
	nfnl_queue_msg_set_family(msg, nfnlmsg_family(nlh));

	attr = tb[NFQA_PACKET_HDR];
	if (attr) {
		struct nfqnl_msg_packet_hdr *hdr = nla_data(attr);

		nfnl_queue_msg_set_packetid(msg, ntohl(hdr->packet_id));
		if (hdr->hw_protocol)
			nfnl_queue_msg_set_hwproto(msg, hdr->hw_protocol);
		nfnl_queue_msg_set_hook(msg, hdr->hook);
	}

	attr = tb[NFQA_MARK];
	if (attr)
		nfnl_queue_msg_set_mark(msg, ntohl(nla_get_u32(attr)));

	attr = tb[NFQA_TIMESTAMP];
	if (attr) {
		struct nfqnl_msg_packet_timestamp *timestamp = nla_data(attr);
		struct timeval tv;

		tv.tv_sec = ntohll(timestamp->sec);
		tv.tv_usec = ntohll(timestamp->usec);
		nfnl_queue_msg_set_timestamp(msg, &tv);
	}

	attr = tb[NFQA_IFINDEX_INDEV];
	if (attr)
		nfnl_queue_msg_set_indev(msg, ntohl(nla_get_u32(attr)));

	attr = tb[NFQA_IFINDEX_OUTDEV];
	if (attr)
		nfnl_queue_msg_set_outdev(msg, ntohl(nla_get_u32(attr)));

	attr = tb[NFQA_IFINDEX_PHYSINDEV];
	if (attr)
		nfnl_queue_msg_set_physindev(msg, ntohl(nla_get_u32(attr)));

	attr = tb[NFQA_IFINDEX_PHYSOUTDEV];
	if (attr)
		nfnl_queue_msg_set_physoutdev(msg, ntohl(nla_get_u32(attr)));

	attr = tb[NFQA_HWADDR];
	if (attr) {
		struct nfqnl_msg_packet_hw *hw = nla_data(attr);

		nfnl_queue_msg_set_hwaddr(msg, hw->hw_addr,
					  ntohs(hw->hw_addrlen));
	}

	attr = tb[NFQA_PAYLOAD];
	if (attr) {
		err = nfnl_queue_msg_set_payload(msg, nla_data(attr),
						 nla_len(attr));
		if (err < 0)
			goto errout;
	}

	*result = msg;
	return 0;

errout:
	nfnl_queue_msg_put(msg);
	return err;
}