void
read_nginx_live_stats(struct module *mod, char *parameter)
{
    int                 addr_len, domain, m, sockfd, send, pos = 0;
    char                buf[LEN_1M], request[LEN_4096], line[LEN_4096];
    unsigned long long online = 0, online_history = 0, up_flow = 0;
    unsigned long long down_flow = 0, fmtime = 0, drop_frame = 0;
    char               *p;
    void               *addr;
    FILE               *stream = NULL;
    struct sockaddr_in  servaddr;
    struct sockaddr_un  servaddr_un;
    struct hostinfo     hinfo;
    struct stats_nginx_live  stat;

    /* get peer info */
    init_nginx_host_info(&hinfo);

    if (*hinfo.host == '/') {
        addr = &servaddr_un;
        addr_len = sizeof(servaddr_un);
        bzero(addr, addr_len);
        domain = AF_LOCAL;
        servaddr_un.sun_family = AF_LOCAL;
        strncpy(servaddr_un.sun_path, hinfo.host, sizeof(servaddr_un.sun_path) - 1);

    } else {
        addr = &servaddr;
        addr_len = sizeof(servaddr);
        bzero(addr, addr_len);
        domain = AF_INET;
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(hinfo.port);
        inet_pton(AF_INET, hinfo.host, &servaddr.sin_addr);
    }

    /* send request */
    if ((sockfd = socket(domain, SOCK_STREAM, 0)) == -1) {
        return;
    }

    sprintf(request,
            "GET %s HTTP/1.0\r\n"
            "User-Agent: taobot\r\n"
            "Host: %s\r\n"
            "Accept:*/*\r\n"
            "Connection: Close\r\n\r\n",
            hinfo.uri, hinfo.server_name);

    if ((m = connect(sockfd, (struct sockaddr *) addr, addr_len)) == -1 ) {
        close(sockfd);
        return;
    }

    if ((send = write(sockfd, request, strlen(request))) == -1) {
        close(sockfd);
        return;
    }

    /* read & parse request */
    if ((stream = fdopen(sockfd, "r")) == NULL) {
        close(sockfd);
        return;
    }

    memset(&stat, 0, sizeof(struct stats_nginx_live));
    while (fgets(line, LEN_4096, stream) != NULL) {
        if ((p = strstr(line, "fm_time")) == NULL) {
            continue;
        }

        if (sscanf(p, "fm_time:%llu drop_frame:%llu online:%llu online_history:%llu down_flow:%llu up_flow:%llu",
                   &fmtime, &drop_frame, &online, &online_history, &down_flow, &up_flow) != 6) {
            continue;
        }
        stat.online += online;
        stat.fmdata += fmtime;
        stat.dropfr += drop_frame;
        stat.olhstr += online_history;
        stat.downfl += down_flow;
        stat.upflow += up_flow;
    }
    pos += snprintf(buf + pos, LEN_1M - pos, "%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld", stat.online, stat.olhstr, stat.olvary, stat.upflow, stat.uspeed, stat.downfl, stat.dspeed, stat.fmtime, stat.fmdata, stat.dropfr);
    if (strlen(buf) >= LEN_1M - 1) {
        fclose(stream);
        close(sockfd);
        return;
    }

    set_mod_record(mod, buf);
    fclose(stream);
    close(sockfd);
}