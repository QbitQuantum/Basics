int
_intf_get_noalias(intf_t *intf, struct intf_entry *entry)
{
	struct lifreq lifr;
	int fd;

	/* Get interface index. */
	entry->intf_index = if_nametoindex(entry->intf_name);
	if (entry->intf_index == 0)
		return (-1);

	strlcpy(lifr.lifr_name, entry->intf_name, sizeof(lifr.lifr_name));

	/* Get interface flags. Here he also check whether we need to use fd or
	 * fd6 in the rest of the function. Using the wrong address family in
	 * the ioctls gives ENXIO on Solaris. */
	if (ioctl(intf->fd, SIOCGLIFFLAGS, &lifr) >= 0)
		fd = intf->fd;
	else if (intf->fd6 != -1 && ioctl(intf->fd6, SIOCGLIFFLAGS, &lifr) >= 0)
		fd = intf->fd6;
	else
		return (-1);
	
	entry->intf_flags = intf_iff_to_flags(lifr.lifr_flags);
	_intf_set_type(entry);
	
	/* Get interface MTU. */
#ifdef SIOCGLIFMTU
	if (ioctl(fd, SIOCGLIFMTU, &lifr) < 0)
#endif
		return (-1);
	entry->intf_mtu = lifr.lifr_mtu;

	entry->intf_addr.addr_type = entry->intf_dst_addr.addr_type =
	    entry->intf_link_addr.addr_type = ADDR_TYPE_NONE;
	
	/* Get primary interface address. */
	if (ioctl(fd, SIOCGLIFADDR, &lifr) == 0) {
		addr_ston((struct sockaddr *)&lifr.lifr_addr, &entry->intf_addr);
		if (ioctl(fd, SIOCGLIFNETMASK, &lifr) < 0)
			return (-1);
		addr_stob((struct sockaddr *)&lifr.lifr_addr, &entry->intf_addr.addr_bits);
	}
	/* Get other addresses. */
	if (entry->intf_type == INTF_TYPE_TUN) {
		if (ioctl(fd, SIOCGLIFDSTADDR, &lifr) == 0) {
			if (addr_ston((struct sockaddr *)&lifr.lifr_addr,
			    &entry->intf_dst_addr) < 0)
				return (-1);
		}
	} else if (entry->intf_type == INTF_TYPE_ETH) {
		eth_t *eth;
		
		if ((eth = eth_open(entry->intf_name)) != NULL) {
			if (!eth_get(eth, &entry->intf_link_addr.addr_eth)) {
				entry->intf_link_addr.addr_type =
				    ADDR_TYPE_ETH;
				entry->intf_link_addr.addr_bits =
				    ETH_ADDR_BITS;
			}
			eth_close(eth);
		}
	}
	return (0);
}