static int init_by_resolv_conf(ares_channel channel)
{
#ifndef WATT32
  char *line = NULL;
#endif
  int status = -1, nservers = 0, nsort = 0;
  struct server_state *servers = NULL;
  struct apattern *sortlist = NULL;

#ifdef WIN32

    /*
  NameServer info via IPHLPAPI (IP helper API):
    GetNetworkParams() should be the trusted source for this.
    Available in Win-98/2000 and later. If that fail, fall-back to
    registry information.

  NameServer Registry:

   On Windows 9X, the DNS server can be found in:
HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\VxD\MSTCP\NameServer

        On Windows NT/2000/XP/2003:
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Tcpip\Parameters\NameServer
        or
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Tcpip\Parameters\DhcpNameServer
        or
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Tcpip\Parameters\{AdapterID}\
NameServer
        or
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Tcpip\Parameters\{AdapterID}\
DhcpNameServer
   */

  HKEY mykey;
  HKEY subkey;
  DWORD data_type;
  DWORD bytes;
  DWORD result;
  char  buf[512];
  win_platform platform;

  if (channel->nservers > -1)  /* don't override ARES_OPT_SERVER */
     return ARES_SUCCESS;

  if (get_iphlpapi_dns_info(buf,sizeof(buf)) > 0)
  {
    status = config_nameserver(&servers, &nservers, buf);
    if (status == ARES_SUCCESS)
      goto okay;
  }

  platform = ares__getplatform();

  if (platform == WIN_NT)
  {
    if (RegOpenKeyEx(
          HKEY_LOCAL_MACHINE, WIN_NS_NT_KEY, 0,
          KEY_READ, &mykey
          ) == ERROR_SUCCESS)
    {
      RegOpenKeyEx(mykey, "Interfaces", 0,
                   KEY_QUERY_VALUE|KEY_ENUMERATE_SUB_KEYS, &subkey);
      if (get_res_nt(mykey, NAMESERVER, &line))
      {
        status = config_nameserver(&servers, &nservers, line);
        free(line);
      }
      else if (get_res_nt(mykey, DHCPNAMESERVER, &line))
      {
        status = config_nameserver(&servers, &nservers, line);
        free(line);
      }
      /* Try the interfaces */
      else if (get_res_interfaces_nt(subkey, NAMESERVER, &line))
      {
        status = config_nameserver(&servers, &nservers, line);
        free(line);
      }
      else if (get_res_interfaces_nt(subkey, DHCPNAMESERVER, &line))
      {
        status = config_nameserver(&servers, &nservers, line);
        free(line);
      }
      RegCloseKey(subkey);
      RegCloseKey(mykey);
    }
  }
  else if (platform == WIN_9X)
  {
    if (RegOpenKeyEx(
          HKEY_LOCAL_MACHINE, WIN_NS_9X, 0,
          KEY_READ, &mykey
          ) == ERROR_SUCCESS)
    {
      if ((result = RegQueryValueEx(
             mykey, NAMESERVER, NULL, &data_type,
             NULL, &bytes
             )
            ) == ERROR_SUCCESS ||
          result == ERROR_MORE_DATA)
      {
        if (bytes)
        {
          line = malloc(bytes+1);
          if (RegQueryValueEx(mykey, NAMESERVER, NULL, &data_type,
                              (unsigned char *)line, &bytes) ==
              ERROR_SUCCESS)
          {
            status = config_nameserver(&servers, &nservers, line);
          }
          free(line);
        }
      }
    }
    RegCloseKey(mykey);
  }

  if (status == ARES_SUCCESS)
    status = ARES_EOF;
  else
    /* Catch the case when all the above checks fail (which happens when there
       is no network card or the cable is unplugged) */
    status = ARES_EFILE;

#elif defined(__riscos__)

  /* Under RISC OS, name servers are listed in the
     system variable Inet$Resolvers, space separated. */

  line = getenv("Inet$Resolvers");
  status = ARES_EOF;
  if (line) {
    char *resolvers = strdup(line), *pos, *space;

    if (!resolvers)
      return ARES_ENOMEM;

    pos = resolvers;
    do {
      space = strchr(pos, ' ');
      if (space)
        *space = '\0';
      status = config_nameserver(&servers, &nservers, pos);
      if (status != ARES_SUCCESS)
        break;
      pos = space + 1;
    } while (space);

    if (status == ARES_SUCCESS)
      status = ARES_EOF;

    free(resolvers);
  }

#elif defined(WATT32)
  int i;

  sock_init();
  for (i = 0; def_nameservers[i]; i++)
      ;
  if (i == 0)
    return ARES_SUCCESS; /* use localhost DNS server */

  nservers = i;
  servers = calloc(i, sizeof(struct server_state));
  if (!servers)
     return ARES_ENOMEM;

  for (i = 0; def_nameservers[i]; i++)
  {
    servers[i].addr.addrV4.s_addr = htonl(def_nameservers[i]);
    servers[i].addr.family = AF_INET;
  }
  status = ARES_EOF;

#elif defined(ANDROID)
  char value[PROP_VALUE_MAX]="";
  __system_property_get("net.dns1", value);
  status = config_nameserver(&servers, &nservers, value);
  if (status == ARES_SUCCESS)
    status = ARES_EOF;
#else
  {
    char *p;
    FILE *fp;
    size_t linesize;
    int error;

    /* Don't read resolv.conf and friends if we don't have to */
    if (ARES_CONFIG_CHECK(channel))
        return ARES_SUCCESS;

    fp = fopen(PATH_RESOLV_CONF, "r");
    if (fp) {
      while ((status = ares__read_line(fp, &line, &linesize)) == ARES_SUCCESS)
      {
        if ((p = try_config(line, "domain", ';')))
          status = config_domain(channel, p);
        else if ((p = try_config(line, "lookup", ';')) && !channel->lookups)
          status = config_lookup(channel, p, "bind", "file");
        else if ((p = try_config(line, "search", ';')))
          status = set_search(channel, p);
        else if ((p = try_config(line, "nameserver", ';')) &&
                 channel->nservers == -1)
          status = config_nameserver(&servers, &nservers, p);
        else if ((p = try_config(line, "sortlist", ';')) &&
                 channel->nsort == -1)
          status = config_sortlist(&sortlist, &nsort, p);
        else if ((p = try_config(line, "options", ';')))
          status = set_options(channel, p);
        else
          status = ARES_SUCCESS;
        if (status != ARES_SUCCESS)
          break;
      }
      fclose(fp);
    }
    else {
      error = ERRNO;
      switch(error) {
      case ENOENT:
      case ESRCH:
        status = ARES_EOF;
        break;
      default:
        DEBUGF(fprintf(stderr, "fopen() failed with error: %d %s\n",
                       error, strerror(error)));
        DEBUGF(fprintf(stderr, "Error opening file: %s\n", PATH_RESOLV_CONF));
        status = ARES_EFILE;
      }
    }

    if ((status == ARES_EOF) && (!channel->lookups)) {
      /* Many systems (Solaris, Linux, BSD's) use nsswitch.conf */
      fp = fopen("/etc/nsswitch.conf", "r");
      if (fp) {
        while ((status = ares__read_line(fp, &line, &linesize)) == ARES_SUCCESS)
        {
          if ((p = try_config(line, "hosts:", '\0')) && !channel->lookups)
            /* ignore errors */
            (void)config_lookup(channel, p, "dns", "files");
        }
        fclose(fp);
      }
      else {
        error = ERRNO;
        switch(error) {
        case ENOENT:
        case ESRCH:
          status = ARES_EOF;
          break;
        default:
          DEBUGF(fprintf(stderr, "fopen() failed with error: %d %s\n",
                         error, strerror(error)));
          DEBUGF(fprintf(stderr, "Error opening file: %s\n", "/etc/nsswitch.conf"));
          status = ARES_EFILE;
        }
      }
    }

    if ((status == ARES_EOF) && (!channel->lookups)) {
      /* Linux / GNU libc 2.x and possibly others have host.conf */
      fp = fopen("/etc/host.conf", "r");
      if (fp) {
        while ((status = ares__read_line(fp, &line, &linesize)) == ARES_SUCCESS)
        {
          if ((p = try_config(line, "order", '\0')) && !channel->lookups)
            /* ignore errors */
            (void)config_lookup(channel, p, "bind", "hosts");
        }
        fclose(fp);
      }
      else {
        error = ERRNO;
        switch(error) {
        case ENOENT:
        case ESRCH:
          status = ARES_EOF;
          break;
        default:
          DEBUGF(fprintf(stderr, "fopen() failed with error: %d %s\n",
                         error, strerror(error)));
          DEBUGF(fprintf(stderr, "Error opening file: %s\n", "/etc/host.conf"));
          status = ARES_EFILE;
        }
      }
    }

    if ((status == ARES_EOF) && (!channel->lookups)) {
      /* Tru64 uses /etc/svc.conf */
      fp = fopen("/etc/svc.conf", "r");
      if (fp) {
        while ((status = ares__read_line(fp, &line, &linesize)) == ARES_SUCCESS)
        {
          if ((p = try_config(line, "hosts=", '\0')) && !channel->lookups)
            /* ignore errors */
            (void)config_lookup(channel, p, "bind", "local");
        }
        fclose(fp);
      }
      else {
        error = ERRNO;
        switch(error) {
        case ENOENT:
        case ESRCH:
          status = ARES_EOF;
          break;
        default:
          DEBUGF(fprintf(stderr, "fopen() failed with error: %d %s\n",
                         error, strerror(error)));
          DEBUGF(fprintf(stderr, "Error opening file: %s\n", "/etc/svc.conf"));
          status = ARES_EFILE;
        }
      }
    }

    if(line)
      free(line);
  }

#endif

  /* Handle errors. */
  if (status != ARES_EOF)
    {
      if (servers != NULL)
        free(servers);
      if (sortlist != NULL)
        free(sortlist);
      return status;
    }

  /* If we got any name server entries, fill them in. */
#ifdef WIN32
okay:
#endif
  if (servers)
    {
      channel->servers = servers;
      channel->nservers = nservers;
    }

  /* If we got any sortlist entries, fill them in. */
  if (sortlist)
    {
      channel->sortlist = sortlist;
      channel->nsort = nsort;
    }

  return ARES_SUCCESS;
}