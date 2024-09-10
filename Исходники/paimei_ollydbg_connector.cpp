void paimei_connect (void)
{
    hostent      *he;
    sockaddr_in  sin;
    in_addr      addr;
    WSADATA      wsa_data;

    char server[256];

    memset(server, 0, sizeof(server));
    strcpy(server, "127.0.0.1");

    // if we are already connected then to do nothing.
    if (connection)
        return;

    if (Gettext("PaiMei Server:", server, 0x00, NM_NONAME, FIXEDFONT) == -1)
        return;

    // initialize winsock.
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
    {
        olly_add_to_list(0, 1, "[!] "PLUGIN_NAME"> WSAStartup() failed.");
        return;
    }

    // confirm that the requested winsock version is supported.
    if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 2)
    {
        WSACleanup();
        olly_add_to_list(0, 1, PLUGIN_NAME"> Winsock version 2.2 not found.");
        return;
    }

    // if the provided server address is a hostname, then resolve it with gethostbyname().
    if (isalpha(server[0]))
    {
        if ((he = gethostbyname(server)) == NULL)
        {
            olly_add_to_list(0, 1, "[!] "PLUGIN_NAME"> Unable to resolve name: %s", server);
            return;
        }
    }
    // otherwise resolve the server address with gethostbyaddr().
    else
    {
        addr.s_addr = inet_addr(server);

        if ((he = gethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET)) == NULL)
        {
            olly_add_to_list(0, 1, "[!] "PLUGIN_NAME"> Unable to resolve address");
            return;
        }
    }

    // create a socket.
    if ((connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        WSACleanup();
        olly_add_to_list(0, 1, "[!] "PLUGIN_NAME"> Failed to create socket.");
        return;
    }

    // connect to the server.
    sin.sin_family = AF_INET;
    sin.sin_addr   = *((LPIN_ADDR)*he->h_addr_list);
    sin.sin_port   = htons(7033);

    if (connect(connection, (SOCKADDR *) &sin, sizeof(sin)) == SOCKET_ERROR)
    {
        WSACleanup();
        olly_add_to_list(0, 1, "[!] "PLUGIN_NAME"> Failed to connect to server.");
        return;
    }
}