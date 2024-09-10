/*Look if the source ip address is local to the subnet*/
int watch_bogon(char* buffer, uint16_t vlan_id, struct ether_header* eptr, struct ip6_hdr* ipptr)
{

	struct ether_addr* eth_addr = (struct ether_addr*) eptr->ether_shost;
	struct in6_addr* ip_addr = &ipptr->ip6_src;
	char str_ip[IP6_STR_SIZE];

	router_list_t *tmp = routers;
	int find = 0;

	ipv6_ntoa(str_ip, *ip_addr);

	while( tmp != NULL)
	{
		prefix_t *ptmp = tmp->prefixes;
		while(ptmp != NULL)
		{
			if(IN6_ARE_PRE_EQUAL(ip_addr, &(ptmp->prefix)))
				find = 1;

			ptmp = ptmp->next;
		}
		tmp = tmp->next;
	}

	if (!find && !IN6_IS_ADDR_UNSPECIFIED(ip_addr)&&!IN6_IS_ADDR_LINKLOCAL(ip_addr)&&!IN6_IS_ADDR_MULTICAST(ip_addr)&&!IN6_IS_ADDR_SITELOCAL(ip_addr))
	{
		snprintf (buffer, NOTIFY_BUFFER_SIZE, "VLAN%d: bogon %s %s",vlan_id,ether_ntoa(eth_addr),str_ip);
		notify(1, buffer, "bogon", eth_addr, str_ip, NULL);
		return 1;
	}
	else
		return 0;
}