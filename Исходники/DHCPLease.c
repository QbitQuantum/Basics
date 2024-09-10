/*
 * Function: DHCPLeaseCreateWithDictionary
 * Purpose:
 *   Instantiate a new DHCPLease structure corresponding to the given
 *   dictionary.  Validates that required properties are present,
 *   returns NULL if those checks fail.
 */
static DHCPLeaseRef
DHCPLeaseCreateWithDictionary(CFDictionaryRef dict, bool is_wifi)
{
    CFDataRef			hwaddr_data;
    dhcp_lease_time_t		lease_time;
    DHCPLeaseRef		lease_p;
    CFDataRef			pkt_data;
    CFRange			pkt_data_range;
    struct in_addr *		router_p;
    CFStringRef			ssid = NULL;
    CFDateRef			start_date;
    dhcp_lease_time_t		t1_time;
    dhcp_lease_time_t		t2_time;

    /* get the lease start time */
    start_date = CFDictionaryGetValue(dict, kLeaseStartDate);
    if (isA_CFDate(start_date) == NULL) {
	goto failed;
    }
    /* get the packet data */
    pkt_data = CFDictionaryGetValue(dict, kPacketData);
    if (isA_CFData(pkt_data) == NULL) {
	goto failed;
    }
    /* if Wi-Fi, get the SSID */
    if (is_wifi) {
	ssid = CFDictionaryGetValue(dict, kSSID);
	if (isA_CFString(ssid) == NULL) {
	    goto failed;
	}
    }

    pkt_data_range.location = 0;
    pkt_data_range.length = CFDataGetLength(pkt_data);
    if (pkt_data_range.length < sizeof(struct dhcp)) {
	goto failed;
    }
    lease_p = (DHCPLeaseRef)
	malloc(offsetof(DHCPLease, pkt) + pkt_data_range.length);
    bzero(lease_p, offsetof(DHCPLease, pkt));

    /* copy the packet data */
    CFDataGetBytes(pkt_data, pkt_data_range, lease_p->pkt);
    lease_p->pkt_length = pkt_data_range.length;

    /* get the lease information and router IP address */
    lease_p->lease_start = (absolute_time_t)CFDateGetAbsoluteTime(start_date);
    { /* parse/retrieve options */
	dhcpol_t			options;
	
	(void)dhcpol_parse_packet(&options, (void *)lease_p->pkt,
				  pkt_data_range.length, NULL);
	dhcp_get_lease_from_options(&options, &lease_time, &t1_time, &t2_time);
	router_p = dhcp_get_router_from_options(&options, lease_p->our_ip);
	dhcpol_free(&options);
    }
    lease_p->lease_length = lease_time;

    /* get the IP address */
    /* ALIGN: lease_p->pkt is aligned, cast ok. */
    lease_p->our_ip = ((struct dhcp *)(void *)lease_p->pkt)->dp_yiaddr;

    /* get the router information */
    if (router_p != NULL) {
	CFRange		hwaddr_range;

	lease_p->router_ip = *router_p;
	/* get the router hardware address */
	hwaddr_data = CFDictionaryGetValue(dict, kRouterHardwareAddress);
	hwaddr_range.length = 0;
	if (isA_CFData(hwaddr_data) != NULL) {
	    hwaddr_range.length = CFDataGetLength(hwaddr_data);
	}
	if (hwaddr_range.length > 0) {
	    hwaddr_range.location = 0;
	    if (hwaddr_range.length > sizeof(lease_p->router_hwaddr)) {
		hwaddr_range.length = sizeof(lease_p->router_hwaddr);
	    }
	    lease_p->router_hwaddr_length = hwaddr_range.length;
	    CFDataGetBytes(hwaddr_data, hwaddr_range, lease_p->router_hwaddr);
	}
    }
    if (ssid != NULL) {
	CFRetain(ssid);
	lease_p->ssid = ssid;
    }
    return (lease_p);

 failed:
    return (NULL);
}