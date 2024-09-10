int worker_process(epdata_t *epd, int thread_at)
{
    //printf("worker_process\n");
    working_at_fd = epd->fd;
    //network_send_error(epd, 503, "Lua Error: main function not found !!!");return 0;
    //network_send(epd, "aaa", 3);network_be_end(epd);return 0;

    if(epd->ssl && !epd->ssl_verify) {
        network_send_error(epd, 400, "No required SSL certificate was send");
        return 0;
    }

    lua_State *L = epd->L;

    if(!L) {
        epd->L = new_lua_thread(_L);

        if(!epd->L) {
            network_send_error(epd, 503, "Lua Error: Thread pool full !!!");
            return 0;
        }

        lua_pushlightuserdata(epd->L, epd);
        lua_setglobal(epd->L, "__epd__");

        L = epd->L;
    }

    lua_getglobal(L, "process");

    update_timeout(epd->timeout_ptr, STEP_PROCESS_TIMEOUT + 100);

    int init_tables = 0;
    char *pt1 = NULL, *pt2 = NULL, *t1 = NULL, *t2 = NULL, *t3 = NULL;

    int is_form_post = 0;
    char *cookies = NULL;
    pt1 = epd->headers;
    int i = 0;

    epd->uri = NULL;
    epd->host = NULL;
    epd->query = NULL;
    epd->http_ver = NULL;
    epd->referer = NULL;
    epd->user_agent = NULL;
    epd->if_modified_since = NULL;

    //epd->start_time = longtime();

    while(t1 = strtok_r(pt1, "\n", &pt1)) {
        if(++i == 1) { /// first line
            t2 = strtok_r(t1, " ", &t1);
            t3 = strtok_r(t1, " ", &t1);
            epd->http_ver = strtok_r(t1, " ", &t1);

            if(!epd->http_ver) {
                return 1;

            } else {
                if(init_tables == 0) {
                    lua_newtable(L); //headers
                }
            }

            int len = strlen(epd->http_ver);

            if(epd->http_ver[len - 1] == 13) { // CR == 13
                epd->http_ver[len - 1] = '\0';
            }

            if(t2 && t3) {
                for(t1 = t2 ; *t1 ; *t1 = toupper(*t1), t1++);

                epd->method = t2;
                lua_pushstring(L, t2);
                lua_setfield(L, -2, "method");
                t1 = strtok_r(t3, "?", &t3);
                t2 = strtok_r(t3, "?", &t3);
                epd->uri = t1;
                lua_pushstring(L, t1);
                lua_setfield(L, -2, "uri");

                if(t2) {
                    epd->query = (t2 - 1);
                    epd->query[0] = '?';
                    lua_pushstring(L, epd->query);
                    lua_setfield(L, -2, "query");
                }
            }

            continue;
        }

        t2 = strtok_r(t1, ":", &t1);

        if(t2) {
            if(t2[0] == '\r') {
                break;
            }

            for(t3 = t2; *t3; ++t3) {
                *t3 = *t3 >= 'A' && *t3 <= 'Z' ? *t3 | 0x60 : *t3;
            }

            t3 = t2 + strlen(t2) + 1; //strtok_r ( t1, ":", &t1 )

            if(t3) {
                int len = strlen(t3);

                if(t3[len - 1] == 13) { /// 13 == CR
                    t3[len - 1] = '\0';
                    len -= 1;
                }

                if(len < 1) {
                    break;
                }

                lua_pushstring(L, t3 + (t3[0] == ' ' ? 1 : 0));
                lua_setfield(L, -2, t2);

                /// check content-type
                if(t2[0] == 'h' && epd->host == NULL && strcmp(t2, "host") == 0) {
                    char *_t = strstr(t3, ":");

                    if(_t) {
                        _t[0] = '\0';
                    }

                    epd->host = t3 + (t3[0] == ' ' ? 1 : 0);

                } else if(t2[1] == 'o' && strcmp(t2, "content-type") == 0) {
                    if(stristr(t3, "x-www-form-urlencoded", len)) {
                        is_form_post = 1;

                    } else if(stristr(t3, "multipart/form-data", len)) {
                        epd->boundary = (char *)stristr(t3, "boundary=", len - 2);

                        if(epd->boundary) {
                            epd->boundary += 9;
                        }
                    }

                } else if(!cookies && t2[1] == 'o' && strcmp(t2, "cookie") == 0) {
                    cookies = t3 + (t3[0] == ' ' ? 1 : 0);

                } else if(!epd->user_agent && t2[1] == 's' && strcmp(t2, "user-agent") == 0) {
                    epd->user_agent = t3 + (t3[0] == ' ' ? 1 : 0);

                } else if(!epd->referer && t2[1] == 'e' && strcmp(t2, "referer") == 0) {
                    epd->referer = t3 + (t3[0] == ' ' ? 1 : 0);

                } else if(!epd->if_modified_since && t2[1] == 'f' && strcmp(t2, "if-modified-since") == 0) {
                    epd->if_modified_since = t3 + (t3[0] == ' ' ? 1 : 0);
                }
            }
        }
    }

    char *client_ip = inet_ntoa(epd->client_addr);
    lua_pushstring(L, client_ip);
    lua_setfield(L, -2, "remote-addr");
    int l = sizeof(struct sockaddr);
    struct sockaddr_in addr;
    getsockname(epd->fd, (struct sockaddr *) &addr, &l);
    lua_pushstring(L, inet_ntoa(addr.sin_addr));
    lua_setfield(L, -2, "server-addr");

    lua_setglobal(L, "headers");

    lua_newtable(L); /// _GET

    if(epd->query) { /// parse query string /?a=1&b=2
        char *last = NULL;
        int plen = 0;
        int qlen = strlen(epd->query) - 1;

        t1 = (char *)strsplit(epd->query + 1, qlen, "&", &last, &plen);
        char kk[256] = {0};

        while(t1) {
            char *last2 = NULL;
            int plen2 = 0;
            int plen3 = 0;

            t2 = (char *)strsplit(t1, plen, "=", &last2, &plen2);
            t3 = (char *)strsplit(t1, plen, "=", &last2, &plen3);

            if(t2 && plen2 > 0 && plen3 > 0 && plen2 <= 4096 && plen3 <= 4096) {
                size_t dlen;
                u_char *p;
                u_char *src, *dst;

                p = (u_char *)&buf_4096;
                p[0] = '\0';
                dst = p;
                dlen = urldecode(&p, (u_char **)&t3, plen3, RAW_UNESCAPE_URL);
                lua_pushlstring(L, (char *) p, dlen);

                p[0] = '\0';
                dst = p;

                dlen = urldecode(&dst, (u_char **)&t2, plen2, RAW_UNESCAPE_URL);
                p[dlen] = '\0';
                lua_setfield(L, -2, p);
            }

            t1 = (char *)strsplit(epd->query + 1, qlen, "&", &last, &plen);
        }
    }

    lua_setglobal(L, "_GET");

    lua_newtable(L); /// _COOKIE

    if(cookies) {
        while(t1 = strtok_r(cookies, ";", &cookies)) {
            t2 = strtok_r(t1, "=", &t1);
            t3 = strtok_r(t1, "=", &t1);

            if(t2 && t3 && strlen(t2) > 0 && strlen(t3) > 0) {
                size_t len, dlen;
                u_char *p;
                u_char *src, *dst;
                len = strlen(t3);
                p = malloc(len);
                p[0] = '\0';
                dst = p;
                dlen = urldecode(&dst, (u_char **)&t3, len, RAW_UNESCAPE_URL);
                lua_pushlstring(L, (char *) p, dlen);

                len = strlen(t2);

                if(len > 4096) {
                    free(p);
                    p = malloc(len);
                }

                p[0] = '\0';
                dst = p;

                dlen = urldecode(&dst, (u_char **)&t2, len, RAW_UNESCAPE_URL);
                p[dlen] = '\0';
                lua_setfield(L, -2, p + (p[0] == ' ' ? 1 : 0));
                free(p);
            }
        }
    }

    lua_setglobal(L, "_COOKIE");

    lua_pushnil(L);
    lua_setglobal(L, "__body_buf");

    epd->vhost_root = get_vhost_root(epd->host, &epd->vhost_root_len);

    memcpy(buf_4096, epd->vhost_root, epd->vhost_root_len + 1);
    sprintf(buf_4096 + epd->vhost_root_len + 1, "?.lua;%s/lua-libs/?.lua;", process_chdir);

    lua_pushstring(L, buf_4096);
    lua_getglobal(L, "package");
    lua_insert(L, -2); //-1 bufres -2 package
    lua_setfield(L, -2, "path"); //-1: path -2: package
    lua_pop(L, 1); //void

    lua_pushlstring(L, epd->vhost_root, epd->vhost_root_len); /// host root

    lua_setglobal(L, "__root");

    lua_pushstring(L, epd->vhost_root + epd->vhost_root_len); /// index-route.lua file

    epd->iov[0].iov_base = NULL;
    epd->iov[0].iov_len = 0;
    epd->iov[1].iov_base = NULL;
    epd->iov[1].iov_len = 0;

    lua_routed = 0;

    if(lua_resume(L, 1) == LUA_ERRRUN && lua_isstring(L, -1)) {
        LOGF(ERR, "Lua:error %s", lua_tostring(L, -1));
        network_send_error(epd, 503, lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    return 0;
}