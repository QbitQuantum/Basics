int main(int argc, char *argv[]) {
    int conn;
    struct addrinfo hints;
    struct addrinfo *res;
    char *host;
    char *port;
    char rhost[NI_MAXHOST + NI_MAXSERV];
    char rport[NI_MAXSERV];
    int error;
    int opt;
    int sock;

    if (argc < 4) {
        fprintf(stderr, "Usage: %s <host> <port> ['zfs recv' args ...]\n",
                argv[0]);
        exit(2);
    }

    host = argv[1];
    port = argv[2];

    bzero((char *)&hints, sizeof (struct addrinfo));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags |= AI_NUMERICHOST;
    hints.ai_flags |= AI_NUMERICSERV;

    if ((error = getaddrinfo(host, port, &hints, &res))) {
        fprintf(stderr, "zfs_recv: getaddrinfo(): %s\n", gai_strerror(error));
        exit(1);
    }

    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock < 0) {
        perror("zfs_recv: socket()");
        exit(1);
    }

    opt = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
                   (char *)&opt, sizeof (opt)) < 0) {

        perror("zfs_recv: setsockopt()");
        exit(1);
    }

    if (bind(sock, (struct sockaddr *)res->ai_addr, res->ai_addrlen) < 0) {
        perror("zfs_recv: bind()");
        exit(1);
    }

    if (listen(sock, 1) < 0) {
        perror("zfs_recv: listen()");
        exit(1);
    }

    error = getnameinfo(res->ai_addr, res->ai_addrlen, rhost, sizeof (rhost),
                        rport, sizeof (rport), NI_NUMERICHOST|NI_NUMERICSERV);
    if (error != 0) {
        fprintf(stderr, "zfs_recv: getnameinfo(): %s\n", gai_strerror(error));
        exit(1);
    }
    fprintf(stderr, "Waiting for stream on: {'host': '%s', 'port': '%s'}\n",
            rhost, rport);

    freeaddrinfo(res);

    if ((conn = accept(sock, NULL, NULL)) < 0) {
        perror("zfs_recv: accept()");
        exit(1);
    }

    /* redir stdout and stderr to the socket, keep stderr (caller can log it) */
    if (dup2(conn, 0) < 0) {
        perror("zfs_recv: dup2(stdin)");
        exit(1);
    }
    if (dup2(conn, 1) < 0) {
        perror("zfs_recv: dup2(stdout)");
        exit(1);
    }

    /* run the <program> and its args */
    argv++;
    argc--;
    argv[0] = "/usr/sbin/zfs"; // replace host
    argv[1] = "recv";         // replace port
    execvp(*argv, argv);      // now 'zfs recv <args>'

    /* if we got here we failed. */
    perror("zfs_recv: execvp()");
    exit(1);
}