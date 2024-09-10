void* server_echo(void* context) {
    char buffer[1000];
    Context* ctx = (Context*) context;
    Socket client = ctx->socket;
    if (!local) {
        char ip_addr[Socket::IP_ADDR_BUFF_SIZE];
        client.remote_address(ip_addr);
        SBL_TEST_EQ_STR(ip_addr, loopback_addr);
        int port = client.local_address(ip_addr);
        SBL_TEST_EQ_STR(ip_addr, loopback_addr);
        SBL_TEST_EQ(port, loopback_port);
    }
    do {
        if (client.recv(buffer, sizeof buffer ) == 0) {
            return NULL;
        }
        client.send(buffer);
    } while (1);
    return NULL;
}