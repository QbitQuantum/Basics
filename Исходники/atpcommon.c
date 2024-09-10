int xbind_connect(const len_and_sockaddr *lsa, const char *ip)
{
	int fd;
    /*Start of MNT 2008-10-13 14:40 for 传输超时检测 by z65940*/
    g_TimeoutCnt = ATP_CONNECT_TIMEOUT_D;  // 每个命令的超时检测
    /*End of MNT 2008-10-13 14:40 for by z65940*/

    #if 0
    /*Added by yehuisheng00183935@20110806 修改IPv6链路地址访问问题--使用链路地址时，必须指定参数"sin6_scope_id"*/
    if ( AF_INET6 == lsa->u.sa.sa_family )
    {
        if (IN6_IS_ADDR_LINKLOCAL(&(((struct sockaddr_in6 *)(&(lsa->u.sa)))->sin6_addr)))
        {
            ((struct sockaddr_in6 *)(&(lsa->u.sa)))->sin6_scope_id = if_nametoindex("br0");
        }
    }
    /*Added by yehuisheng00183935@20110806 修改IPv6链路地址访问问题--使用链路地址时，必须指定参数"sin6_scope_id"*/
    #endif
    if (NULL == ip)
    {
        // No bind, the same as xconnect_stream
        fd = xconnect_stream(lsa);
        /*Start of MNT 2008-10-13 14:40 for 传输超时检测 by z65940*/
        g_TimeoutCnt = -1;
        /*End of MNT 2008-10-13 14:40 for by z65940*/
        return fd;
    }

    // Bind to specified local interface
    //fd = create_and_bind_stream_or_die(ip, get_nport(&(lsa->u.sa)));
    fd = create_and_bind_stream_or_die(ip, 0);
    xconnect(fd, &(lsa->u.sa), lsa->len);
    /*Start of MNT 2008-10-13 14:40 for 传输超时检测 by z65940*/
    g_TimeoutCnt = -1;
    /*End of MNT 2008-10-13 14:40 for by z65940*/
	return fd;
}