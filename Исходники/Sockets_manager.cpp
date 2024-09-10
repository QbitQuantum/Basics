int	Sockets_manager::AcceptFromHost(void)
{
	Socket*	skt;
	char	ip[16];

	skt = this->GetHostSocket();
	if (skt != NULL)
	{
		int		fdmax;
		fd_set		fdread;
		struct timeval	timeout;

		fdmax = skt->fd + 1;
		FD_ZERO(&fdread);
		FD_SET(skt->fd, &fdread);
		timeout.tv_sec = 0;
		timeout.tv_usec = 0;
		if (select(fdmax, &fdread, 0, 0, &timeout) == -1)
			return -1;
		if (FD_ISSET(skt->fd, &fdread))
		{
			skt->Accept(&fdmax, ip);
			if (fdmax != -1)
			{
				skt = NULL;
				while (skt == NULL)
					skt = new Socket(fdmax, ip);
				this->clientSockets.push_back(skt);
				return 1;
			}
		}
	}
	return 0;

}