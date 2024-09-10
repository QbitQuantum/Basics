struct libwebsocket *libwebsocket_client_connect_2(
	struct libwebsocket_context *context,
	struct libwebsocket *wsi
) {
	struct libwebsocket_pollfd pfd;
#ifdef LWS_USE_IPV6
	struct sockaddr_in6 server_addr6;
	struct sockaddr_in6 client_addr6;
	struct addrinfo hints, *result;
#endif
	struct sockaddr_in server_addr4;
	struct sockaddr_in client_addr4;
	struct hostent *server_hostent;

	struct sockaddr *v;
	int n;
	int plen = 0;
	const char *ads;

       lwsl_client("libwebsocket_client_connect_2\n");

	/*
	 * proxy?
	 */

	if (context->http_proxy_port) {
		plen = sprintf((char *)context->service_buffer,
			"CONNECT %s:%u HTTP/1.0\x0d\x0a"
			"User-agent: libwebsockets\x0d\x0a"
/*Proxy-authorization: basic aGVsbG86d29ybGQ= */
			"\x0d\x0a",
			lws_hdr_simple_ptr(wsi, _WSI_TOKEN_CLIENT_PEER_ADDRESS),
			wsi->u.hdr.ah->c_port);
		ads = context->http_proxy_address;

#ifdef LWS_USE_IPV6
		if (LWS_IPV6_ENABLED(context))
			server_addr6.sin6_port = htons(context->http_proxy_port);
		else
#endif
			server_addr4.sin_port = htons(context->http_proxy_port);

	} else {
		ads = lws_hdr_simple_ptr(wsi, _WSI_TOKEN_CLIENT_PEER_ADDRESS);
#ifdef LWS_USE_IPV6
		if (LWS_IPV6_ENABLED(context))
			server_addr6.sin6_port = htons(wsi->u.hdr.ah->c_port);
		else
#endif
			server_addr4.sin_port = htons(wsi->u.hdr.ah->c_port);
	}

	/*
	 * prepare the actual connection (to the proxy, if any)
	 */
       lwsl_client("libwebsocket_client_connect_2: address %s\n", ads);

#ifdef LWS_USE_IPV6
	if (LWS_IPV6_ENABLED(context)) {
		memset(&hints, 0, sizeof(struct addrinfo));
		n = getaddrinfo(ads, NULL, &hints, &result);
		if (n) {
#ifdef _WIN32
			lwsl_err("getaddrinfo: %ls\n", gai_strerrorW(n));
#else
			lwsl_err("getaddrinfo: %s\n", gai_strerror(n));
#endif
			goto oom4;
		}

		server_addr6.sin6_family = AF_INET6;
		switch (result->ai_family) {
		case AF_INET:
			/* map IPv4 to IPv6 */
			bzero((char *)&server_addr6.sin6_addr,
						sizeof(struct in6_addr));
			server_addr6.sin6_addr.s6_addr[10] = 0xff;
			server_addr6.sin6_addr.s6_addr[11] = 0xff;
			memcpy(&server_addr6.sin6_addr.s6_addr[12],
				&((struct sockaddr_in *)result->ai_addr)->sin_addr,
							sizeof(struct in_addr));
			break;
		case AF_INET6:
			memcpy(&server_addr6.sin6_addr,
			  &((struct sockaddr_in6 *)result->ai_addr)->sin6_addr,
						sizeof(struct in6_addr));
			break;
		default:
			lwsl_err("Unknown address family\n");
			freeaddrinfo(result);
			goto oom4;
		}

		freeaddrinfo(result);
	} else
#endif
	{
		server_hostent = gethostbyname(ads);
		if (!server_hostent) {
			lwsl_err("Unable to get host name from %s\n", ads);
			goto oom4;
		}

		server_addr4.sin_family = AF_INET;
		server_addr4.sin_addr =
				*((struct in_addr *)server_hostent->h_addr);
		bzero(&server_addr4.sin_zero, 8);
	}

	if (wsi->sock < 0) {

#ifdef LWS_USE_IPV6
		if (LWS_IPV6_ENABLED(context))
			wsi->sock = socket(AF_INET6, SOCK_STREAM, 0);
		else
#endif
			wsi->sock = socket(AF_INET, SOCK_STREAM, 0);

		if (wsi->sock < 0) {
			lwsl_warn("Unable to open socket\n");
			goto oom4;
		}

		if (lws_plat_set_socket_options(context, wsi->sock)) {
			lwsl_err("Failed to set wsi socket options\n");
			compatible_close(wsi->sock);
			goto oom4;
		}

		wsi->mode = LWS_CONNMODE_WS_CLIENT_WAITING_CONNECT;

		insert_wsi_socket_into_fds(context, wsi);

		libwebsocket_set_timeout(wsi,
			PENDING_TIMEOUT_AWAITING_CONNECT_RESPONSE,
							      AWAITING_TIMEOUT);
#ifdef LWS_USE_IPV6
		if (LWS_IPV6_ENABLED(context)) {
			v = (struct sockaddr *)&client_addr6;
			n = sizeof(client_addr6);
			bzero((char *)v, n);
			client_addr6.sin6_family = AF_INET6;
		} else
#endif
		{
			v = (struct sockaddr *)&client_addr4;
			n = sizeof(client_addr4);
			bzero((char *)v, n);
			client_addr4.sin_family = AF_INET;
		}

		if (context->iface) {
			if (interface_to_sa(context, context->iface,
					(struct sockaddr_in *)v, n) < 0) {
				lwsl_err("Unable to find interface %s\n",
								context->iface);
				compatible_close(wsi->sock);
				goto failed;
			}

			if (bind(wsi->sock, v, n) < 0) {
				lwsl_err("Error binding to interface %s",
								context->iface);
				compatible_close(wsi->sock);
				goto failed;
			}
		}
	}

#ifdef LWS_USE_IPV6
	if (LWS_IPV6_ENABLED(context)) {
		v = (struct sockaddr *)&server_addr6;
		n = sizeof(struct sockaddr_in6);
	} else
#endif
	{
		v = (struct sockaddr *)&server_addr4;
		n = sizeof(struct sockaddr);
	}

	if (connect(wsi->sock, v, n) == -1 || LWS_ERRNO == LWS_EISCONN) {

		if (LWS_ERRNO == LWS_EALREADY || LWS_ERRNO == LWS_EINPROGRESS
		                              || LWS_ERRNO == LWS_EWOULDBLOCK) {
			lwsl_client("nonblocking connect retry\n");

			/*
			 * must do specifically a POLLOUT poll to hear
			 * about the connect completion
			 */
			if (lws_change_pollfd(wsi, 0, LWS_POLLOUT))
				goto oom4;

			return wsi;
		}

		if (LWS_ERRNO != LWS_EISCONN) {
			lwsl_debug("Connect failed errno=%d\n", LWS_ERRNO);
			goto failed;
		}
	}

	lwsl_client("connected\n");

	/* we are connected to server, or proxy */

	if (context->http_proxy_port) {

		/* OK from now on we talk via the proxy, so connect to that */

		/*
		 * (will overwrite existing pointer,
		 * leaving old string/frag there but unreferenced)
		 */
		if (lws_hdr_simple_create(wsi, _WSI_TOKEN_CLIENT_PEER_ADDRESS,
						   context->http_proxy_address))
			goto failed;
		wsi->u.hdr.ah->c_port = context->http_proxy_port;

		n = send(wsi->sock, context->service_buffer, plen, MSG_NOSIGNAL);
		if (n < 0) {
			lwsl_debug("ERROR writing to proxy socket\n");
			goto failed;
		}

		libwebsocket_set_timeout(wsi,
			PENDING_TIMEOUT_AWAITING_PROXY_RESPONSE,
							      AWAITING_TIMEOUT);

		wsi->mode = LWS_CONNMODE_WS_CLIENT_WAITING_PROXY_REPLY;

		return wsi;
	}

	/*
	 * provoke service to issue the handshake directly
	 * we need to do it this way because in the proxy case, this is the
	 * next state and executed only if and when we get a good proxy
	 * response inside the state machine... but notice in SSL case this
	 * may not have sent anything yet with 0 return, and won't until some
	 * many retries from main loop.  To stop that becoming endless,
	 * cover with a timeout.
	 */

	libwebsocket_set_timeout(wsi,
		PENDING_TIMEOUT_SENT_CLIENT_HANDSHAKE, AWAITING_TIMEOUT);

	wsi->mode = LWS_CONNMODE_WS_CLIENT_ISSUE_HANDSHAKE;
	pfd.fd = wsi->sock;
	pfd.revents = LWS_POLLIN;

	n = libwebsocket_service_fd(context, &pfd);

	if (n < 0)
		goto failed;

	if (n) /* returns 1 on failure after closing wsi */
		return NULL;

	return wsi;

oom4:
	free(wsi->u.hdr.ah);
	free(wsi);
	return NULL;

failed:
	libwebsocket_close_and_free_session(context, wsi,
						     LWS_CLOSE_STATUS_NOSTATUS);
	return NULL;
}