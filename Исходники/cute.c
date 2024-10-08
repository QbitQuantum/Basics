int
mcast_join(int sockfd, const struct sockaddr *grp, socklen_t grplen, const char *ifname, u_int ifindex)
{
#ifdef MCAST_JOIN_GROUP
struct	group_req	req;

        if (ifindex > 0) {
                req.gr_interface = ifindex;
        } else if (ifname != NULL) {
                if ( (req.gr_interface = if_nametoindex(ifname)) == 0) {
                        errno = ENXIO;  /* i/f name not found */
                        return -1;
                }
        } else req.gr_interface = 0;
        if (grplen > sizeof(req.gr_group)) {
                errno = EINVAL;
                return -1;
        }
        memcpy(&req.gr_group, grp, grplen);
        return setsockopt(sockfd, family_to_level(grp->sa_family), MCAST_JOIN_GROUP, &req, sizeof(req));
#else
/* end mcast_join1 */

/* include mcast_join2 */
        switch (grp->sa_family) {
        case AF_INET:
        struct	ip_mreqn	mreq;
        struct	ifreq		ifreq;

                memcpy(&mreq.imr_multiaddr,\
                       &((const struct sockaddr_in *) grp)->sin_addr,\
                       sizeof(struct in_addr));

                if (ifindex > 0) {
                        if (if_indextoname(ifindex, ifreq.ifr_name) == NULL) {
                                errno = ENXIO;  /* i/f index not found */
                                return -1;
                        }
                        goto doioctl;
                } else if (ifname != NULL) {
                        strncpy(ifreq.ifr_name, ifname, IFNAMSIZ);
		doioctl:
                        if (ioctl(sockfd, SIOCGIFADDR, &ifreq) < 0) return -1;
                        memcpy(&mreq.imr_interface,\
                               &((struct sockaddr_in *) &ifreq.ifr_addr)->sin_addr,\
                               sizeof(struct in_addr));
                } else mreq.imr_interface.s_addr = htonl(INADDR_ANY);

                return setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
/* end mcast_join2 */

/* include mcast_join3 */
#ifdef  IPV6
#ifndef IPV6_JOIN_GROUP         /* APIv0 compatibility */
#define IPV6_JOIN_GROUP         IPV6_ADD_MEMBERSHIP
#endif
        case AF_INET6:
        struct	ipv6_mreq	mreq6;

                memcpy(&mreq6.ipv6mr_multiaddr,\
                       &((const struct sockaddr_in6 *) grp)->sin6_addr,\
                       sizeof(struct in6_addr));

                if (ifindex > 0) mreq6.ipv6mr_interface = ifindex;
                else if (ifname != NULL) {
                        if ( (mreq6.ipv6mr_interface = if_nametoindex(ifname)) == 0) {
                                errno = ENXIO;  /* i/f name not found */
                                return -1;
                        }
                } else mreq6.ipv6mr_interface = 0;

                return setsockopt(sockfd, IPPROTO_IPV6, IPV6_JOIN_GROUP, &mreq6, sizeof(mreq6));
#endif

        default:
                errno = EAFNOSUPPORT;
                return -1;
        }
#endif
}