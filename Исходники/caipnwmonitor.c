CAInterface_t *CAFindInterfaceChange()
{
    char buf[MAX_INTERFACE_INFO_LENGTH] = { 0 };
    struct ifconf ifc  = { .ifc_len = MAX_INTERFACE_INFO_LENGTH, .ifc_buf = buf };

    int s = caglobals.ip.u6.fd != -1 ? caglobals.ip.u6.fd : caglobals.ip.u4.fd;
    if (ioctl(s, SIOCGIFCONF, &ifc) < 0)
    {
        OIC_LOG_V(ERROR, TAG, "SIOCGIFCONF failed: %s", strerror(errno));
        return NULL;
    }

    CAInterface_t *foundNewInterface = NULL;

    struct ifreq* ifr = ifc.ifc_req;
    size_t interfaces = ifc.ifc_len / sizeof (ifc.ifc_req[0]);
    size_t ifreqsize = ifc.ifc_len;

    CAIfItem_t *previous = (CAIfItem_t *)OICMalloc(ifreqsize);
    if (!previous)
    {
        OIC_LOG(ERROR, TAG, "OICMalloc failed");
        return NULL;
    }

    memcpy(previous, caglobals.ip.nm.ifItems, ifreqsize);
    size_t numprevious = caglobals.ip.nm.numIfItems;

    if (ifreqsize > caglobals.ip.nm.sizeIfItems)
    {

        CAIfItem_t *items = (CAIfItem_t *)OICRealloc(caglobals.ip.nm.ifItems, ifreqsize);
        if (!items)
        {
            OIC_LOG(ERROR, TAG, "OICRealloc failed");
            OICFree(previous);
            return NULL;
        }
        caglobals.ip.nm.ifItems = items;
        caglobals.ip.nm.sizeIfItems = ifreqsize;
    }

    caglobals.ip.nm.numIfItems = 0;
    for (size_t i = 0; i < interfaces; i++)
    {
        struct ifreq* item = &ifr[i];
        char *name = item->ifr_name;
        struct sockaddr_in *sa4 = (struct sockaddr_in *)&item->ifr_addr;
        uint32_t ipv4addr = sa4->sin_addr.s_addr;

        if (ioctl(s, SIOCGIFFLAGS, item) < 0)
        {
            OIC_LOG_V(ERROR, TAG, "SIOCGIFFLAGS failed: %s", strerror(errno));
            continue;
        }
        int16_t flags = item->ifr_flags;
        if ((flags & IFF_LOOPBACK) || !(flags & IFF_RUNNING))
        {
            continue;
        }
        if (ioctl(s, SIOCGIFINDEX, item) < 0)
        {
            OIC_LOG_V(ERROR, TAG, "SIOCGIFINDEX failed: %s", strerror(errno));
            continue;
        }

        int ifIndex = item->ifr_ifindex;
        caglobals.ip.nm.ifItems[i].ifIndex = ifIndex;  // refill interface list
        caglobals.ip.nm.numIfItems++;

        if (foundNewInterface)
        {
            continue;   // continue updating interface list
        }

        // see if this interface didn't previously exist
        bool found = false;
        for (size_t j = 0; j < numprevious; j++)
        {
            if (ifIndex == previous[j].ifIndex)
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            OIC_LOG_V(INFO, TAG, "Interface found: %s", name);
            continue;
        }

        foundNewInterface = CANewInterfaceItem(ifIndex, name, AF_INET, ipv4addr, flags);
    }

    OICFree(previous);
    return foundNewInterface;
}