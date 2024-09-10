/*
 * Parse a RTM_NEWNDUSEROPT message.
 */
bool NetlinkEvent::parseNdUserOptMessage(struct nduseroptmsg *msg, int len) {
    // Check the length is valid.
    if (msg->nduseropt_opts_len > len) {
        SLOGE("RTM_NEWNDUSEROPT invalid length %d > %d\n",
              msg->nduseropt_opts_len, len);
        return false;
    }
    len = msg->nduseropt_opts_len;

    // Check address family and packet type.
    if (msg->nduseropt_family != AF_INET6) {
        SLOGE("RTM_NEWNDUSEROPT message for unknown family %d\n",
              msg->nduseropt_family);
        return false;
    }

    if (msg->nduseropt_icmp_type != ND_ROUTER_ADVERT ||
        msg->nduseropt_icmp_code != 0) {
        SLOGE("RTM_NEWNDUSEROPT message for unknown ICMPv6 type/code %d/%d\n",
              msg->nduseropt_icmp_type, msg->nduseropt_icmp_code);
        return false;
    }

    // Find the interface name.
    char ifname[IFNAMSIZ + 1];
    if (!if_indextoname(msg->nduseropt_ifindex, ifname)) {
        SLOGE("RTM_NEWNDUSEROPT on unknown ifindex %d\n",
              msg->nduseropt_ifindex);
        return false;
    }

    // The kernel sends a separate netlink message for each ND option in the RA.
    // So only parse the first ND option in the message.
    struct nd_opt_hdr *opthdr = (struct nd_opt_hdr *) (msg + 1);

    // The length is in multiples of 8 octets.
    uint16_t optlen = opthdr->nd_opt_len;
    if (optlen * 8 > len) {
        SLOGE("Invalid option length %d > %d for ND option %d\n",
              optlen * 8, len, opthdr->nd_opt_type);
        return false;
    }

    if (opthdr->nd_opt_type == ND_OPT_RDNSS) {
        // DNS Servers (RFC 6106).
        // Each address takes up 2*8 octets, and the header takes up 8 octets.
        // So for a valid option with one or more addresses, optlen must be
        // odd and greater than 1.
        if ((optlen < 3) || !(optlen & 0x1)) {
            SLOGE("Invalid optlen %d for RDNSS option\n", optlen);
            return false;
        }
        int numaddrs = (optlen - 1) / 2;

        // Find the lifetime.
        struct nd_opt_rdnss *rndss_opt = (struct nd_opt_rdnss *) opthdr;
        uint32_t lifetime = ntohl(rndss_opt->nd_opt_rdnss_lifetime);

        // Construct "SERVERS=<comma-separated string of DNS addresses>".
        // Reserve (INET6_ADDRSTRLEN + 1) chars for each address: all but the
        // the last address are followed by ','; the last is followed by '\0'.
        static const char kServerTag[] = "SERVERS=";
        static const int kTagLength = sizeof(kServerTag) - 1;
        int bufsize = kTagLength + numaddrs * (INET6_ADDRSTRLEN + 1);
        char *buf = (char *) malloc(bufsize);
        if (!buf) {
            SLOGE("RDNSS option: out of memory\n");
            return false;
        }
        strcpy(buf, kServerTag);
        int pos = kTagLength;

        struct in6_addr *addrs = (struct in6_addr *) (rndss_opt + 1);
        for (int i = 0; i < numaddrs; i++) {
            if (i > 0) {
                buf[pos++] = ',';
            }
            inet_ntop(AF_INET6, addrs + i, buf + pos, bufsize - pos);
            pos += strlen(buf + pos);
        }
        buf[pos] = '\0';

        mAction = NlActionRdnss;
        mSubsystem = strdup("net");
        asprintf(&mParams[0], "INTERFACE=%s", ifname);
        asprintf(&mParams[1], "LIFETIME=%u", lifetime);
        mParams[2] = buf;
    } else {
        SLOGD("Unknown ND option type %d\n", opthdr->nd_opt_type);
        return false;
    }

    return true;
}