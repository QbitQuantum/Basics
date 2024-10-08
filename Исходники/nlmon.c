int
main(int argc OVS_UNUSED, char *argv[])
{
    uint64_t buf_stub[4096 / 64];
    struct nl_sock *sock;
    struct ofpbuf buf;
    int error;

    set_program_name(argv[0]);
    vlog_set_levels(NULL, VLF_ANY_FACILITY, VLL_DBG);

    error = nl_sock_create(NETLINK_ROUTE, &sock);
    if (error) {
        ovs_fatal(error, "could not create rtnetlink socket");
    }

    error = nl_sock_join_mcgroup(sock, RTNLGRP_LINK);
    if (error) {
        ovs_fatal(error, "could not join RTNLGRP_LINK multicast group");
    }

    ofpbuf_use_stub(&buf, buf_stub, sizeof buf_stub);
    for (;;) {
        error = nl_sock_recv(sock, &buf, false);
        if (error == EAGAIN) {
            /* Nothing to do. */
        } else if (error == ENOBUFS) {
            ovs_error(0, "network monitor socket overflowed");
        } else if (error) {
            ovs_fatal(error, "error on network monitor socket");
        } else {
            struct iff_flag {
                unsigned int flag;
                const char *name;
            };

            static const struct iff_flag flags[] = {
                { IFF_UP, "UP", },
                { IFF_BROADCAST, "BROADCAST", },
#ifndef _WIN32
                { IFF_DEBUG, "DEBUG", },
#endif
                { IFF_LOOPBACK, "LOOPBACK", },
#ifndef _WIN32
                { IFF_POINTOPOINT, "POINTOPOINT", },
                { IFF_NOTRAILERS, "NOTRAILERS", },
#endif
                { IFF_RUNNING, "RUNNING", },
#ifndef _WIN32
                { IFF_NOARP, "NOARP", },
#endif
                { IFF_PROMISC, "PROMISC", },
#ifndef _WIN32
                { IFF_ALLMULTI, "ALLMULTI", },
                { IFF_MASTER, "MASTER", },
                { IFF_SLAVE, "SLAVE", },
#endif
                { IFF_MULTICAST, "MULTICAST", },
#ifndef _WIN32
                { IFF_PORTSEL, "PORTSEL", },
                { IFF_AUTOMEDIA, "AUTOMEDIA", },
                { IFF_DYNAMIC, "DYNAMIC", },
#endif
            };

            struct nlattr *attrs[ARRAY_SIZE(rtnlgrp_link_policy)];
            struct nlmsghdr *nlh;
            struct ifinfomsg *iim;
            int i;

            nlh = ofpbuf_at(&buf, 0, NLMSG_HDRLEN);
            iim = ofpbuf_at(&buf, NLMSG_HDRLEN, sizeof *iim);
            if (!iim) {
                ovs_error(0, "received bad rtnl message (no ifinfomsg)");
                continue;
            }

            if (!nl_policy_parse(&buf, NLMSG_HDRLEN + sizeof(struct ifinfomsg),
                                 rtnlgrp_link_policy,
                                 attrs, ARRAY_SIZE(rtnlgrp_link_policy))) {
                ovs_error(0, "received bad rtnl message (policy)");
                continue;
            }
            printf("netdev %s changed (%s):\n",
                   nl_attr_get_string(attrs[IFLA_IFNAME]),
                   (nlh->nlmsg_type == RTM_NEWLINK ? "RTM_NEWLINK"
#ifndef _WIN32
                    : nlh->nlmsg_type == RTM_DELLINK ? "RTM_DELLINK"
#endif
                    : nlh->nlmsg_type == RTM_GETLINK ? "RTM_GETLINK"
#ifndef _WIN32
                    : nlh->nlmsg_type == RTM_SETLINK ? "RTM_SETLINK"
#endif
                    : "other"));
            printf("\tflags:");
            for (i = 0; i < ARRAY_SIZE(flags); i++) {
                if (iim->ifi_flags & flags[i].flag) {
                    printf(" %s", flags[i].name);
                }
            }
            printf("\n");
            if (attrs[IFLA_MASTER]) {
                uint32_t idx = nl_attr_get_u32(attrs[IFLA_MASTER]);
                char ifname[IFNAMSIZ];
#ifndef _WIN32
                if (!if_indextoname(idx, ifname)) {
                    strcpy(ifname, "unknown");
                }
#endif
                printf("\tmaster=%"PRIu32" (%s)\n", idx, ifname);
            }
        }

        nl_sock_wait(sock, POLLIN);
        poll_block();
    }
}