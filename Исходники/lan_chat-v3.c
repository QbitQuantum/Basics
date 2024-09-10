static void update_try_address(char *try_address, size_t try_address_len,
                               char *subnet_address, int host, 
                               struct sockaddr_in *servaddr)
{
    snprintf(try_address, try_address_len, "%s%d", subnet_address, host);

    Inet_pton(AF_INET, try_address, &servaddr->sin_addr);
}