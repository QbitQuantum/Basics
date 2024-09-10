/*
 * get_dev_ip: fetches the ip currently assigned to the interface named `dev'
 * and stores it to `ip'.
 * On success 0 is returned, -1 otherwise.
 */
int get_dev_ip(inet_prefix *ip, int family, char *dev)
{
	int s=-1;
	int ret=0;

	setzero(ip, sizeof(inet_prefix));

	if((s=new_socket(family)) < 0) {
		error("Error while setting \"%s\" ip: Cannot open socket", dev);
		return -1;
	}

	if(family == AF_INET) {
		struct ifreq req;

		strncpy(req.ifr_name, dev, IFNAMSIZ);
		req.ifr_addr.sa_family = family;
		
		if(ioctl(s, SIOCGIFADDR, &req))
			ERROR_FINISH(ret, -1, finish);

		sockaddr_to_inet(&req.ifr_addr, ip, 0);
	} else if(family == AF_INET6) {
		struct in6_ifreq req6;

		/*
		 * XXX: NOT TESTED
		 */

		req6.ifr6_ifindex=ll_name_to_index(dev);
		req6.ifr6_prefixlen=0;

		if(ioctl(s, SIOCGIFADDR, &req6))
			ERROR_FINISH(ret, -1, finish);

		inet_setip(ip, (u_int *)&req6.ifr6_addr, family);
	}

finish:
	if(s != -1)
		close(s);
	return ret;
}