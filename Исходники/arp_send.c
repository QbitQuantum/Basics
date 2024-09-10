int arp_send(in_addr_t ipaddr)
{
    FAR struct net_driver_s *dev;
    struct arp_notify_s notify;
    struct timespec delay;
    struct arp_send_s state;
    net_lock_t save;
    int ret;

    /* First check if destination is a local broadcast. */

    if (ipaddr == INADDR_BROADCAST)
    {
        /* We don't need to send the ARP request */

        return OK;
    }

#ifdef CONFIG_NET_IGMP
    /* Check if the destination address is a multicast address
     *
     * - IPv4: multicast addresses lie in the class D group -- The address range
     *   224.0.0.0 to 239.255.255.255 (224.0.0.0/4)
     *
     * - IPv6 multicast addresses are have the high-order octet of the
     *   addresses=0xff (ff00::/8.)
     */

    if (NTOHL(ipaddr) >= 0xe0000000 && NTOHL(ipaddr) <= 0xefffffff)
    {
        /* We don't need to send the ARP request */

        return OK;
    }
#endif

    /* Get the device that can route this request */

#ifdef CONFIG_NETDEV_MULTINIC
    dev = netdev_findby_ipv4addr(g_ipv4_allzeroaddr, ipaddr);
#else
    dev = netdev_findby_ipv4addr(ipaddr);
#endif
    if (!dev)
    {
        ndbg("ERROR: Unreachable: %08lx\n", (unsigned long)ipaddr);
        ret = -EHOSTUNREACH;
        goto errout;
    }

#ifdef CONFIG_NET_MULTILINK
    /* ARP support is only built if the Ethernet data link is supported.
     * However, if we are supporting multiple network devices and using
     * different link level protocols then we can get here for other
     * link protocols as well.  Continue and send the ARP request only
     * if this device uses the Ethernet data link protocol.
     */

    if (dev->d_lltype != NET_LL_ETHERNET)
    {
        return OK;
    }
#endif

    /* Check if the destination address is on the local network. */

    if (!net_ipv4addr_maskcmp(ipaddr, dev->d_ipaddr, dev->d_netmask))
    {
        in_addr_t dripaddr;

        /* Destination address is not on the local network */

#ifdef CONFIG_NET_ROUTE

        /* We have a routing table.. find the correct router to use in
         * this case (or, as a fall-back, use the device's default router
         * address).  We will use the router IP address instead of the
         * destination address when determining the MAC address.
         */

        netdev_ipv4_router(dev, ipaddr, &dripaddr);
#else
        /* Use the device's default router IP address instead of the
         * destination address when determining the MAC address.
         */

        net_ipv4addr_copy(dripaddr, dev->d_draddr);
#endif
        ipaddr = dripaddr;
    }

    /* Allocate resources to receive a callback.  This and the following
     * initialization is performed with the network lock because we don't
     * want anything to happen until we are ready.
     */

    save = net_lock();
    state.snd_cb = arp_callback_alloc(&g_arp_conn);
    if (!state.snd_cb)
    {
        ndbg("ERROR: Failed to allocate a cllback\n");
        ret = -ENOMEM;
        goto errout_with_lock;
    }

    /* Initialize the state structure. This is done with interrupts
     * disabled
     */

    (void)sem_init(&state.snd_sem, 0, 0); /* Doesn't really fail */
    state.snd_retries   = 0;              /* No retries yet */
    state.snd_ipaddr    = ipaddr;         /* IP address to query */

#ifdef CONFIG_NETDEV_MULTINIC
    /* Remember the routing device name */

    strncpy((FAR char *)state.snd_ifname, (FAR const char *)dev->d_ifname, IFNAMSIZ);
#endif

    /* Now loop, testing if the address mapping is in the ARP table and re-sending the ARP request if it is not.
     */

    ret = -ETIMEDOUT; /* Assume a timeout failure */

    while (state.snd_retries < CONFIG_ARP_SEND_MAXTRIES)
    {
        /* Check if the address mapping is present in the ARP table.  This
         * is only really meaningful on the first time through the loop.
         *
         * NOTE: If the ARP table is large than this could be a performance
         * issue.
         */

        if (arp_find(ipaddr))
        {
            /* We have it!  Break out with success */

            ret = OK;
            break;
        }

        /* Set up the ARP response wait BEFORE we send the ARP request */

        arp_wait_setup(ipaddr, &notify);

        /* Arm/re-arm the callback */

        state.snd_sent      = false;
        state.snd_cb->flags = ARP_POLL;
        state.snd_cb->priv  = (FAR void *)&state;
        state.snd_cb->event = arp_send_interrupt;

        /* Notify the device driver that new TX data is available.
         * NOTES: This is in essence what netdev_ipv4_txnotify() does, which
         * is not possible to call since it expects a in_addr_t as
         * its single argument to lookup the network interface.
         */

        dev->d_txavail(dev);

        /* Wait for the send to complete or an error to occur: NOTES: (1)
         * net_lockedwait will also terminate if a signal is received, (2)
         * interrupts may be disabled! They will be re-enabled while the
         * task sleeps and automatically re-enabled when the task restarts.
         */

        do
        {
            (void)net_lockedwait(&state.snd_sem);
        }
        while (!state.snd_sent);

        /* Now wait for response to the ARP response to be received.  The
         * optimal delay would be the work case round trip time.
         * NOTE: The network is locked.
         */

        delay.tv_sec  = CONFIG_ARP_SEND_DELAYSEC;
        delay.tv_nsec = CONFIG_ARP_SEND_DELAYNSEC;

        ret = arp_wait(&notify, &delay);

        /* arp_wait will return OK if and only if the matching ARP response
         * is received.  Otherwise, it will return -ETIMEDOUT.
         */

        if (ret == OK)
        {
            break;
        }

        /* Increment the retry count */

        state.snd_retries++;
    }

    sem_destroy(&state.snd_sem);
    arp_callback_free(&g_arp_conn, state.snd_cb);
errout_with_lock:
    net_unlock(save);
errout:
    return ret;
}