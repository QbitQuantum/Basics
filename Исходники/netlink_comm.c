static int netlink_msg_handler(struct nl_msg *msg, void *arg)
{
	struct nlmsghdr *hdr;
	struct tcmsg *tcm;
	struct nlattr *attrs[TCA_MAX+1];
	struct nlattr *stat_attrs[TCA_STATS_MAX+1];
	struct qdisc_handler *h;
	char qdisc[IFNAMSIZ] = {0};
	int qdisc_l = 0;
	char ifname[IFNAMSIZ] = {0};
	int ifname_l = 0;
	struct timeval current_time = {0};
	double time;

	char *ret = NULL;

	struct gnet_stats_basic *sb;
	struct gnet_stats_queue *q;

	struct options *opt = arg;

	struct recordset rset = {0};

	hdr = nlmsg_hdr(msg);
	tcm = nlmsg_data(hdr);
	if(!has_iface(opt, tcm->tcm_ifindex))
		return NL_SKIP;

	if((ret = rtnl_link_i2name(opt->cache, tcm->tcm_ifindex, ifname, IFNAMSIZ)) == NULL)
		return NL_SKIP;

	// No length checking in netlink library.
	if((ifname_l = 1 + strnlen(ifname, IFNAMSIZ)) >= IFNAMSIZ) {
		ifname[IFNAMSIZ-1] = '\0';
		ifname_l = IFNAMSIZ;
	}

	gettimeofday(&current_time, NULL);
	time = (double)current_time.tv_usec / 1000000 + (double) current_time.tv_sec;
	add_record_double(&rset, "time", sizeof("time"), time);
	add_record_str(&rset, "iface", sizeof("iface"), ifname, ifname_l);

	nlmsg_parse(hdr, sizeof(*tcm), attrs, TCA_MAX, tca_policy);

	if(attrs[TCA_KIND]) {
		qdisc_l = nla_len(attrs[TCA_KIND]);
		memcpy(qdisc, nla_get_string(attrs[TCA_KIND]), qdisc_l);
		add_record_str(&rset, "qdisc", sizeof("qdisc"), qdisc, qdisc_l);
	}

	add_record_hex(&rset, "handle", sizeof("handle"), tcm->tcm_handle >> 16);

	if(attrs[TCA_STATS2]) {
		nla_parse_nested(stat_attrs, TCA_STATS_MAX, attrs[TCA_STATS2], tca_stats_policy);
		if(stat_attrs[TCA_STATS_BASIC]) {
			sb = nla_data(stat_attrs[TCA_STATS_BASIC]);
			add_record_uint(&rset, "bytes", sizeof("bytes"), sb->bytes);
			add_record_uint(&rset, "packets", sizeof("packets"), sb->packets);
		}

		if(stat_attrs[TCA_STATS_QUEUE]) {
			q = nla_data(stat_attrs[TCA_STATS_QUEUE]);
			add_record_uint(&rset, "drops", sizeof("drops"), q->drops);
			add_record_uint(&rset, "qlen", sizeof("qlen"), q->qlen);
			add_record_uint(&rset, "backlog", sizeof("backlog"), q->backlog);
			add_record_uint(&rset, "overlimits", sizeof("overlimits"), q->overlimits);
			add_record_uint(&rset, "requeues", sizeof("requeues"), q->requeues);
		}
		if(stat_attrs[TCA_STATS_APP]) {
			h = find_qdisc_handler(qdisc);
			if(h)
				h->parse_stats(stat_attrs[TCA_STATS_APP], &rset);
		}
	}
	opt->formatter->format(opt->formatter, &rset);
	clear_records(&rset);
	if(!opt->run_length || current_time.tv_sec < opt->start_time.tv_sec + opt->run_length)
		return NL_OK;
	else
		return NL_STOP;
}