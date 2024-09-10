static char *
port_to_service(int port)
{
    struct servent *service;

    if ((service = getservbyport(htons(port), "udp")))
        return service->s_name;

    return NULL;
}