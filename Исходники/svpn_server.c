int svpn_server_handle_thread(struct svpn_server* pvoid)
{
	struct svpn_server *psc = pvoid;

	struct sockaddr_in6 addr;
	socklen_t alen = sizeof(addr);

	struct timeval tv;

	char tmpstr[32];
	struct svpn_net_ipv4_header* pheader = NULL;
	unsigned char buffer[BUFFER_LEN], tmp_buffer[BUFFER_LEN];
	int ret, uid, len;
	fd_set fd_list;
	int maxfd = (psc->sock_fd > psc->tun_fd) ? psc->sock_fd : psc->tun_fd;
	maxfd++;

	strcpy(fmtstr, "Send:99,000,000,000B [9,000,000B/s], Recv:99,000,000,000B [9,000,000B/s]\r");

	memset(&stat, 0, sizeof(stat));
	gettimeofday(&tv, NULL);
	stat.ts_last = tv.tv_sec * 1000000LL + tv.tv_usec;

	while(1)
	{
		FD_ZERO(&fd_list);
		FD_SET(psc->tun_fd, &fd_list);
		FD_SET(psc->sock_fd, &fd_list);
		
		ret = select(maxfd, &fd_list, NULL, NULL, NULL);
		if(ret < 0)
		{
			if(errno == EINTR)
				return 0;
			continue;
		}

		// update statistics data
		gettimeofday(&tv, NULL);
		stat.ts_current = tv.tv_sec * 1000000LL + tv.tv_usec;


		if(FD_ISSET(psc->sock_fd, &fd_list))
		{
			len = recvfrom(psc->sock_fd, tmp_buffer, BUFFER_LEN, 0, 
				(struct sockaddr*)&addr, &alen);

			if(len <= 0 || len > BUFFER_LEN)
				continue;

			uid = tmp_buffer[0];
			if (psc->clients[uid] == NULL)
			{
				mprintf(LWARN, "Unknown user #%d", uid);
				continue;
			}

			Decrypt(&(psc->clients[uid]->table), tmp_buffer, buffer, len);

			pheader = (struct svpn_net_ipv4_header*)buffer;
			if (pheader->src_ip[0] != psc->local_addr[0] ||
				pheader->src_ip[1] != psc->local_addr[1] ||
				pheader->src_ip[2] != psc->local_addr[2] ||
				pheader->src_ip[3] != uid)
			{
				mprintf(LWARN, "Invalid password : %s", inet_ntop(PF_INET6, (char*)&addr + 8, tmpstr, sizeof(tmpstr)));
				continue;
			}

			if (memcmp(&addr, &psc->clients[uid]->addr, sizeof(addr)) != 0)
			{
				memcpy(&psc->clients[uid]->addr, &addr, sizeof(addr));
				mprintf(LINFO, "Client #%d move to %s", uid,
						inet_ntop(PF_INET6, (char*)&addr + 8, tmpstr, sizeof(tmpstr)));
			}

			stat.total_send += len;
			stat.total_pkgsend++;
			output_info();

			len = write(psc->tun_fd, buffer, len);
		}

		if(FD_ISSET(psc->tun_fd, &fd_list))
		{
			len = read(psc->tun_fd, tmp_buffer, BUFFER_LEN);

			if (len <= 0 || len > BUFFER_LEN)
				continue;

			pheader = (struct svpn_net_ipv4_header*)tmp_buffer;

			uid = pheader->dst_ip[3];
			if (psc->clients[uid] == NULL)
			{
				mprintf(LWARN, "User #%d not exist", uid);
				continue;
			}

			Encrypt(&(psc->clients[uid]->table), tmp_buffer, buffer, len);

			len = sendto(psc->sock_fd, buffer, len, 0,
					(struct sockaddr*)&psc->clients[uid]->addr,
					sizeof(struct sockaddr_in6));

			if (len <= 0)
			{
				mprintf(LERROR, "Client #%d disconnected", uid);
				continue;
			}

			// update statistics data
			stat.total_recv += len;
			stat.total_pkgrecv++;
			output_info();
		}
	}
	return 0;
}