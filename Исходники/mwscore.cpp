void connect_score(char const *addr, unsigned short port, IStatus *status, ISockets *socks) {
    istatus = status;
    sockaddr_in sin;
    unsigned int buf[4];
    unsigned char ucbuf[4];
    if (4 == sscanf(addr, "%d.%d.%d.%d", &buf[0], &buf[1], &buf[2], &buf[3])) {
        if (buf[0] >= 0 && buf[0] <= 255 &&
            buf[1] >= 0 && buf[1] <= 255 &&
            buf[2] >= 0 && buf[2] <= 255 &&
            buf[3] >= 0 && buf[3] <= 255) {
            ucbuf[0] = buf[0] & 0xff;
            ucbuf[1] = buf[1] & 0xff;
            ucbuf[2] = buf[2] & 0xff;
            ucbuf[3] = buf[3] & 0xff;
	    }
        else {
            throw std::runtime_error(std::string("Bad address in connect_score(): ") + addr);
        }
    }
    else {
        throw std::runtime_error(std::string("Wanted x.x.x.x in connect_score(): ") + addr);
    }
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    memcpy(&sin.sin_addr, ucbuf, 4);
    sin.sin_port = htons(port);
    sock = socks->connect(sin);
    sock->send("add me please\n", 14);
    sock->step();
}