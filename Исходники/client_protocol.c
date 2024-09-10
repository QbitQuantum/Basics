int IdentifyAgent(int sd)
{
    char uname[CF_BUFSIZE], sendbuff[CF_BUFSIZE];
    char dnsname[CF_MAXVARSIZE], localip[CF_MAX_IP_LEN];
    int ret;

    if ((!SKIPIDENTIFY) && (strcmp(VDOMAIN, CF_START_DOMAIN) == 0))
    {
        Log(LOG_LEVEL_ERR, "Undefined domain name");
        return false;
    }

    if (!SKIPIDENTIFY)
    {
        /* First we need to find out the IP address and DNS name of the socket
           we are sending from. This is not necessarily the same as VFQNAME if
           the machine has a different uname from its IP name (!) This can
           happen on poorly set up machines or on hosts with multiple
           interfaces, with different names on each interface ... */
        struct sockaddr_storage myaddr = {0};
        socklen_t myaddr_len = sizeof(myaddr);

        if (getsockname(sd, (struct sockaddr *) &myaddr, &myaddr_len) == -1)
        {
            Log(LOG_LEVEL_ERR, "Couldn't get socket address. (getsockname: %s)", GetErrorStr());
            return false;
        }

        /* No lookup, just convert the bound address to string. */
        ret = getnameinfo((struct sockaddr *) &myaddr, myaddr_len,
                          localip, sizeof(localip),
                          NULL, 0, NI_NUMERICHOST);
        if (ret != 0)
        {
            Log(LOG_LEVEL_ERR,
                "During agent identification. (getnameinfo: %s)",
                  gai_strerror(ret));
            return false;
        }

        /* dnsname: Reverse lookup of the bound IP address. */
        ret = getnameinfo((struct sockaddr *) &myaddr, myaddr_len,
                          dnsname, sizeof(dnsname), NULL, 0, 0);
        if (ret != 0)
        {
            /* getnameinfo doesn't fail on resolution failure, it just prints
             * the IP, so here something else is wrong. */
            Log(LOG_LEVEL_ERR,
                "During agent identification for '%s'. (getnameinfo: %s)",
                  localip, gai_strerror(ret));
            return false;
        }

        /* getnameinfo() should always return FQDN. Some resolvers will not
         * return FQNAME and missing PTR will give numerical result */
        if ((strlen(VDOMAIN) > 0)                      /* TODO true always? */
            && (!IsIPV6Address(dnsname)) && (!strchr(dnsname, '.')))
        {
            strcat(dnsname, ".");
            strncat(dnsname, VDOMAIN, CF_MAXVARSIZE / 2);
        }

        /* Seems to be a bug in some resolvers that adds garbage, when it just
         * returns the input. */
        if (strncmp(dnsname, localip, strlen(localip)) == 0
            && dnsname[strlen(localip)] != '\0')
        {
            dnsname[strlen(localip)] = '\0';
            Log(LOG_LEVEL_WARNING,
                "getnameinfo() seems to append garbage to unresolvable IPs, bug mitigated by CFEngine but please report your platform!");
        }
    }
    else
    {
        assert(sizeof(localip) >= sizeof(VIPADDRESS));
        strcpy(localip, VIPADDRESS);

        Log(LOG_LEVEL_VERBOSE,
            "skipidentify was promised, so we are trusting and simply announcing the identity as '%s' for this host",
            strlen(VFQNAME) > 0 ? VFQNAME : "skipident");
        if (strlen(VFQNAME) > 0)
        {
            strcpy(dnsname, VFQNAME);
        }
        else
        {
            strcpy(dnsname, "skipident");
        }
    }

/* client always identifies as root on windows */
#ifdef __MINGW32__
    snprintf(uname, sizeof(uname), "%s", "root");
#else
    GetCurrentUserName(uname, sizeof(uname));
#endif

    snprintf(sendbuff, sizeof(sendbuff), "CAUTH %s %s %s %d",
             localip, dnsname, uname, 0);

    if (SendTransaction(sd, sendbuff, 0, CF_DONE) == -1)
    {
        Log(LOG_LEVEL_ERR,
              "During identify agent, could not send auth response. (SendTransaction: %s)", GetErrorStr());
        return false;
    }

    return true;
}