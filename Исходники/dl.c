void nv_get(const char *vid) {
	WS2I
	const char * const us = getSession();
	char * const buf = malloc(1024 * 1024);//1MB cache
	char *ptr, *host, *url;
	int sock = create_socket("www.nicovideo.jp", "http", 0), len;
	send(sock, "HEAD /watch/", 12, 0);
	send(sock, vid, strlen(vid), 0);
	send(sock, " HTTP/1.0\r\nHost: www.nicovideo.jp\r\nCookie: user_session=", 56, 0);
	send(sock, us, strlen(us), 0);
	send(sock, "\r\n\r\n", 4, 0);
	buf[recv(sock, buf, 1024 * 1024, MSG_WAITALL)] = 0;
	CLOSESOCKET(sock);
	ptr = strstr(buf, "nicohistory=") + 12; *strchr(ptr, ';') = 0;
	strcpy(buf + 1024 * 1023, ptr);
	// ---------------------------------------------------------------------------------
	sock = create_socket("flapi.nicovideo.jp", "http", 0);
	send(sock, "GET /api/getflv?v=", 18, 0);
	send(sock, vid, strlen(vid), 0);
	send(sock, " HTTP/1.0\r\nHost: flapi.nicovideo.jp\r\nCookie: user_session=", 58, 0);
	send(sock, us, strlen(us), 0);
	send(sock, "\r\n\r\n", 4, 0);
	buf[recv(sock, buf, 1024 * 1023, MSG_WAITALL)] = 0;
	CLOSESOCKET(sock);
	ptr = strstr(buf, "url=") + 4; *strchr(ptr, '&') = 0;
	sep_dec_url(ptr, &host, &url);
	// ---------------------------------------------------------------------------------
	sock = create_socket(host, ptr, 0);
	send(sock, "GET ", 4, 0);
	send(sock, url, strlen(url), 0);
	send(sock, " HTTP/1.0\r\nHost: ", 17, 0);
	send(sock, host, strlen(host), 0);
	send(sock, "\r\nCookie: nicohistory=", 22, 0);
	send(sock, buf + 1024 * 1023, strlen(buf + 1024 * 1023), 0);
	send(sock, "; user_session=", 15, 0);
	send(sock, us, strlen(us), 0);
	send(sock, "\r\n\r\n", 4, 0);
	memcpy(buf, CACHE_DIR, 6);
	strcpy(buf + 6, vid);
	FILE *f = fopen(buf, "wb");
	int http = 0;
	while ((len = recv(sock, buf, 1024 * 1024, MSG_WAITALL))) {
		ptr = buf; url = ptr + len;
		if (http >= 2) goto L2;
L1:		if (*ptr == '\n') { if (++http >= 2) { ptr++; goto L2; }
		} else if (*ptr != '\r') http = 0;
		if (++ptr < url) goto L1;
		continue;
L2:		fwrite(ptr, 1, url - ptr, f);
	}
	CLOSESOCKET(sock);
	fclose(f);
	WS2U
}