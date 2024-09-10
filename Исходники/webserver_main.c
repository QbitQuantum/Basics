int webserver_main(int argc, char *argv[])
#endif
{
  struct in_addr addr;
#if defined(CONFIG_EXAMPLES_WEBSERVER_DHCPC) || defined(CONFIG_EXAMPLES_WEBSERVER_NOMAC)
  uint8_t mac[IFHWADDRLEN];
#endif
#ifdef CONFIG_EXAMPLES_WEBSERVER_DHCPC
  void *handle;
#endif

/* Many embedded network interfaces must have a software assigned MAC */

#ifdef CONFIG_EXAMPLES_WEBSERVER_NOMAC
  mac[0] = 0x00;
  mac[1] = 0xe0;
  mac[2] = 0xde;
  mac[3] = 0xad;
  mac[4] = 0xbe;
  mac[5] = 0xef;
  netlib_setmacaddr("eth0", mac);
#endif

  /* Set up our host address */

#ifdef CONFIG_EXAMPLES_WEBSERVER_DHCPC
  addr.s_addr = 0;
#else
  addr.s_addr = HTONL(CONFIG_EXAMPLES_WEBSERVER_IPADDR);
#endif
  netlib_set_ipv4addr("eth0", &addr);

  /* Set up the default router address */

  addr.s_addr = HTONL(CONFIG_EXAMPLES_WEBSERVER_DRIPADDR);
  netlib_set_dripv4addr("eth0", &addr);

  /* Setup the subnet mask */

  addr.s_addr = HTONL(CONFIG_EXAMPLES_WEBSERVER_NETMASK);
  netlib_set_ipv4netmask("eth0", &addr);

#ifdef CONFIG_EXAMPLES_WEBSERVER_DHCPC
  /* Get the MAC address of the NIC */

  netlib_getmacaddr("eth0", mac);

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
        netlib_set_ipv4addr("eth0", &ds.ipaddr);

        if (ds.netmask.s_addr != 0)
          {
            netlib_set_ipv4netmask("eth0", &ds.netmask);
          }

        if (ds.default_router.s_addr != 0)
          {
            netlib_set_dripv4addr("eth0", &ds.default_router);
          }

        if (ds.dnsaddr.s_addr != 0)
          {
            netlib_set_ipv4dnsaddr(&ds.dnsaddr);
          }

        dhcpc_close(handle);
        printf("IP: %s\n", inet_ntoa(ds.ipaddr));
    }
#endif

#ifdef CONFIG_NET_TCP
  printf("Starting webserver\n");
  httpd_init();
  cgi_register();
  httpd_listen();
#endif

  while (1)
    {
      sleep(3);
      printf("webserver_main: Still running\n");
#if CONFIG_NFILE_DESCRIPTORS > 0
      fflush(stdout);
#endif
    }

  return 0;
}