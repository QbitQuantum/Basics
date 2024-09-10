int PROXY_INFO::parse(MIOFILE& in) {
    char buf[1024];

    memset(this, 0, sizeof(PROXY_INFO));
    while (in.fgets(buf, 256)) {
        if (match_tag(buf, "</proxy_info>")) {
            present = false;
            if (strlen(http_server_name)) present = true;
            if (strlen(socks_server_name)) present = true;
            return 0;
        }
        else if (parse_bool(buf, "use_http_proxy", use_http_proxy)) continue;
        else if (parse_bool(buf, "use_socks_proxy", use_socks_proxy)) continue;
        else if (parse_bool(buf, "use_http_auth", use_http_auth)) continue;
        else if (parse_str(buf, "<socks_server_name>", socks_server_name, sizeof(socks_server_name))) continue;
        else if (parse_int(buf, "<socks_server_port>", socks_server_port)) continue;
        else if (parse_str(buf, "<http_server_name>", http_server_name, sizeof(http_server_name))) continue;
        else if (parse_int(buf, "<http_server_port>", http_server_port)) continue;
        else if (parse_str(buf, "<socks5_user_name>", socks5_user_name,sizeof(socks5_user_name))) continue;
        else if (parse_str(buf, "<socks5_user_passwd>", socks5_user_passwd,sizeof(socks5_user_passwd))) continue;
        else if (parse_str(buf, "<http_user_name>", http_user_name,sizeof(http_user_name))) continue;
        else if (parse_str(buf, "<http_user_passwd>", http_user_passwd,sizeof(http_user_passwd))) continue;
		else if (parse_str(buf, "<no_proxy>", noproxy_hosts, sizeof(noproxy_hosts))) continue;
    }
    return ERR_XML_PARSE;
}