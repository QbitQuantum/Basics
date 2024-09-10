/**
 * \brief Get interface for a destination route.
 * \param addr destination address
 * \param src source address, this parameter will be filled in function succeed
 * \return 0 if success, -1 otherwise
 */
static int get_source_for_destination(struct sockaddr* dst, struct sockaddr_storage* src)
{
  DWORD ifindex = 0;
  IP_ADAPTER_ADDRESSES* allAdapters = NULL;
  IP_ADAPTER_ADDRESSES* adapter = NULL;
  ULONG size = ADAPTERS_DEFAULT_SIZE;
  ULONG ret = 0;
  BOOL found = FALSE;

  /* need a valid pointer */
  if(!src || !dst)
  {
    return -1;
  }

  /* get output interface index for specific destination address */
  if(GetBestInterfaceEx(dst, &ifindex) != NO_ERROR)
  {
    return -1;
  }

  do
  {
    /* we should loop only if host has more than 
     * (ADAPTERS_DEFAULT_SIZE / sizeof(IP_ADAPTER_ADDRESSES)) interfaces
     */
    allAdapters = malloc(size);

    if(!allAdapters)
    {
      /* out of memory */
      return -1;
    }

    /* get the list of host addresses and try to find 
     * the index
     */
    ret = GetAdaptersAddresses(dst->sa_family, /* return same address family as destination */
        GAA_FLAG_INCLUDE_ALL_INTERFACES | GAA_FLAG_INCLUDE_PREFIX | GAA_FLAG_SKIP_DNS_SERVER | 
        GAA_FLAG_SKIP_FRIENDLY_NAME | GAA_FLAG_SKIP_MULTICAST,
        NULL, /* reserved */
        allAdapters,
        &size);

    if(ret == ERROR_BUFFER_OVERFLOW)
    {
      /* free memory as the loop will allocate again with
       * proper size
       */
      free(allAdapters);
    }
  }while(ret == ERROR_BUFFER_OVERFLOW);

  if(ret != ERROR_SUCCESS)
  {
    free(allAdapters);
    return -1;
  }

  adapter = allAdapters;

  while(adapter)
  {
    /* find the right adapter for interface index return by GetBestInterface */
    if(dst->sa_family == AF_INET && (adapter->IfIndex == ifindex))
    {
      IP_ADAPTER_UNICAST_ADDRESS* unicast = adapter->FirstUnicastAddress;
      if(unicast != NULL)
      {
        struct sockaddr_in* addr = (struct sockaddr_in*)unicast->Address.lpSockaddr;

        memcpy(src, addr, sizeof(struct sockaddr_in));
        found = TRUE;

        /* found source address, break the loop */
        break;
      }
    }
    else if(dst->sa_family == AF_INET6 && (adapter->Ipv6IfIndex == ifindex))
    {
      /* XXX multihoming on IPv6 interfaces, they can have 
       * multiple global addresses (+ link-local address), handle this case 
       */
      IP_ADAPTER_UNICAST_ADDRESS* unicast = adapter->FirstUnicastAddress;
      if(unicast != NULL)
      {
        struct sockaddr_in6* addr = (struct sockaddr_in6*)unicast->Address.lpSockaddr;

        memcpy(src, addr, sizeof(struct sockaddr_in6));
        found = TRUE;

        /* found source address, break the loop */
        break;
      }
    }

    adapter = adapter->Next;
  }

  /* cleanup */
  free(allAdapters);

  return found ? 0 : -1;
}