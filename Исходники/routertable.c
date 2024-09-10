int  get_route_table_by_snmp(struct route_table *rt)
{
	ipRouteTable *rtable = NULL ;
//	getIpRouteTable(rt->routerip, &rtable); 
	getIpForwardTable(rt->routerip, &rtable); 
	if(rtable == NULL)
	{
		printf("Get routing table failed\n");
		return NULL;
	}
	ipRouteTable* r = rtable->next;
	int total = 0;
	while(r!=NULL){
		struct route* newroute = malloc_z(struct route); 

		inet_pton(AF_INET, r->ipRouteDest ,&newroute->prefix.prefix);
		newroute->prefix.family = AF_INET;
		newroute->prefix.prefixlen = get_prefix_length(r->ipRouteMask);

		inet_pton(AF_INET, r->ipRouteNextHop, &newroute->gateway);

		newroute->interface_id = atoi(r->ipRouteIfIndex);

		newroute->metric = atoi(r->ipRouteMetric);

		if ( strcmp(r->ipRouteType,"local") == 0 ) 
		newroute->type = ROUTE_TYPE_LOCAL;
		else 
			newroute->type = ROUTE_TYPE_REMOTE;
		
		newroute->dirty = FRESH_STATUS;
		
		struct route** rr = find_before_route(rt->routes, *newroute);
		if( rr== NULL)
			add_route(rt->routes, newroute);
		else
			update_route(rr, newroute);

		total++;
		r = r->next;
	}
	freeIpRouteTable(rtable);
	rt->route_table_len = total;
}