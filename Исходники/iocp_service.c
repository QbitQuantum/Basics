int
post_listen(struct net_service* service, struct net_session* session, struct accept_session* asession)
{
    NET_SOCKET accept_socket;
    int err;

    accept_socket = create_socket();
    if(NET_INVALID_SOCKET == accept_socket)
    {
        return -1;
    }

    CreateIoCompletionPort((HANDLE)accept_socket, service->net_service_fd, (ULONG_PTR)accept_socket, sizeof(NET_SOCKET));
    memset(asession, 0, sizeof(struct accept_session));
    asession->id = session->id;
    asession->accept_socket = accept_socket;
    asession->op = OP_NET_ACCEPT;

    if(!AcceptEx(
                session->fd,
                accept_socket,
                asession->data_buf,
                0,
                sizeof(struct sockaddr_in) + 32,
                sizeof(struct sockaddr_in) + 32,
                &asession->recv_bytes,
                &asession->overlapped
            ))
    {
        err = net_get_error();
        if(ERROR_IO_PENDING != err)
        {
            net_close_fd(accept_socket);
            return err;
        }
    }
    return NO_ERROR;
}