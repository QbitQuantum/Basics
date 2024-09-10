static int tcpconn_async_connect(struct socket_info* send_sock,
					union sockaddr_union* server, char *buf, unsigned len,
					struct tcp_connection** c, int *ret_fd)
{
	int fd, n;
	union sockaddr_union my_name;
	socklen_t my_name_len;
	struct tcp_connection* con;

	struct pollfd pf;

	unsigned int elapsed,to;
	int err;
	unsigned int err_len;
	int poll_err;
	char *ip;
	unsigned short port;
	struct timeval begin;

	/* create the socket */
	fd = socket(AF2PF(server->s.sa_family), SOCK_STREAM, 0);
	if (fd == -1){
		LM_ERR("socket: (%d) %s\n", errno, strerror(errno));
		return -1;
	}
	if (tcp_init_sock_opt(fd)<0){
		LM_ERR("tcp_init_sock_opt failed\n");
		goto error;
	}
	my_name_len = sockaddru_len(send_sock->su);
	memcpy( &my_name, &send_sock->su, my_name_len);
	su_setport( &my_name, 0);
	if (bind(fd, &my_name.s, my_name_len )!=0) {
		LM_ERR("bind failed (%d) %s\n", errno,strerror(errno));
		goto error;
	}

	/* attempt to do connect and see if we do block or not */
	poll_err = 0;
	elapsed = 0;
	to = hep_async_local_connect_timeout*1000;

	if (gettimeofday(&(begin), NULL)) {
		LM_ERR("Failed to get TCP connect start time\n");
		goto error;
	}

again:
	n = connect(fd, &server->s, sockaddru_len(*server));
	if (n == -1) {
		if (errno == EINTR){
			elapsed=get_time_diff(&begin);
			if (elapsed < to) goto again;
			else {
				LM_DBG("Local connect attempt failed \n");
				goto async_connect;
			}
		}
		if (errno != EINPROGRESS && errno!=EALREADY) {
			get_su_info(&server->s, ip, port);
			LM_ERR("[server=%s:%d] (%d) %s\n",ip, port, errno,strerror(errno));
			goto error;
		}
	} else goto local_connect;

	/* let's poll for a little */

	pf.fd = fd;
	pf.events = POLLOUT;

	while(1){
		elapsed = get_time_diff(&begin);
		if (elapsed < to)
			to -= elapsed;
		else {
			LM_DBG("Polling is overdue \n");
			goto async_connect;
		}

		n = poll(&pf, 1, to/1000);

		if (n < 0){
			if (errno == EINTR) continue;
			get_su_info(&server->s, ip, port);
			LM_ERR("poll/select failed:[server=%s:%d] (%d) %s\n",
				ip, port, errno, strerror(errno));
			goto error;
		} else if (n==0) /* timeout */ continue;

		if (pf.revents & (POLLERR|POLLHUP|POLLNVAL)){
			LM_ERR("poll error: flags %x\n", pf.revents);
			poll_err=1;
		}


		err_len=sizeof(err);
		getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &err_len);
		if ((err==0) && (poll_err==0)) goto local_connect;
		if (err!=EINPROGRESS && err!=EALREADY){
			get_su_info(&server->s, ip, port);
			LM_ERR("failed to retrieve SO_ERROR [server=%s:%d] (%d) %s\n",
				ip, port, err, strerror(err));
			goto error;
		}
	}

async_connect:
	LM_DBG("Create connection for async connect\n");
	/* create a new dummy connection */
	con = tcp_conn_create(fd, server, send_sock, S_CONN_CONNECTING);
	if (con==NULL) {
		LM_ERR("tcp_conn_create failed\n");
		goto error;
	}

	/* attach the write buffer to it */
	lock_get(&con->write_lock);

	if (add_write_chunk(con,buf,len,0) < 0) {
		LM_ERR("Failed to add the initial write chunk\n");
		/* FIXME - seems no more SHM now ...
		 * continue the async connect process ? */
	}

	lock_release(&con->write_lock);
	/* report an async, in progress connect */
	*c = con;
	return 0;

local_connect:
	con = tcp_conn_create(fd, server, send_sock, S_CONN_OK);
	if (con==NULL) {
		LM_ERR("tcp_conn_create failed, closing the socket\n");
		goto error;
	}
	*c = con;
	*ret_fd = fd;
	/* report a local connect */
	return 1;

error:
	close(fd);
	*c = NULL;
	return -1;
}