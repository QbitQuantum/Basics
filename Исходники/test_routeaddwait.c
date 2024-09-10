void
try_add_route_with_wait(void)
{
    DWORD result;
    HANDLE h_pipe;
    struct rt_msghdr *msg;
    struct sockaddr_storage *pss;
    struct sockaddr_in *psin;
    int msgsize;
    int nbytes;
    int i;

    if (!WaitNamedPipeA(XORPRTM_PIPENAME, NMPWAIT_USE_DEFAULT_WAIT)) {
        fprintf(stderr, "No named pipe instances available.\n");
        return;
    }

    h_pipe = CreateFileA(XORPRTM_PIPENAME, GENERIC_READ | GENERIC_WRITE,
                         0, NULL, OPEN_EXISTING, 0, NULL);
    if (h_pipe == INVALID_HANDLE_VALUE) {
        result = GetLastError();
        fprintf(stderr, "error opening pipe: %d\n", result);
        return;
    }

    fprintf(stderr, "connected\n");

    msgsize = sizeof(*msg) + (sizeof(struct sockaddr_storage) * 3);
    msg = malloc(msgsize);
    if (msg == NULL) {
        fprintf(stderr, "cannot allocate routing socket message\n");
        CloseHandle(h_pipe);
        return;
    }

    ZeroMemory(msg, msgsize);

    /* Fill out routing message header */
    msg->rtm_type = RTM_ADD;
    msg->rtm_msglen = msgsize;
    msg->rtm_version = RTM_VERSION;
    msg->rtm_addrs |= RTA_DST | RTA_NETMASK | RTA_GATEWAY;

    msg->rtm_pid = GetCurrentProcessId();

    pss = (struct sockaddr_storage *)(msg + 1);

    /* Fill out destination XXX 192.0.2.0 in little endian */
    psin = (struct sockaddr_in *)pss;
    psin->sin_family = AF_INET;
    psin->sin_addr.s_addr = 0x000200C0;

    /* Fill out next-hop XXX 192.168.123.6 in little endian */
    psin = (struct sockaddr_in *)++pss;
    psin->sin_family = AF_INET;
    psin->sin_addr.s_addr = 0x067BA8C0;

    /* Fill out netmask XXX 255.255.255.0 in little endian */
    psin = (struct sockaddr_in *)++pss;
    psin->sin_family = AF_INET;
    psin->sin_addr.s_addr = 0x00FFFFFF;

    /* Try to add a route 3 times to test callbacks */
    for (i = 0; i < 3; i++) {
        fprintf(stderr, "attempting to add a route\n", GetLastError());
        result = WriteFile(h_pipe, msg, msgsize, &nbytes, NULL);
        if (result == 0) {
            fprintf(stderr, "error %d writing to pipe\n", GetLastError());
        } else {
            fprintf(stderr, "sent request %d\n", i);
            print_rtmsg(msg, msgsize);
        }

        /* Block and read a single reply. */
        result = ReadFile(h_pipe, msg, msgsize, &nbytes, NULL);
        if (result == 0) {
            fprintf(stderr, "error %d reading from pipe\n", GetLastError());
        } else {
            fprintf(stderr, "got reply %d, printing\n", i);
            print_rtmsg(msg, msgsize);
        }
    }
    fprintf(stderr, "done\n");

    CloseHandle(h_pipe);
    free(msg);
}