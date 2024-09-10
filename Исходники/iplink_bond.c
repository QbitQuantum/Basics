static void bond_print_opt(struct link_util *lu, FILE *f, struct rtattr *tb[])
{
	unsigned ifindex;

	if (!tb)
		return;

	if (tb[IFLA_BOND_MODE]) {
		const char *mode = get_name(mode_tbl,
			rta_getattr_u8(tb[IFLA_BOND_MODE]));
		fprintf(f, "mode %s ", mode);
	}

	if (tb[IFLA_BOND_ACTIVE_SLAVE] &&
	    (ifindex = rta_getattr_u32(tb[IFLA_BOND_ACTIVE_SLAVE]))) {
		char buf[IFNAMSIZ];
		const char *n = if_indextoname(ifindex, buf);

		if (n)
			fprintf(f, "active_slave %s ", n);
		else
			fprintf(f, "active_slave %u ", ifindex);
	}

	if (tb[IFLA_BOND_MIIMON])
		fprintf(f, "miimon %u ", rta_getattr_u32(tb[IFLA_BOND_MIIMON]));

	if (tb[IFLA_BOND_UPDELAY])
		fprintf(f, "updelay %u ", rta_getattr_u32(tb[IFLA_BOND_UPDELAY]));

	if (tb[IFLA_BOND_DOWNDELAY])
		fprintf(f, "downdelay %u ",
			rta_getattr_u32(tb[IFLA_BOND_DOWNDELAY]));

	if (tb[IFLA_BOND_USE_CARRIER])
		fprintf(f, "use_carrier %u ",
			rta_getattr_u8(tb[IFLA_BOND_USE_CARRIER]));

	if (tb[IFLA_BOND_ARP_INTERVAL])
		fprintf(f, "arp_interval %u ",
			rta_getattr_u32(tb[IFLA_BOND_ARP_INTERVAL]));

	if (tb[IFLA_BOND_ARP_IP_TARGET]) {
		struct rtattr *iptb[BOND_MAX_ARP_TARGETS + 1];
		char buf[INET_ADDRSTRLEN];
		int i;

		parse_rtattr_nested(iptb, BOND_MAX_ARP_TARGETS,
			tb[IFLA_BOND_ARP_IP_TARGET]);

		if (iptb[0])
			fprintf(f, "arp_ip_target ");

		for (i = 0; i < BOND_MAX_ARP_TARGETS; i++) {
			if (iptb[i])
				fprintf(f, "%s",
					rt_addr_n2a(AF_INET,
						    RTA_PAYLOAD(iptb[i]),
						    RTA_DATA(iptb[i]),
						    buf,
						    INET_ADDRSTRLEN));
			if (i < BOND_MAX_ARP_TARGETS-1 && iptb[i+1])
				fprintf(f, ",");
		}

		if (iptb[0])
			fprintf(f, " ");
	}

	if (tb[IFLA_BOND_ARP_VALIDATE]) {
		const char *arp_validate = get_name(arp_validate_tbl,
			rta_getattr_u32(tb[IFLA_BOND_ARP_VALIDATE]));
		fprintf(f, "arp_validate %s ", arp_validate);
	}

	if (tb[IFLA_BOND_ARP_ALL_TARGETS]) {
		const char *arp_all_targets = get_name(arp_all_targets_tbl,
			rta_getattr_u32(tb[IFLA_BOND_ARP_ALL_TARGETS]));
		fprintf(f, "arp_all_targets %s ", arp_all_targets);
	}

	if (tb[IFLA_BOND_PRIMARY] &&
	    (ifindex = rta_getattr_u32(tb[IFLA_BOND_PRIMARY]))) {
		char buf[IFNAMSIZ];
		const char *n = if_indextoname(ifindex, buf);

		if (n)
			fprintf(f, "primary %s ", n);
		else
			fprintf(f, "primary %u ", ifindex);
	}

	if (tb[IFLA_BOND_PRIMARY_RESELECT]) {
		const char *primary_reselect = get_name(primary_reselect_tbl,
			rta_getattr_u8(tb[IFLA_BOND_PRIMARY_RESELECT]));
		fprintf(f, "primary_reselect %s ", primary_reselect);
	}

	if (tb[IFLA_BOND_FAIL_OVER_MAC]) {
		const char *fail_over_mac = get_name(fail_over_mac_tbl,
			rta_getattr_u8(tb[IFLA_BOND_FAIL_OVER_MAC]));
		fprintf(f, "fail_over_mac %s ", fail_over_mac);
	}

	if (tb[IFLA_BOND_XMIT_HASH_POLICY]) {
		const char *xmit_hash_policy = get_name(xmit_hash_policy_tbl,
			rta_getattr_u8(tb[IFLA_BOND_XMIT_HASH_POLICY]));
		fprintf(f, "xmit_hash_policy %s ", xmit_hash_policy);
	}

	if (tb[IFLA_BOND_RESEND_IGMP])
		fprintf(f, "resend_igmp %u ",
			rta_getattr_u32(tb[IFLA_BOND_RESEND_IGMP]));

	if (tb[IFLA_BOND_NUM_PEER_NOTIF])
		fprintf(f, "num_grat_arp %u ",
			rta_getattr_u8(tb[IFLA_BOND_NUM_PEER_NOTIF]));

	if (tb[IFLA_BOND_ALL_SLAVES_ACTIVE])
		fprintf(f, "all_slaves_active %u ",
			rta_getattr_u8(tb[IFLA_BOND_ALL_SLAVES_ACTIVE]));

	if (tb[IFLA_BOND_MIN_LINKS])
		fprintf(f, "min_links %u ",
			rta_getattr_u32(tb[IFLA_BOND_MIN_LINKS]));

	if (tb[IFLA_BOND_LP_INTERVAL])
		fprintf(f, "lp_interval %u ",
			rta_getattr_u32(tb[IFLA_BOND_LP_INTERVAL]));

	if (tb[IFLA_BOND_PACKETS_PER_SLAVE])
		fprintf(f, "packets_per_slave %u ",
			rta_getattr_u32(tb[IFLA_BOND_PACKETS_PER_SLAVE]));

	if (tb[IFLA_BOND_AD_LACP_RATE]) {
		const char *lacp_rate = get_name(lacp_rate_tbl,
			rta_getattr_u8(tb[IFLA_BOND_AD_LACP_RATE]));
		fprintf(f, "lacp_rate %s ", lacp_rate);
	}

	if (tb[IFLA_BOND_AD_SELECT]) {
		const char *ad_select = get_name(ad_select_tbl,
			rta_getattr_u8(tb[IFLA_BOND_AD_SELECT]));
		fprintf(f, "ad_select %s ", ad_select);
	}

	if (tb[IFLA_BOND_AD_INFO]) {
		struct rtattr *adtb[IFLA_BOND_AD_INFO_MAX + 1];

		parse_rtattr_nested(adtb, IFLA_BOND_AD_INFO_MAX,
			tb[IFLA_BOND_AD_INFO]);

		if (adtb[IFLA_BOND_AD_INFO_AGGREGATOR])
			fprintf(f, "ad_aggregator %d ",
			  rta_getattr_u16(adtb[IFLA_BOND_AD_INFO_AGGREGATOR]));

		if (adtb[IFLA_BOND_AD_INFO_NUM_PORTS])
			fprintf(f, "ad_num_ports %d ",
			  rta_getattr_u16(adtb[IFLA_BOND_AD_INFO_NUM_PORTS]));

		if (adtb[IFLA_BOND_AD_INFO_ACTOR_KEY])
			fprintf(f, "ad_actor_key %d ",
			  rta_getattr_u16(adtb[IFLA_BOND_AD_INFO_ACTOR_KEY]));

		if (adtb[IFLA_BOND_AD_INFO_PARTNER_KEY])
			fprintf(f, "ad_partner_key %d ",
			  rta_getattr_u16(adtb[IFLA_BOND_AD_INFO_PARTNER_KEY]));

		if (adtb[IFLA_BOND_AD_INFO_PARTNER_MAC]) {
			unsigned char *p =
				RTA_DATA(adtb[IFLA_BOND_AD_INFO_PARTNER_MAC]);
			SPRINT_BUF(b);
			fprintf(f, "ad_partner_mac %s ",
				ll_addr_n2a(p, ETH_ALEN, 0, b, sizeof(b)));
		}
	}
}