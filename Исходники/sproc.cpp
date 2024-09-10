void RemoteSlaveProcess::Open(const char *host, int port, const char *cmdline, const char *envptr, int to)
{
    SVRLOG("RemoteSlaveProcess(" << host << ":" << port << ")=" << cmdline);
    Kill();

    timeout = to;
    Socket::Init();
    String localhost;
    if(host == 0 || *host == 0)
    {
        localhost = Socket::GetHostName();
        host = localhost;
    }
    if(port == 0)
        port = DEFAULT_PORT;
    terminated = false;
    current_part = 0;
    output[0] = output[1] = output[2] = Null;
    if(!ClientSocket(socket, host, port, true, NULL, REQUEST_TIMEOUT))
        throw Exc(NFormat(t_("Opening host '%s' / port %d failed, error = %s"), host, port, Socket::GetErrorText()));
    int len = (int)strlen(cmdline);
    if(envptr && *envptr) {
        const char *e = envptr;
        while(*e)
            e = e + strlen(e) + 1;
        socket.Write(":");
        socket.Write(ASCII85Encode(String(envptr, e + 1)));
        socket.Write("\n");
    }
    socket.Write("=");
    socket.Write(cmdline, len + 1); // send terminating 0 as well
    Recv(0, timeout);
    if(output[0][0] == '-')
        throw Exc(NFormat(t_("Error running process: %s\nCommand: %s"), output[0].Begin() + 1, cmdline));

    if(output[0] != "+")
        throw Exc(NFormat(t_("Communication error; process = %s"), cmdline));
}