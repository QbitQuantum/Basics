/*
 * Probe if each router in the default router list is still alive. 
 */
void
defrouter_probe(int ifindex)
{
	struct in6_drlist dr;
	int s, i;
	u_char ntopbuf[INET6_ADDRSTRLEN];

	if ((s = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) {
		warnmsg(LOG_ERR, __FUNCTION__, "socket: %s", strerror(errno));
		return;
	}
	bzero(&dr, sizeof(dr));
	strlcpy(dr.ifname, "lo0", sizeof(dr.ifname)); /* dummy interface */
	if (ioctl(s, SIOCGDRLST_IN6, (caddr_t)&dr) < 0) {
		warnmsg(LOG_ERR, __FUNCTION__, "ioctl(SIOCGDRLST_IN6): %s",
		       strerror(errno));
		goto closeandend;
	}

	for(i = 0; dr.defrouter[i].if_index && i < PRLSTSIZ; i++) {
		if (ifindex && dr.defrouter[i].if_index == ifindex) {
			/* sanity check */
			if (!IN6_IS_ADDR_LINKLOCAL(&dr.defrouter[i].rtaddr)) {
				warnmsg(LOG_ERR, __FUNCTION__,
					"default router list contains a "
					"non-linklocal address(%s)",
				       inet_ntop(AF_INET6,
						 &dr.defrouter[i].rtaddr,
						 (char *)ntopbuf, INET6_ADDRSTRLEN));
				continue; /* ignore the address */
			}
			sendprobe(&dr.defrouter[i].rtaddr,
				  dr.defrouter[i].if_index);
		}
	}

  closeandend:
	close(s);
	return;
}