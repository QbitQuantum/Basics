    int send_message(u_long ip, u_short port, u_long *metaint){
        int rc;
        FILE *stream;
        u_char *line;
        u_char *cp;
        TCPSOCKET *sock;

        u_long baud = DBG_BAUDRATE;
//        u_long radio_ip = inet_addr(RADIO_IPADDR);
        u_short tcpbufsiz = TCPIP_BUFSIZ;
        u_long rx_to = TCPIP_READTIMEOUT;
        u_short mss = TCPIP_MSS;
        puts("create a TCP socket");

        /*
         * Create a TCP socket.
         */
        if ((sock = NutTcpCreateSocket()) == 0) {
            puts("Error: Can't create socket");
            for (; ;);
        }

        puts("set socket options");

        /*
         * Set socket options. Failures are ignored.
         */
        if (NutTcpSetSockOpt(sock, TCP_MAXSEG, &mss, sizeof(mss)))
            printf("Sockopt MSS failed\n");
        if (NutTcpSetSockOpt(sock, SO_RCVTIMEO, &rx_to, sizeof(rx_to)))
            printf("Sockopt TO failed\n");
        if (NutTcpSetSockOpt(sock, SO_RCVBUF, &tcpbufsiz, sizeof(tcpbufsiz)))
            printf("Sockopt rxbuf failed\n");

        /*
         * Connect the TCP server.
         */

        printf("Connecting %s:%u...","83.128.250.123" , 8080);
        if ((rc = NutTcpConnect(sock, inet_addr("83.128.250.123"), 8080))) {
            printf("Error: Connect failed with %d\n", NutTcpError(sock));
            return 0;
        }
        puts("OK");

        if ((stream = _fdopen((int) sock, "r+b")) == 0) {
            puts("Error: Can't create stream");
            return 0;
        }

        /*
         * Send the HTTP request.
         */
        printf("GET %s HTTP/1.0\n\n", "/api/telegram");
        fprintf(stream, "GET %s HTTP/1.0\r\n", "/api/telegram");
        fprintf(stream, "Host: %s\r\n", "83.128.250.123");
        fprintf(stream, "User-Agent: Ethernut\r\n");
        fprintf(stream, "Accept: */*\r\n");
        fprintf(stream, "Connection: close\r\n");
        fputs("\r\n", stream);
        fflush(stream);

        /*
         * Receive the HTTP header.
         */
        line = malloc(MAX_HEADERLINE);
        while (fgets(line, MAX_HEADERLINE, stream)) {

            /*
             * Chop off the carriage return at the end of the line. If none
             * was found, then this line was probably too large for our buffer.
             */
            cp = strchr(line, '\r');
            if (cp == 0) {
                puts("Warning: Input buffer overflow");
                continue;
            }
            *cp = 0;

            /*
             * The header is terminated by an empty line.
             */
            if (*line == 0) {
                break;
            }
            printf("%s\n", line);
        }
        putchar('\n');

        free(line);
        return 0;
    }