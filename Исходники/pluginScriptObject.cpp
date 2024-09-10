std::string
GnashPluginScriptObject::readPlayer(int fd)
{
    std::string empty;

    if (fd <= 0) {
        log_error("Invalid fd passed");
        return empty;
    }

    // Wait for some data from the player
    int bytes = 0;

    pollfd pfds[1] = { pollfd() };
    pfds[0].fd = fd;
    pfds[0].events = POLLIN;

    int rv = poll(pfds, 1 /* arraySize */, 2000 /* ms */);

    // No data yet
    if (rv <= 0) {
        return empty;
    }

#ifndef _WIN32
    rv = ioctl(fd, FIONREAD, &bytes);
#else
    rv = ioctlSocket(fd, FIONREAD, &bytes);
#endif
    if (rv < 0) {
        log_error("FIONREAD ioctl failed, unable to get network buffer length");
        return empty;
    }
    log_debug("There are %d bytes in the network buffer", bytes);

    if (bytes <= 0) {
        return empty;
    }

    char buf[bytes];

    int ret = ::read(fd, buf, bytes);
    if (ret <= 0 || ret > bytes) {
        return empty;
    }

    return std::string(buf, ret);
}