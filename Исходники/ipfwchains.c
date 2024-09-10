static char* port_to_service(int port, unsigned short proto)
{
        struct servent *service;

        if (proto == IPPROTO_TCP && (service = getservbyport(htons(port), "tcp")) != NULL)
                return service->s_name;
        else if (proto == IPPROTO_UDP &&
                        (service = getservbyport(htons(port), "udp")) != NULL)
                return service->s_name;
        else
                return (char *) NULL;
}