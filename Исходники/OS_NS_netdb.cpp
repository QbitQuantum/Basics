ACE_BEGIN_VERSIONED_NAMESPACE_DECL

int
ACE_OS::getmacaddress (struct macaddr_node_t *node)
{
  ACE_OS_TRACE ("ACE_OS::getmacaddress");

#if defined (ACE_WIN32) && !defined (ACE_HAS_WINCE)
# if !defined (ACE_HAS_PHARLAP)
    /** Define a structure for use with the netbios routine */
    struct ADAPTERSTAT
    {
      ADAPTER_STATUS adapt;
      NAME_BUFFER    NameBuff [30];
    };

    NCB         ncb;
    LANA_ENUM   lenum;
    unsigned char result;

    ACE_OS::memset (&ncb, 0, sizeof(ncb));
    ncb.ncb_command = NCBENUM;
    ncb.ncb_buffer  = reinterpret_cast<unsigned char*> (&lenum);
    ncb.ncb_length  = sizeof(lenum);

    result = Netbios (&ncb);

    for(int i = 0; i < lenum.length; i++)
      {
        ACE_OS::memset (&ncb, 0, sizeof(ncb));
        ncb.ncb_command  = NCBRESET;
        ncb.ncb_lana_num = lenum.lana [i];

        /** Reset the netbios */
        result = Netbios (&ncb);

        if (ncb.ncb_retcode != NRC_GOODRET)
        {
          return -1;
        }

        ADAPTERSTAT adapter;
        ACE_OS::memset (&ncb, 0, sizeof (ncb));
        ACE_OS::strcpy (reinterpret_cast<char*> (ncb.ncb_callname), "*");
        ncb.ncb_command     = NCBASTAT;
        ncb.ncb_lana_num    = lenum.lana[i];
        ncb.ncb_buffer      = reinterpret_cast<unsigned char*> (&adapter);
        ncb.ncb_length      = sizeof (adapter);

        result = Netbios (&ncb);

        if (result == 0)
        {
          ACE_OS::memcpy (node->node,
              adapter.adapt.adapter_address,
              6);
          return 0;
        }
      }
    return 0;
# else
#   if defined (ACE_HAS_PHARLAP_RT)
      DEVHANDLE ip_dev = (DEVHANDLE)0;
      EK_TCPIPCFG *devp = 0;
      size_t i;
      ACE_TCHAR dev_name[16];

      for (i = 0; i < 10; i++)
        {
          // Ethernet.
          ACE_OS::sprintf (dev_name,
                           "ether%d",
                           i);
          ip_dev = EtsTCPGetDeviceHandle (dev_name);
          if (ip_dev != 0)
            break;
        }
      if (ip_dev == 0)
        return -1;
      devp = EtsTCPGetDeviceCfg (ip_dev);
      if (devp == 0)
        return -1;
      ACE_OS::memcpy (node->node,
            &devp->EthernetAddress[0],
            6);
      return 0;
#   else
      ACE_UNUSED_ARG (node);
      ACE_NOTSUP_RETURN (-1);
#   endif /* ACE_HAS_PHARLAP_RT */
# endif /* ACE_HAS_PHARLAP */
#elif defined (sun)

  /** obtain the local host name */
  char hostname [MAXHOSTNAMELEN];
  ACE_OS::hostname (hostname, sizeof (hostname));

  /** Get the hostent to use with ioctl */
  struct hostent *phost =
    ACE_OS::gethostbyname (hostname);

  if (phost == 0)
    return -1;

  ACE_HANDLE handle =
    ACE_OS::socket (PF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (handle == ACE_INVALID_HANDLE)
    return -1;

  char **paddrs = phost->h_addr_list;

  struct arpreq ar;

  struct sockaddr_in *psa =
    (struct sockaddr_in *)&(ar.arp_pa);

  ACE_OS::memset (&ar,
                  0,
                  sizeof (struct arpreq));

  psa->sin_family = AF_INET;

  ACE_OS::memcpy (&(psa->sin_addr),
                  *paddrs,
                  sizeof (struct in_addr));

  if (ACE_OS::ioctl (handle,
                     SIOCGARP,
                     &ar) == -1)
    {
      ACE_OS::close (handle);
      return -1;
    }

  ACE_OS::close (handle);

  ACE_OS::memcpy (node->node,
                  ar.arp_ha.sa_data,
                  6);

  return 0;

#elif defined (ACE_LINUX) && !defined (ACE_LACKS_NETWORKING)

  // It's easiest to know the first MAC-using interface. Use the BSD
  // getifaddrs function that simplifies access to connected interfaces.
  struct ifaddrs *ifap = 0;
  struct ifaddrs *p_if = 0;

  if (::getifaddrs (&ifap) != 0)
    return -1;

  for (p_if = ifap; p_if != 0; p_if = p_if->ifa_next)
    {
      if (p_if->ifa_addr == 0)
        continue;

      // Check to see if it's up and is not either PPP or loopback
      if ((p_if->ifa_flags & IFF_UP) == IFF_UP &&
          (p_if->ifa_flags & (IFF_LOOPBACK | IFF_POINTOPOINT)) == 0)
        break;
    }
  if (p_if == 0)
    {
      errno = ENODEV;
      ::freeifaddrs (ifap);
      return -1;
    }

  struct ifreq ifr;
  ACE_OS::strcpy (ifr.ifr_name, p_if->ifa_name);
  ::freeifaddrs (ifap);

  ACE_HANDLE handle =
    ACE_OS::socket (PF_INET, SOCK_DGRAM, 0);

  if (handle == ACE_INVALID_HANDLE)
    return -1;

  if (ACE_OS::ioctl (handle/*s*/, SIOCGIFHWADDR, &ifr) < 0)
    {
      ACE_OS::close (handle);
      return -1;
    }

  struct sockaddr* sa =
    (struct sockaddr *) &ifr.ifr_addr;

  ACE_OS::close (handle);

  ACE_OS::memcpy (node->node,
                  sa->sa_data,
                  6);

  return 0;

#elif defined (ACE_HAS_SIOCGIFCONF)

  const long BUFFERSIZE = 4000;
  char buffer[BUFFERSIZE];

  struct ifconf ifc;
  struct ifreq* ifr = 0;

  ACE_HANDLE handle =
    ACE_OS::socket (AF_INET, SOCK_DGRAM, 0);

  if (handle == ACE_INVALID_HANDLE)
    {
      return -1;
    }

  ifc.ifc_len = BUFFERSIZE;
  ifc.ifc_buf = buffer;

  if (ACE_OS::ioctl (handle, SIOCGIFCONF, &ifc) < 0)
    {
      ACE_OS::close (handle);
      return -1;
    }

  for(char* ptr=buffer; ptr < buffer + ifc.ifc_len; )
    {
      ifr = (struct ifreq *) ptr;

      if (ifr->ifr_addr.sa_family == AF_LINK)
        {
          if(ACE_OS::strcmp (ifr->ifr_name, "en0") == 0)
            {
              struct sockaddr_dl* sdl =
                (struct sockaddr_dl *) &ifr->ifr_addr;

              ACE_OS::memcpy (node->node,
                              LLADDR(sdl),
                              6);
            }
        }

      ptr += sizeof(ifr->ifr_name);

      if(sizeof(ifr->ifr_addr) > ifr->ifr_addr.sa_len)
        ptr += sizeof(ifr->ifr_addr);
      else
        ptr += ifr->ifr_addr.sa_len;
    }

  ACE_OS::close (handle);

  return 0;

#else
  ACE_UNUSED_ARG (node);
  ACE_NOTSUP_RETURN (-1);
#endif
}