void
mroute6pr(u_long mfcaddr, u_long mifaddr)
{
	struct mf6c *mf6ctable[MF6CTBLSIZ], *mfcp;
	struct mif6 mif6table[MAXMIFS];
	struct mf6c mfc;
	struct rtdetq rte, *rtep;
	struct mif6 *mifp;
	mifi_t mifi;
	int i;
	int banner_printed;
	int saved_numeric_addr;
	mifi_t maxmif = 0;
	long int waitings;
	size_t len;

	len = sizeof(mif6table);
	if (live) {
		if (sysctlbyname("net.inet6.ip6.mif6table", mif6table, &len,
		    NULL, 0) < 0) {
			warn("sysctl: net.inet6.ip6.mif6table");
			return;
		}
	} else
		kread(mifaddr, (char *)mif6table, sizeof(mif6table));

	saved_numeric_addr = numeric_addr;
	numeric_addr = 1;
	banner_printed = 0;

	for (mifi = 0, mifp = mif6table; mifi < MAXMIFS; ++mifi, ++mifp) {
		struct ifnet ifnet;
		char ifname[IFNAMSIZ];

		if (mifp->m6_ifp == NULL)
			continue;

		/* XXX KVM */
		kread((u_long)mifp->m6_ifp, (char *)&ifnet, sizeof(ifnet));

		maxmif = mifi;
		if (!banner_printed) {
			printf("\nIPv6 Multicast Interface Table\n"
			       " Mif   Rate   PhyIF   "
			       "Pkts-In   Pkts-Out\n");
			banner_printed = 1;
		}

		printf("  %2u   %4d",
		       mifi, mifp->m6_rate_limit);
		printf("   %5s", (mifp->m6_flags & MIFF_REGISTER) ?
		       "reg0" : if_indextoname(ifnet.if_index, ifname));

		printf(" %9ju  %9ju\n", (uintmax_t)mifp->m6_pkt_in,
		    (uintmax_t)mifp->m6_pkt_out);
	}
	if (!banner_printed)
		printf("\nIPv6 Multicast Interface Table is empty\n");

	len = sizeof(mf6ctable);
	if (live) {
		if (sysctlbyname("net.inet6.ip6.mf6ctable", mf6ctable, &len,
		    NULL, 0) < 0) {
			warn("sysctl: net.inet6.ip6.mf6ctable");
			return;
		}
	} else
		kread(mfcaddr, (char *)mf6ctable, sizeof(mf6ctable));

	banner_printed = 0;

	for (i = 0; i < MF6CTBLSIZ; ++i) {
		mfcp = mf6ctable[i];
		while(mfcp) {
			kread((u_long)mfcp, (char *)&mfc, sizeof(mfc));
			if (!banner_printed) {
				printf ("\nIPv6 Multicast Forwarding Cache\n");
				printf(" %-*.*s %-*.*s %s",
				       WID_ORG, WID_ORG, "Origin",
				       WID_GRP, WID_GRP, "Group",
				       "  Packets Waits In-Mif  Out-Mifs\n");
				banner_printed = 1;
			}

			printf(" %-*.*s", WID_ORG, WID_ORG,
			       routename6(&mfc.mf6c_origin));
			printf(" %-*.*s", WID_GRP, WID_GRP,
			       routename6(&mfc.mf6c_mcastgrp));
			printf(" %9ju", (uintmax_t)mfc.mf6c_pkt_cnt);

			for (waitings = 0, rtep = mfc.mf6c_stall; rtep; ) {
				waitings++;
				/* XXX KVM */
				kread((u_long)rtep, (char *)&rte, sizeof(rte));
				rtep = rte.next;
			}
			printf("   %3ld", waitings);

			if (mfc.mf6c_parent == MF6C_INCOMPLETE_PARENT)
				printf(" ---   ");
			else
				printf("  %3d   ", mfc.mf6c_parent);
			for (mifi = 0; mifi <= maxmif; mifi++) {
				if (IF_ISSET(mifi, &mfc.mf6c_ifset))
					printf(" %u", mifi);
			}
			printf("\n");

			mfcp = mfc.mf6c_next;
		}
	}
	if (!banner_printed)
		printf("\nIPv6 Multicast Forwarding Table is empty\n");

	printf("\n");
	numeric_addr = saved_numeric_addr;
}