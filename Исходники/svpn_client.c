static void *svpn_handle_thread(void *pvoid) {
	struct svpn_client *psc = (struct svpn_client*)pvoid;

	struct sockaddr_in addr;
	socklen_t alen = sizeof(addr);
	unsigned char buffer[BUFFER_LEN], tmp_buffer[BUFFER_LEN];
//	struct timeval tv;
	fd_set fd_list;
	int maxfd = (psc->sock_fd > psc->tun_fd) ? psc->sock_fd : psc->tun_fd;
	int ret, len;
	++maxfd;
	int recvc = 0, sendc = 0;

//	tv.tv_sec = 0;
//	tv.tv_usec = 0;
	while(1) {
		FD_ZERO(&fd_list);
		FD_SET(psc->tun_fd, &fd_list);
		FD_SET(psc->sock_fd, &fd_list);
		ret = select(maxfd, &fd_list, NULL, NULL, NULL);
		if(ret < 0) {
			if(errno == EINTR) {
				return NULL;
			}
			continue;
		}
		if(FD_ISSET(psc->tun_fd, &fd_list)) {
			len = read(psc->tun_fd, tmp_buffer, BUFFER_LEN);

			++sendc;

			len -= 4;
			printf("send : %d total:%d\n", len, sendc);
			if(len < 0) {
			//printf("nothing in send\n");
				continue;
			}

			Encrypt(&(psc->table), tmp_buffer + 4, buffer, len);
//			printf("header?0x%08x\n", *(int*)tmp_buffer);

			len = sendto(psc->sock_fd, buffer, len, 0,
					(struct sockaddr*)&(psc->server_addr), sizeof(psc->server_addr));
	
		}
		if(FD_ISSET(psc->sock_fd, &fd_list)) {
			len = recvfrom(psc->sock_fd, tmp_buffer, BUFFER_LEN, 0,
					(struct sockaddr*)&addr, &alen);
			++recvc;
			printf("recv : %d total:%d\n", len, recvc);
			if(len < 0) {
				continue;
			}
			memset(buffer, 0, 4);
			*(int*)buffer = 0x02000000;
			Decrypt(&(psc->table), tmp_buffer, buffer + 4, len);
			len += 4;
			len = write(psc->tun_fd, buffer, len);
//			printf("write:%d\n", len);
		}

	}
	return NULL;
}