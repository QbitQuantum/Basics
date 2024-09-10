static int
impl_dummy_server(void)
{
    int dummy_server = -1;

    /* Create our dummy sock. */
    struct sockaddr_un dummy_addr;
    char *socket_path = tempnam("/tmp", ".huptime");

    memset(&dummy_addr, 0, sizeof(struct sockaddr_un));
    dummy_addr.sun_family = AF_UNIX;
    strncpy(dummy_addr.sun_path, socket_path, sizeof(dummy_addr.sun_path)-1);

    /* Create a dummy server. */
    dummy_server = socket(AF_UNIX, SOCK_STREAM, 0);
    if( dummy_server < 0 )
    {
        fprintf(stderr, "Unable to create unix socket?");
        return -1;
    }
    if( fcntl(dummy_server, F_SETFD, FD_CLOEXEC) < 0 )
    {
        close(dummy_server);
        fprintf(stderr, "Unable to set cloexec?");
        return -1;
    }
    if( libc.bind(
            dummy_server,
            (struct sockaddr*)&dummy_addr,
            sizeof(struct sockaddr_un)) < 0 )
    {
        close(dummy_server);
        fprintf(stderr, "Unable to bind unix socket?");
        return -1;
    }
    if( libc.listen(dummy_server, 1) < 0 )
    {
        close(dummy_server);
        fprintf(stderr, "Unable to listen on unix socket?");
        return -1;
    }

    /* Connect a dummy client. */
    int dummy_client = socket(AF_UNIX, SOCK_STREAM, 0);
    if( dummy_client < 0 )
    {
        close(dummy_server);
        fprintf(stderr, "Unable to create unix socket?");
        return -1;
    }
    if( fcntl(dummy_client, F_SETFD, FD_CLOEXEC) < 0 )
    {
        close(dummy_server);
        close(dummy_client);
        fprintf(stderr, "Unable to set cloexec?");
        return -1;
    }
    if( connect(
            dummy_client,
            (struct sockaddr*)&dummy_addr,
            sizeof(struct sockaddr_un)) < 0 )
    {
        close(dummy_server);
        close(dummy_client);
        fprintf(stderr, "Unable to connect dummy client?");
        return -1;
    }

    /* Put the client into an error state. */
    int dummy_fd = libc.accept(dummy_server, NULL, 0);
    if( dummy_fd < 0 )
    {
        fprintf(stderr, "Unable to accept internal client?");
        close(dummy_server);
        close(dummy_client);
        return -1;
    }
    close(dummy_fd);

    /* Save the dummy info. */
    fdinfo_t* dummy_info = alloc_info(DUMMY);
    if( dummy_info == NULL )
    {
        fprintf(stderr, "Unable to allocate dummy info?");
        return -1;
    }
    dummy_info->dummy.client = dummy_client;
    fd_save(dummy_server, dummy_info);
    inc_ref(dummy_info);
    fd_save(dummy_client, dummy_info);

    /* Ensure that it's unlinked. */
    unlink(socket_path);
    free(socket_path);

    return dummy_server;
}