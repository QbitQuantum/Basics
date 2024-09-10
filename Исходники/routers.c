router_list_t * router_get(router_list_t *list, uint16_t vlan_id, struct in6_addr lla, struct ether_addr eth)
{
	router_list_t *tmp = list;

	while(tmp != NULL)
	{
		if(in_vlan(tmp, vlan_id) && !MEMCMP(&eth,&(tmp->mac), sizeof(struct ether_addr)))
			if(IN6_ARE_ADDR_EQUAL(&lla,&(tmp->lla)))
				return tmp;

		tmp = tmp->next;
	}

	return NULL;
}