int discover_main(int argc, char *argv[])
{
    /* If this task is excecutated as an NSH built-in function, then the
     * network has already been configured by NSH's start-up logic.
     */

#ifndef CONFIG_NSH_BUILTIN_APPS
    struct in_addr addr;
#if defined(CONFIG_EXAMPLES_DISCOVER_DHCPC) || defined(CONFIG_EXAMPLES_DISCOVER_NOMAC)
    uint8_t mac[IFHWADDRLEN];
#endif
#ifdef CONFIG_EXAMPLES_DISCOVER_DHCPC
    void *handle;
#endif

    /* Many embedded network interfaces must have a software assigned MAC */

#ifdef CONFIG_EXAMPLES_DISCOVER_NOMAC
    mac[0] = 0x00;
    mac[1] = 0xe0;
    mac[2] = 0xde;
    mac[3] = 0xad;
    mac[4] = 0xbe;
    mac[5] = 0xef;
    uip_setmacaddr("eth0", mac);
#endif

    /* Set up our host address */

#ifdef CONFIG_EXAMPLES_DISCOVER_DHCPC
    addr.s_addr = 0;
#else
    addr.s_addr = HTONL(CONFIG_EXAMPLES_DISCOVER_IPADDR);
#endif
    uip_sethostaddr("eth0", &addr);

    /* Set up the default router address */

    addr.s_addr = HTONL(CONFIG_EXAMPLES_DISCOVER_DRIPADDR);
    uip_setdraddr("eth0", &addr);

    /* Setup the subnet mask */

    addr.s_addr = HTONL(CONFIG_EXAMPLES_DISCOVER_NETMASK);
    uip_setnetmask("eth0", &addr);

#ifdef CONFIG_EXAMPLES_DISCOVER_DHCPC
    /* Set up the resolver */

    resolv_init();

    /* Get the MAC address of the NIC */

    uip_getmacaddr("eth0", mac);

    /* Set up the DHCPC modules */

    handle = dhcpc_open(&mac, IFHWADDRLEN);

    /* Get an IP address.  Note:  there is no logic here for renewing the address in this
     * example.  The address should be renewed in ds.lease_time/2 seconds.
     */

    printf("Getting IP address\n");
    if (handle)
    {
        struct dhcpc_state ds;
        (void)dhcpc_request(handle, &ds);
        uip_sethostaddr("eth1", &ds.ipaddr);

        if (ds.netmask.s_addr != 0)
        {
            uip_setnetmask("eth0", &ds.netmask);
        }

        if (ds.default_router.s_addr != 0)
        {
            uip_setdraddr("eth0", &ds.default_router);
        }

        if (ds.dnsaddr.s_addr != 0)
        {
            resolv_conf(&ds.dnsaddr);
        }

        dhcpc_close(handle);
        printf("IP: %s\n", inet_ntoa(ds.ipaddr));
    }

#endif /* CONFIG_EXAMPLES_DISCOVER_DHCPC */
#endif /* CONFIG_NSH_BUILTIN_APPS */

    if (discover_start(NULL) < 0)
    {
        ndbg("Could not start discover daemon.\n");
        return ERROR;
    }

    return OK;
}