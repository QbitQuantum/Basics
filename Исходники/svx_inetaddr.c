int svx_inetaddr_get_ipport(svx_inetaddr_t *self, char *ip, size_t ip_len, uint16_t *port)
{
    size_t len;

    if(NULL == self || ((NULL == ip || ip_len < SVX_INETADDR_STR_IP_LEN) && NULL == port))
        SVX_LOG_ERRNO_RETURN_ERR(SVX_ERRNO_INVAL, "self:%p, ip:%p, ip_len:%zu, port:%p\n", self, ip, ip_len, port);
    
    switch(self->storage.addr.sa_family)
    {
    case AF_INET:
        if(NULL != ip && ip_len >= SVX_INETADDR_STR_IP_LEN)
        {
            memset(ip, 0, ip_len);
            if(NULL == inet_ntop(AF_INET, &(self->storage.addr4.sin_addr), ip, (socklen_t)ip_len))
                SVX_LOG_ERRNO_RETURN_ERR(errno, NULL);
        }
        if(NULL != port) *port = ntohs(self->storage.addr4.sin_port);
        return 0;
    case AF_INET6:
        if(NULL != ip && ip_len >= SVX_INETADDR_STR_IP_LEN)
        {
            memset(ip, 0, ip_len);
            if(NULL == inet_ntop(AF_INET6, &(self->storage.addr6.sin6_addr), ip, (socklen_t)ip_len))
                SVX_LOG_ERRNO_RETURN_ERR(errno, NULL);
            
            /* append IPv6 link-local address interface name */
            if(IN6_IS_ADDR_LINKLOCAL(&(self->storage.addr6.sin6_addr)) || 
               IN6_IS_ADDR_MC_LINKLOCAL(&(self->storage.addr6.sin6_addr)))
            {
                len = strlen(ip);
                ip[len++] = '%';
                if(NULL == if_indextoname(self->storage.addr6.sin6_scope_id, ip + len))
                    SVX_LOG_ERRNO_RETURN_ERR(errno, NULL);
            }
        }
        if(NULL != port) *port = ntohs(self->storage.addr6.sin6_port);
        return 0;
    default:
        SVX_LOG_ERRNO_RETURN_ERR(SVX_ERRNO_NOTSPT, "family:%u\n", self->storage.addr.sa_family);
    }
}