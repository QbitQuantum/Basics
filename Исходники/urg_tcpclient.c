int tcpclient_open(urg_tcpclient_t* cli, const char* ip_str, int port_num)
{
    enum { Connect_timeout_second = 2 };
    fd_set rmask, wmask;
    struct timeval tv = { Connect_timeout_second, 0 };
#if defined(URG_WINDOWS_OS)
    u_long flag;
#else
    int flag;
    int sock_optval = -1;
    int sock_optval_size = sizeof(sock_optval);
#endif
    int ret;

    cli->sock_desc = Invalid_desc;
    cli->pushed_back = -1; // no pushed back char.

#if defined(URG_WINDOWS_OS)
    {
        static int is_initialized = 0;
        WORD wVersionRequested = 0x0202;
        WSADATA WSAData;
        int err;
        if (!is_initialized) {
            err = WSAStartup(wVersionRequested, &WSAData);
            if (err != 0) {
                return -1;
            }
            is_initialized = 1;
        }
    }
#endif

    tcpclient_buffer_init(cli);

    cli->sock_addr_size = sizeof (struct sockaddr_in);
    if ((cli->sock_desc = (int)socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }

    memset((char*)&(cli->server_addr), 0, sizeof(cli->sock_addr_size));
    cli->server_addr.sin_family = AF_INET;
    cli->server_addr.sin_port = htons(port_num);

    if (!strcmp(ip_str, "localhost")) {
        ip_str = "127.0.0.1";
    }

    /* bind is not required, and port number is dynamic */
    if ((cli->server_addr.sin_addr.s_addr = inet_addr(ip_str)) == INADDR_NONE) {
        return -1;
    }

#if defined(URG_WINDOWS_OS)
    //ノンブロックに変更
    flag = 1;
    ioctlsocket(cli->sock_desc, FIONBIO, &flag);

    if (connect(cli->sock_desc, (const struct sockaddr *)&(cli->server_addr),
                cli->sock_addr_size) == SOCKET_ERROR) {
        int error_number = WSAGetLastError();
        if (error_number != WSAEWOULDBLOCK) {
            tcpclient_close(cli);
            return -1;
        }

        FD_ZERO(&rmask);
        FD_SET((SOCKET)cli->sock_desc, &rmask);
        wmask = rmask;

        ret = select((int)cli->sock_desc + 1, &rmask, &wmask, NULL, &tv);
        if (ret == 0) {
            // タイムアウト
            tcpclient_close(cli);
            return -2;
        }
    }
    //ブロックモードにする
    set_block_mode(cli);

#else
    //ノンブロックに変更
    flag = fcntl(cli->sock_desc, F_GETFL, 0);
    fcntl(cli->sock_desc, F_SETFL, flag | O_NONBLOCK);

    if (connect(cli->sock_desc, (const struct sockaddr *)&(cli->server_addr),
                cli->sock_addr_size) < 0) {
        if (errno != EINPROGRESS) {
            tcpclient_close(cli);
            return -1;
        }

        // EINPROGRESS:コネクション要求は始まったが、まだ完了していない
        FD_ZERO(&rmask);
        FD_SET(cli->sock_desc, &rmask);
        wmask = rmask;

        ret = select(cli->sock_desc + 1, &rmask, &wmask, NULL, &tv);
        if (ret <= 0) {
            // タイムアウト処理
            tcpclient_close(cli);
            return -2;
        }

        if (getsockopt(cli->sock_desc, SOL_SOCKET, SO_ERROR, (int*)&sock_optval,
                       (socklen_t*)&sock_optval_size) != 0) {
            // 接続に失敗
            tcpclient_close(cli);
            return -3;
        }

        if (sock_optval != 0) {
            // 接続に失敗
            tcpclient_close(cli);
            return -4;
        }

        set_block_mode(cli);
    }
#endif

    return 0;
}