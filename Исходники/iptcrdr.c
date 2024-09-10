/* return an (malloc'ed) array of "external" port for which there is
 * a port mapping. number is the size of the array */
unsigned short *
get_portmappings_in_range(unsigned short startport, unsigned short endport,
                          int proto, unsigned int * number)
{
	unsigned short * array;
	unsigned int capacity;
	unsigned short eport;
	IPTC_HANDLE h;
	const struct ipt_entry * e;
	const struct ipt_entry_match *match;

	*number = 0;
	capacity = 128;
	array = calloc(capacity, sizeof(unsigned short));
	if(!array)
	{
		syslog(LOG_ERR, "get_portmappings_in_range() : calloc error");
		return NULL;
	}

	h = iptc_init("nat");
	if(!h)
	{
		syslog(LOG_ERR, "get_redirect_rule_by_index() : "
		                "iptc_init() failed : %s",
		       iptc_strerror(errno));
		free(array);
		return NULL;
	}
	if(!iptc_is_chain(miniupnpd_nat_chain, h))
	{
		syslog(LOG_ERR, "chain %s not found", miniupnpd_nat_chain);
		free(array);
		array = NULL;
	}
	else
	{
#ifdef IPTABLES_143
		for(e = iptc_first_rule(miniupnpd_nat_chain, h);
		    e;
			e = iptc_next_rule(e, h))
#else
		for(e = iptc_first_rule(miniupnpd_nat_chain, &h);
		    e;
			e = iptc_next_rule(e, &h))
#endif
		{
			if(proto == e->ip.proto)
			{
				match = (const struct ipt_entry_match *)&e->elems;
				if(0 == strncmp(match->u.user.name, "tcp", IPT_FUNCTION_MAXNAMELEN))
				{
					const struct ipt_tcp * info;
					info = (const struct ipt_tcp *)match->data;
					eport = info->dpts[0];
				}
				else
				{
					const struct ipt_udp * info;
					info = (const struct ipt_udp *)match->data;
					eport = info->dpts[0];
				}
				if(startport <= eport && eport <= endport)
				{
					if(*number >= capacity)
					{
						/* need to increase the capacity of the array */
						array = realloc(array, sizeof(unsigned short)*capacity);
						if(!array)
						{
							syslog(LOG_ERR, "get_portmappings_in_range() : realloc(%u) error",
							       (unsigned)sizeof(unsigned short)*capacity);
							*number = 0;
							break;
						}
						array[*number] = eport;
						(*number)++;
					}
				}
			}
		}
	}
	if(h)
#ifdef IPTABLES_143
		iptc_free(h);
#else
		iptc_free(&h);
#endif
	return array;
}