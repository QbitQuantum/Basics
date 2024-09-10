int main(int argc, char *argv[])
{
    int sockfd = -1;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        E("%s", strerror(errno));
        return -1;
    }

    int optval = 1;
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
                         &optval, sizeof(optval));
    if (ret == -1) {
        E("%s", strerror(errno));
        return -1;
    }
    //ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT,
    //&optval, sizeof(optval));

    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);

    memset(&addr, '\0', addrlen);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr = INADDR_ANY;

    ret = bind(sockfd, (struct sockaddr *)&addr, addrlen);
    if (ret == -1) {
        E("%s", strerror(errno));
        return -1;
    }

    int backlog = 20;
    ret = listen(sockfd, backlog);
    if (ret == -1) {
        E("%s", strerror(errno));
        return -1;
    }

    sqlite3 *db;
    ret = sqlite3_open("./cs_user.db", &db);
    if (ret != SQLITE_OK) {
        E("sqlite3_open() failed.");
        return -1;
    }
    int query_len_max = 512;
    char *query_line = (char *)cs_malloc(sizeof(char) * query_len_max);
    if (query_line == NULL) {
        E("cs_malloc() failed.");
        return -1;
    }

    struct sockaddr_in peer_addr;
    socklen_t peer_addrlen = sizeof(peer_addr);

    memset(&peer_addr, '\0', peer_addrlen);

    size_t buflen = 512;
    char *buf = (char *)cs_malloc(sizeof(char) * buflen);
    if (buf == NULL) {
        E("cs_malloc() failed.");
        cs_free(&query_line);
        return -1;
    }

    int peer_sockfd = -1;
    ssize_t s = 0;
    char str[INET_ADDRSTRLEN];
    while (1) {
        peer_sockfd = accept(sockfd,
                             (struct sockaddr *)&peer_addr, &peer_addrlen);
        if (peer_sockfd == -1) {
            E("%s", strerror(errno));
            break;
        }
        D("received from %s at PORT %d",
          inet_ntop(AF_INET, &peer_addr.sin_addr, str,
                    sizeof(str)),
          ntohs(peer_addr.sin_port));

        // FIXME: why server exit when client ctrl-c
        while (1) {
            memset(buf, '\0', buflen);

            s = read(peer_sockfd, buf, buflen);
            if (s == -1 || strlen(buf) == 0) {
                //E("%s", strerror(errno));
                break;
            }
            DS(buf);

            /* check username & passwd */
            cs_request_t req = cs_parse_request(buf);
            if (req.name == NULL) {
                E("cs_parse_request() failed.");
                break;
            }
            request_dump(&req);

            memset(query_line, '\0', query_len_max);
            sprintf(query_line, "select * from user where name='%s' and passwd='%s'", req.name, req.passwd);
            DS(query_line);

            int sql_select_num = 0;
            ret = sqlite3_exec(db, query_line, sql_check_identity_cb, &sql_select_num, NULL);
            if (ret == SQLITE_ABORT || sql_select_num != 1) {
                E("sqlite3_exec() failed.");
                DD(sql_select_num);
                s = write(peer_sockfd, "*", 1);
                if (s == -1) {
                    E("%s", strerror(errno));
                }
                D("send sign * to client.");
                break;
            }

            memset(buf, '\0', buflen);
            memset(query_line, '\0', query_len_max);

            /* get buddy name list */
            sprintf(query_line, "select * from %s", req.name);
            DS(query_line);

            cs_str_t buddy;
            buddy.data = buf;
            buddy.len = strlen(buf);

            ret = sqlite3_exec(db, query_line, sql_get_buddy_cb, &buddy, NULL);
            if (ret == SQLITE_ABORT) {
                E("sqlite3_exec() failed.");
                break;
            }
            DDSTR(buddy);

            request_free(&req);

            if (strlen(buf) == 0) {
                s = write(peer_sockfd, ":", 1);
                if (s == -1) {
                    E("%s", strerror(errno));
                }
                D("send sign : to client.");
                break;
            }

            s = write(peer_sockfd, buf, strlen(buf));
            if (s == -1) {
                E("%s", strerror(errno));
                break;
            }
        }
    }

    cs_free(&buf);
    cs_free(&query_line);
    sqlite3_close(db);
    ret = close(sockfd);
    if (ret == -1) {
        E("%s", strerror(errno));
        return -1;
    }

#if 0
    void FD_CLR(int fd, fd_set *set);
    int  FD_ISSET(int fd, fd_set *set);
    void FD_SET(int fd, fd_set *set);
    void FD_ZERO(fd_set *set);
    int select(int nfds, fd_set *readfds, fd_set *writefds,
               fd_set *exceptfds, struct timeval *timeout);
#endif

    return 0;
}