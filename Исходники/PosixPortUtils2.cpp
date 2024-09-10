int VMPI_getpeername(int socket, struct sockaddr *address, socklen_t *address_len)
{
    return getpeername( socket, address, address_len );
}