void zmq::udp_engine_t::in_event()
{
  struct sockaddr_in in_address;
  socklen_t in_addrlen = sizeof(sockaddr_in);
#ifdef ZMQ_HAVE_WINDOWS
    int nbytes = recvfrom(fd, (char*) in_buffer, MAX_UDP_MSG, 0, (sockaddr*) &in_address, &in_addrlen);
    const int last_error = WSAGetLastError();
    if (nbytes == SOCKET_ERROR) {
        wsa_assert(
            last_error == WSAENETDOWN ||
            last_error == WSAENETRESET ||
            last_error == WSAEWOULDBLOCK);
        return;
    }
#else
    int nbytes = recvfrom(fd, in_buffer, MAX_UDP_MSG, 0, (sockaddr*) &in_address, &in_addrlen);
    if (nbytes == -1) {
        errno_assert(errno != EBADF
            && errno != EFAULT
            && errno != ENOMEM
            && errno != ENOTSOCK);
        return;
    }
#endif
    int rc;
    int body_size;
    int body_offset;
    msg_t msg;

    if (options.raw_socket) {
        sockaddr_to_msg (&msg, &in_address);

        body_size = nbytes;
        body_offset = 0;
    }
    else {
        char* group_buffer = (char *)in_buffer + 1;
        int group_size = in_buffer[0];

        rc = msg.init_size (group_size);
        errno_assert (rc == 0);
        msg.set_flags (msg_t::more);
        memcpy (msg.data (), group_buffer, group_size);

        //  This doesn't fit, just ingore
        if (nbytes - 1 < group_size)
            return;

        body_size = nbytes - 1 - group_size;
        body_offset = 1 + group_size;
    }

    rc = session->push_msg (&msg);
    errno_assert (rc == 0 || (rc == -1 && errno == EAGAIN));

    //  Pipe is full
    if (rc != 0) {
        rc = msg.close ();
        errno_assert (rc == 0);

        reset_pollin (handle);
        return;
    }

    rc = msg.close ();
    errno_assert (rc == 0);
    rc = msg.init_size (body_size);
    errno_assert (rc == 0);
    memcpy (msg.data (), in_buffer + body_offset, body_size);
    rc = session->push_msg (&msg);
    errno_assert (rc == 0);
    rc = msg.close ();
    errno_assert (rc == 0);
    session->flush ();
}