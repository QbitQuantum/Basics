int test_udp_runner()
{
    test_udp_addr addr;
    char ifname[IF_NAMESIZE + 1];
    char ipv4[SVX_INETADDR_STR_IP_LEN];
    char ipv6[SVX_INETADDR_STR_IP_LEN];
    char ipv6_grp[SVX_INETADDR_STR_IP_LEN];

    if(test_udp_interface_selector(ifname, sizeof(ifname), ipv4, sizeof(ipv4), ipv6, sizeof(ipv6)))
    {
        SVX_LOG_ERR("UDP test failed.\n"
                    "We need an interface which support the following features:\n"
                    "1. IPv4 address (unicast & multicast)\n"
                    "2. IPv6 link-local address (unicast & multicast)\n");
        exit(1);
    }

    addr.ifindex = if_nametoindex(ifname);
    snprintf(ipv6_grp, sizeof(ipv6_grp), "ff02::7:8:9%%%s", ifname);

    /* unicast, IPv4 */
    addr.server_ip   = "127.0.0.1";
    addr.server_port = 30000;
    addr.client_ip   = NULL;
    addr.client_port = 0;
    test_udp_do(&addr);

    /* unicast, IPv6 */
    addr.server_ip   = "::1";
    addr.server_port = 30000;
    addr.client_ip   = NULL;
    addr.client_port = 0;
    test_udp_do(&addr);
    
    /* multicast, IPv4 */
    addr.server_ip   = "239.7.8.9";
    addr.server_port = 30000;
    addr.client_ip   = NULL;
    addr.client_port = 0;
    test_udp_do(&addr);
    
    /* multicast, IPv6 */
    addr.server_ip   = ipv6_grp;
    addr.server_port = 30000;
    addr.client_ip   = NULL;
    addr.client_port = 0;
    test_udp_do(&addr);

    /* source specific multicast IPv4 */
    addr.server_ip   = "239.7.8.9";
    addr.server_port = 30000;
    addr.client_ip   = ipv4;
    addr.client_port = 40000;
    test_udp_do(&addr);

    /* source specific multicast IPv6 */
    addr.server_ip   = ipv6_grp;
    addr.server_port = 30000;
    addr.client_ip   = ipv6;
    addr.client_port = 40000;
    test_udp_do(&addr);
    
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    return 0;
}