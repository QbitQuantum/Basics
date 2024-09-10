int api_tcp_connect(api_tcp_t* tcp,
                    api_loop_t* loop,
                    const char* ip, int port, uint64_t tmeout)
{
    struct sockaddr_in* addr_in = 
        (struct sockaddr_in*)&tcp->address.address;
    struct sockaddr_in6* addr_in6 = 
        (struct sockaddr_in6*)&tcp->address.address;
    struct sockaddr* a = (struct sockaddr*)&tcp->address.address;
    api_timer_t timeout;
    uint64_t timeout_value = tmeout;
    HANDLE handle;
    DWORD dwSent = 0;
    DWORD sys_error = 0;
    BOOL result;
    BOOL completed = FALSE;
    int af;
    int error = API__OK;

    memset(tcp, 0, sizeof(*tcp));

    if (loop->terminated)
    {
        tcp->stream.status.terminated = 1;
        return API__TERMINATE;
    }

    tcp->stream.os_win.processor = api_tcp_connect_processor;
    tcp->stream.os_win.reserved[0] = loop->scheduler.current;

    if (strchr(ip, ':') == 0)
    {
        // ipv4
        tcp->stream.fd = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP,
                                NULL, 0, WSA_FLAG_OVERLAPPED);

        af = AF_INET;

        tcp->address.length = sizeof(struct sockaddr_in);
        addr_in->sin_family = AF_INET;
        addr_in->sin_addr.s_addr = INADDR_ANY;
        addr_in->sin_port = 0;
    }
    else
    {
        // ipv6
        tcp->stream.fd = WSASocket(AF_INET6, SOCK_STREAM, IPPROTO_TCP, 
                                NULL, 0, WSA_FLAG_OVERLAPPED);

        af = AF_INET6;

        tcp->address.length = sizeof(struct sockaddr_in6);
        addr_in6->sin6_family = AF_INET6;
        addr_in6->sin6_addr = in6addr_any;
        addr_in6->sin6_port = 0;
    }

    error = api_socket_non_block(tcp->stream.fd, 1);
    error = api_socket_recv_buffer_size(tcp->stream.fd, 0);
    error = api_socket_send_buffer_size(tcp->stream.fd, 0);
    error = api_tcp_nodelay(tcp->stream.fd, 1);

    if (0 != bind(tcp->stream.fd, a, tcp->address.length))
    {
        error = api_error_translate(WSAGetLastError());
        closesocket(tcp->stream.fd);
        return error;
    }

    handle = CreateIoCompletionPort((HANDLE)tcp->stream.fd, loop->iocp, 
        (ULONG_PTR)&tcp->stream.os_win, 0);
    if (handle == NULL)
    {
        sys_error = GetLastError();
        closesocket(tcp->stream.fd);
        return api_error_translate(sys_error);
    }

    SetFileCompletionNotificationModes((HANDLE)tcp->stream.fd,
                    FILE_SKIP_COMPLETION_PORT_ON_SUCCESS);

    if (af == AF_INET)
    {
        addr_in->sin_family = AF_INET;
        addr_in->sin_addr.s_addr = inet_addr(ip);
        addr_in->sin_port = htons(port);
    }
    else
    {
        addr_in6->sin6_family = AF_INET6;
        addr_in6->sin6_addr = in6addr_any;
        addr_in6->sin6_port = htons(port);

        inet_pton(AF_INET6, ip, (void*)&addr_in6->sin6_addr);
    }

    if (timeout_value > 0)
    {
        memset(&timeout, 0, sizeof(timeout));
        timeout.task = loop->scheduler.current;

        api_timeout_exec(&loop->timeouts, &timeout, timeout_value);
    }

    result = lpfnConnectEx(tcp->stream.fd, a, tcp->address.length,
                        NULL, 0,
                        &dwSent, (LPOVERLAPPED)&tcp->stream.os_win.read);

    if (!result)
    {
        sys_error = WSAGetLastError();
        if (sys_error == ERROR_SUCCESS)
        {
            completed = TRUE;
        }
        else
        if (sys_error != WSA_IO_PENDING)
        {
            completed = TRUE;
            error = api_error_translate(sys_error);
            tcp->stream.status.error = error;
        }
    }
    else
    {
        completed = TRUE;
    }

    if (!completed)
        api_task_sleep(loop->scheduler.current);

    if (timeout_value > 0)
        api_timeout_exec(&loop->timeouts, &timeout, 0);

    if (timeout_value > 0 && timeout.elapsed)
    {
        tcp->stream.status.read_timeout = 1;

        if (API__OK != error)
            error = api_error_translate(ERROR_TIMEOUT);
    }

    if (API__OK == error)
    {
        api_stream_init(&tcp->stream, STREAM_Tcp, tcp->stream.fd);
        tcp->stream.loop = loop;
        
        api_loop_ref(loop);
        return API__OK;
    }
    else
    {
        closesocket(tcp->stream.fd);
    }

    return error;
}