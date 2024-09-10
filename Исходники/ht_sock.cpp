void *recv_thread(void *arg)
{
    int ret = EXIT_SUCCESS;

    char *message;
    int length = 0;

    fd_set fd_connect_set;
    struct timeval tv_connect_timeout;

    int addr_len = sizeof(struct sockaddr_in);

    message = recv_buffer;

    log(LOG_GENERIC, "recv thread created");

    while (1)
    {
        init_socket();

        while (1)
        {
            // try to bind local port
            log(LOG_GENERIC, "bind %s:%d...", 
                inet_ntoa(local_sck_addr.sin_addr), ntohs(local_sck_addr.sin_port));

            ret = bind(sck_fd, (struct sockaddr *)&local_sck_addr, sizeof(struct sockaddr_in));
            if (ret == 0)
            {
                log(LOG_GENERIC, "bind success");
            }
            else
            {
                log(LOG_ERROR, "bind err %d", ret);
            }

            // try to connect remote:
            log(LOG_GENERIC, "trying to connect %s:%d...",
                inet_ntoa(remote_sck_addr.sin_addr), ntohs(remote_sck_addr.sin_port));

            // force socket as non-blocking
            set_socket_blocking_enabled(sck_fd, false);

            ret = connect(sck_fd, (struct sockaddr *)&remote_sck_addr, sizeof(struct sockaddr_in));
            if (ret < 0)
            {
                if (WSAGetLastError() == WSAEWOULDBLOCK)	//EINPROGRESS
                {
                    tv_connect_timeout.tv_sec = 1; 
                    tv_connect_timeout.tv_usec = 0;

                    FD_ZERO(&fd_connect_set); 
                    FD_SET(sck_fd, &fd_connect_set);

                    // wait 1 seconds:
                    ret = select(sck_fd + 1, NULL, &fd_connect_set, NULL, &tv_connect_timeout);

                    if (ret <= 0)
                    {
                        log(LOG_GENERIC, "connect too slow, reinit socket");
                        deinit_socket();
                        init_socket();
                    }
                    else
                    { // connected
                        break;
                    }
                }
                else
                {
                    log(LOG_ERROR, "connect err %d", ret);
                }
            }
            else if (ret == 0)
            {
                break;
            }

            usleep(CONNECT_RETRY_DELAY);
        }

        // force socket as blocking
        set_socket_blocking_enabled(sck_fd, true);

        log(LOG_GENERIC, "connected");
        usleep(CONNECTED_DELAY);

        send_hunter_message(HUNT_MSG_CONNECTED);

        while (1)
        {
            // blocking socket:
            ret = recv(sck_fd, recv_buffer, MAX_SOCK_BUFFER, 0);
            if (ret > 0)
            {
                length = ret;
            }
            else if (ret == 0)
            {
                // orderly shutdown
                log(LOG_ERROR, "recv shutdown");
                break;
            }
            else
            { // ret < 0, typically -1
                // an error occurred
                log(LOG_ERROR, "recv error %d", ret);
            }

#ifdef sock_DEBUG
            log(LOG_GENERIC, "Receive %d:%s", length, message);
#endif // sock_DEBUG

            // once received, we call handler:
            sock_receive(message, length);

            // check how much time is wasted on receive module
        }

        log(LOG_GENERIC, "disconnect");

        // we should gently close socket, and try to connect again
        closesocket(sck_fd);
    }

    log(LOG_GENERIC, "recv thread exit");
}