struct DomainSocket *new_domain_socket(const char *path, int access_mask, 
    void (*read_callback)(struct DSClient *client), 
    void (*write_callback)(struct DSClient *client), 
    void (*error_callback)(struct DSClient *client),
    int listen_backlog)
{
    struct linger ling = {0, 0};
    struct sockaddr_un addr;
    struct stat tstat;
    int flags = 1;
    int old_umask;
    struct DomainSocket *uds;
    
    assert(path != NULL);
    
    uds = malloc(sizeof(struct DomainSocket));
    uds->path = strdup(path);
    uds->fd = -1;
    uds->read_callback = read_callback;
    uds->write_callback = write_callback;
    uds->error_callback = error_callback;
    
    if ((uds->fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        _DEBUG("%s: socket() failed\n", __FUNCTION__);
        free_domain_socket(uds);
        return NULL;
    }
    
    // clean up a previous socket file if we left it around
    if (lstat(path, &tstat) == 0) { 
        if (S_ISSOCK(tstat.st_mode)) {
            unlink(path);
        }
    }
    
    // @jayridge doesn't think this does anything here
    setsockopt(uds->fd, SOL_SOCKET, SO_REUSEADDR, (void *)&flags, sizeof(flags));
    // @jayridge doesn't think this does anything here
    setsockopt(uds->fd, SOL_SOCKET, SO_KEEPALIVE, (void *)&flags, sizeof(flags));
    setsockopt(uds->fd, SOL_SOCKET, SO_LINGER, (void *)&ling, sizeof(ling));
    
    // clears nonstandard fields in some impementations that otherwise mess things up
    memset(&addr, 0, sizeof(addr));
    
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
    assert(strcmp(addr.sun_path, path) == 0);
    old_umask = umask(~(access_mask & 0777));
    if (bind(uds->fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        _DEBUG("%s: bind() failed\n", __FUNCTION__);
        free_domain_socket(uds);
        umask(old_umask);
        return NULL;
    }
    umask(old_umask);
    
    if (listen(uds->fd, listen_backlog) == -1) {
        _DEBUG("%s: listen() failed\n", __FUNCTION__);
        free_domain_socket(uds);
        return NULL;
    }
    
    if (evutil_make_socket_nonblocking(uds->fd) == -1) {
        _DEBUG("%s: evutil_make_socket_nonblocking() failed\n", __FUNCTION__);
        free_domain_socket(uds);
        return NULL;
    }
    
    event_set(&uds->ev, uds->fd, EV_READ | EV_PERSIST, accept_socket, uds);
    if (event_add(&uds->ev, NULL) == -1) {
        _DEBUG("%s: event_add() failed\n", __FUNCTION__);
        free_domain_socket(uds);
        return NULL;
    }
    
    return uds;
}