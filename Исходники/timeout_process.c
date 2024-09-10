void timeout_listener_process(int rank)
{
	struct sockaddr_un saddr_un;
	struct sockaddr_un *s_un;
	struct sockaddr_in saddr_in;
	struct sockaddr_in *s_in;
	struct sockaddr_in6 *s_in6;
	int connect_fd;
	char buffer[BUF_LEN];
	char *p, *sp, *end, *start;
	unsigned int h_entry, h_id;
	str id;
	unsigned short port;
	struct sockaddr* saddr;
	int len, i,n, left;
	int optval = 1;
	struct sockaddr rtpp_info;
	struct rtpp_notify_node *rtpp_lst;
	str terminate_reason = str_init("RTPProxy Timeout");
	int offset = 0;

	if (init_child(PROC_MODULE) != 0) {
		LM_ERR("cannot init child process");
		return;
	}

	if (!rtpp_notify_socket_un) {
		p = strrchr(rtpp_notify_socket.s, ':');
		if (!p) {
			LM_ERR("invalid udp address <%.*s>\n", rtpp_notify_socket.len, rtpp_notify_socket.s);
			return;
		}
		n = p- rtpp_notify_socket.s;
		rtpp_notify_socket.s[n] = 0;

		id.s = p+1;
		id.len = rtpp_notify_socket.len - n -1;
		port= str2s(id.s, id.len, &n);
		if(n) {
			LM_ERR("Bad format for socket name. Expected ip:port\n");
			return;
		}
		memset(&saddr_in, 0, sizeof(saddr_in));
		saddr_in.sin_addr.s_addr = inet_addr(rtpp_notify_socket.s);
		saddr_in.sin_family = AF_INET;
		saddr_in.sin_port = htons(port);

		socket_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (socket_fd == -1) {
			LM_ERR("can't create timeout socket\n");
			return;
		}
		saddr = (struct sockaddr*)&saddr_in;
		len = sizeof(saddr_in);
		LM_DBG("binding socket %d to %s:%d\n", socket_fd, rtpp_notify_socket.s, port);
	} else {
		/* create socket */
		socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
		if (socket_fd == -1) {
			LM_ERR("Failed to create unix socket\n");
			return;
		}

		memset(&saddr_un, 0, sizeof(struct sockaddr_un));
		saddr_un.sun_family = AF_LOCAL;
		strncpy(saddr_un.sun_path, rtpp_notify_socket.s,
				sizeof(saddr_un.sun_path) - 1);
		saddr = (struct sockaddr*)&saddr_un;
		len = sizeof(saddr_un);
		LM_DBG("binding unix socket %s\n", rtpp_notify_socket.s);
	}

	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (void*)&optval,
				sizeof(optval)) == -1) {
		LM_ERR("setsockopt failed %s\n", strerror(errno));
		return;
	}

	if (bind(socket_fd, saddr, len) == -1) {
		LM_ERR("failed to bind to socket: %s\n", strerror(errno));
		return;
	}

	/* open socket for listening */
	if(listen(socket_fd, 10) == -1) {
		LM_ERR("socket listen failed: %s(%d)\n", strerror(errno), errno);
		close(socket_fd);
		return;
	}

	pfds = (struct pollfd *)pkg_malloc(pfds_size*sizeof(struct pollfd));
	if (!pfds) {
		LM_ERR("no more pkg memory\n");
		return;
	}
	pfds[0].fd = socket_fd;
	pfds[nfds++].events = POLLIN;

	for(;;) {
		nr_events = poll(pfds, nfds, -1);
		if (nr_events < 0)
			continue;

		/* check if the rtpproxy list needs updates */
		lock_get(rtpp_notify_h->lock);
		if (rtpp_notify_h->changed) {
			/* update list */
			update_rtpproxy_list();
			rtpp_notify_h->changed = 0;
		}
		lock_release(rtpp_notify_h->lock);

		rtpp_lst = NULL;
		/* there is a new connection */
		if (pfds[0].revents & POLLIN) {
			i = sizeof(rtpp_info);
			memset(&rtpp_info, 0, i);
			connect_fd = accept(socket_fd, &rtpp_info, (socklen_t *)&i);
			if(connect_fd < 0) {
				LM_ERR("socket accept failed: %s(%d)\n", strerror(errno), errno);
				continue;
			}

			/* if it is a unix socket, try to authenticate it */
			if (rtpp_info.sa_family == AF_UNIX) {
				s_un = (struct sockaddr_un*)&rtpp_info;
				/* check if the socket is already opened */
				lock_get(rtpp_notify_h->lock);
				for (rtpp_lst = rtpp_notify_h->rtpp_list; rtpp_lst; rtpp_lst = rtpp_lst->next)
					if ( rtpp_lst->mode == 0 && !strcmp(rtpp_lst->addr, s_un->sun_path))
						break;

				/* if not found add a new one */
				if (!rtpp_lst) {
					/* leave the lock for a moment */
					lock_release(rtpp_notify_h->lock);
					rtpp_lst = (struct rtpp_notify_node*)
						shm_malloc(sizeof(struct rtpp_notify_node));
					if (!rtpp_lst) {
						LM_ERR("no shm more memory\n");
						return;
					}
					rtpp_lst->index = 0;
					rtpp_lst->mode = 0;
					rtpp_lst->addr = 0;

					/* copy the socket name */
					len = strlen(s_un->sun_path);
					rtpp_lst->addr = (char *)shm_malloc(len + 1);
					if (!rtpp_lst->addr) {
						LM_ERR("no more shm memory\n");
						return;
					}
					memcpy(rtpp_lst->addr, s_un->sun_path, len + 1);

					lock_get(rtpp_notify_h->lock);
					rtpp_lst->next = rtpp_notify_h->rtpp_list;
					rtpp_notify_h->rtpp_list = rtpp_lst;
				}
			} else {
				/* search if I can find this connection */
				if (rtpp_info.sa_family == AF_INET) {
					s_in = (struct sockaddr_in*)&rtpp_info;
					lock_get(rtpp_notify_h->lock);
					for (rtpp_lst = rtpp_notify_h->rtpp_list; rtpp_lst; rtpp_lst = rtpp_lst->next)
						if (rtpp_lst->mode == 1 &&
							memcmp(rtpp_lst->addr, &s_in->sin_addr.s_addr, 4) == 0)
							break;
				} else if (rtpp_info.sa_family == AF_INET6) {
					s_in6 = (struct sockaddr_in6*)&rtpp_info;
					lock_get(rtpp_notify_h->lock);
					for (rtpp_lst = rtpp_notify_h->rtpp_list; rtpp_lst; rtpp_lst = rtpp_lst->next)
						if (rtpp_lst->mode == 6 &&
							memcmp(rtpp_lst->addr, s_in6->sin6_addr.s6_addr, 16) == 0)
							break;
				} else {
					LM_ERR("cannot accept this type of connection\n");
				}
			}

			if (!rtpp_lst) {
				lock_release(rtpp_notify_h->lock);
				LM_DBG("unknown rtpproxy -- ignoring\n");
				shutdown(connect_fd, SHUT_RDWR);
				close(connect_fd);
			} else {
				/* valid connection - checking if already connected */
				if (rtpp_lst->index) {
					LM_DBG("rtpproxy restarted - update connection status\n");
					shutdown(rtpp_lst->fd, SHUT_RDWR);
					close(rtpp_lst->fd);
				} else {
					rtpp_lst->index = nfds++;
					if (nfds > pfds_size) {
						pfds_size *= 2;
						pfds = (struct pollfd*)pkg_realloc(pfds,
								pfds_size*sizeof(struct pollfd));
					}
				}

				LM_DBG("rtpproxy accepted\n");
				pfds[rtpp_lst->index].fd = connect_fd;
				pfds[rtpp_lst->index].events = POLLIN;
				rtpp_lst->fd = connect_fd;
				lock_release(rtpp_notify_h->lock);
			}
			nr_events--;
		}

		for (i=1; (nr_events && i<nfds); i++)
		{
			if (!(pfds[i].revents & POLLIN))
				continue;
			nr_events--;

			do
				len = read(pfds[i].fd, buffer + offset, BUF_LEN - offset);
			while (len == -1 && errno == EINTR);

			if (len < 0) {
				LM_ERR("reading from socket failed: %s\n",strerror(errno));
				continue;
			}

			if (!len) {
				LM_DBG("closing rtpproxy\n");
				lock_get(rtpp_notify_h->lock);
				for (rtpp_lst=rtpp_notify_h->rtpp_list;
						rtpp_lst;rtpp_lst=rtpp_lst->next)
					if (rtpp_lst->index == i)
						break;
				if (!rtpp_lst) {
					LM_ERR("BUG - rtpproxy not found\n");
					lock_release(rtpp_notify_h->lock);
					continue;
				}
				rtpp_lst->index = 0;
				lock_release(rtpp_notify_h->lock);
				nfds--;
				shutdown(pfds[i].fd, SHUT_RDWR);
				close(pfds[i].fd);

				if (nfds == i)
					continue;

				pfds[i].fd = pfds[nfds].fd;
				lock_get(rtpp_notify_h->lock);
				for (rtpp_lst=rtpp_notify_h->rtpp_list; rtpp_lst; rtpp_lst=rtpp_lst->next)
					if (rtpp_lst->index == nfds)
						break;
				if (!rtpp_lst) {
					LM_ERR("BUG - rtpproxy index mismatch\n");
					lock_release(rtpp_notify_h->lock);
					continue;
				}
				rtpp_lst->index = i;
				lock_release(rtpp_notify_h->lock);
				continue;
			}
			LM_INFO("Timeout detected on the following calls [%.*s]\n", len, buffer);
			p = buffer;
			left = len + offset;
			offset = 0;
			end = buffer + left;

			do {
				start = p;
				/* the message is: h_entry.h_id\n */
				sp = memchr(p, '.', left);
				if (sp == NULL)
					break;

				id.s = p;
				id.len = sp - p;

				if (sp >= end)
					break;

				p = sp + 1;
				left -= id.len + 1;

				if(str2int(&id, &h_entry)< 0) {
					LM_ERR("Wrong formated message received from rtpproxy - invalid"
							" dialog entry [%.*s]\n", id.len, id.s);
					break;
				}

				sp = memchr(p, '\n', left);
				if (sp == NULL)
					break;

				id.s = p;
				id.len = sp - p;

				if (sp >= end)
					break;

				p = sp + 1;
				left -= id.len + 1;

				if(str2int(&id, &h_id)< 0) {
					LM_ERR("Wrong formated message received from rtpproxy - invalid"
							" dialog id [%.*s]\n", id.len, id.s);
					break;
				}
				LM_DBG("hentry = %u, h_id = %u\n", h_entry, h_id);

				if(dlg_api.terminate_dlg(h_entry, h_id,&terminate_reason)< 0)
					LM_ERR("Failed to terminate dialog h_entry=[%u], h_id=[%u]\n", h_entry, h_id);

				LM_DBG("Left to process: %d\n[%.*s]\n", left, left, p);

			} while (p < end);

			offset = end - start;
			memmove(buffer, start, end - start);
		}
	}
}