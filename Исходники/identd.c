static int identd_ipv6(char *username)
{
        int sok, read_sok, len;
        char *p;
        char buf[256];
        char outbuf[256];
        char ipv6buf[60];
        DWORD ipv6buflen = sizeof(ipv6buf);
        struct sockaddr_in6 addr;

        sok = socket(AF_INET6, SOCK_STREAM, 0);

        if (sok == INVALID_SOCKET) {
                free(username);
                return 0;
        }

        len = 1;
        setsockopt(sok, SOL_SOCKET, SO_REUSEADDR, (char *)&len, sizeof(len));

        memset(&addr, 0, sizeof(addr));
        addr.sin6_family = AF_INET6;
        addr.sin6_port = htons(113);

        if (bind(sok, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR) {
                closesocket(sok);
                free(username);
                return 0;
        }

        if (listen(sok, 1) == SOCKET_ERROR) {
                closesocket(sok);
                free(username);
                return 0;
        }

        len = sizeof(addr);
        read_sok = accept(sok, (struct sockaddr *)&addr, &len);
        closesocket(sok);

        if (read_sok == INVALID_SOCKET) {
                free(username);
                return 0;
        }

        identd_ipv6_is_running = FALSE;

        if (WSAAddressToString((struct sockaddr *)&addr,
                               sizeof(addr),
                               NULL,
                               &ipv6buf,
                               &ipv6buflen) == SOCKET_ERROR) {
                snprintf(ipv6buf, sizeof(ipv6buf) - 1, "[SOCKET ERROR: 0x%X]", WSAGetLastError());
        }

        snprintf(outbuf, sizeof(outbuf), "%%\tServicing ident request from %s\n", ipv6buf);
        PrintText(current_sess, outbuf);

        recv(read_sok, buf, sizeof(buf) - 1, 0);
        /* buf[sizeof (buf) - 1] = 0; */ /* ensure null termination */

        p = strchr(buf, ',');

        if (p) {
                snprintf(outbuf,
                         sizeof(outbuf) - 1,
                         "%d, %d : USERID : UNIX : %s\r\n",
                         atoi(buf),
                         atoi(p + 1),
                         username);
                outbuf[sizeof(outbuf) - 1] = 0; /* ensure null termination */
                send(read_sok, outbuf, strlen(outbuf), 0);
        }

        sleep(1);
        closesocket(read_sok);
        free(username);

        return 0;
}