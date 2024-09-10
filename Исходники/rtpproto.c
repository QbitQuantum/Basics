static int rtp_read(URLContext *h, uint8_t *buf, int size)
{
	RTPContext *s = h->priv_data;
	struct sockaddr_storage from;
	socklen_t from_len;
	int len, n;
	struct pollfd p[2] = {{s->rtp_fd, POLLIN, 0}, {s->rtcp_fd, POLLIN, 0}};

#if 0
	for(;;)
	{
		from_len = sizeof(from);
		len = recvfrom (s->rtp_fd, buf, size, 0,
		(struct sockaddr *)&from, &from_len);
		if (len < 0)
		{
			if (ff_neterrno() == AVERROR(EAGAIN) ||
			ff_neterrno() == AVERROR(EINTR))
				continue;
			return AVERROR(EIO);
		}
		break;
	}
#else
	for(;;)
	{
		if (url_interrupt_cb())
			return AVERROR_EXIT;
		/* build fdset to listen to RTP and RTCP packets */
		n = poll(p, 2, 100);
		if (n > 0)
		{
			/* first try RTCP */
			if (p[1].revents & POLLIN)
			{
				from_len = sizeof(from);
				len = recvfrom (s->rtcp_fd, buf, size, 0,
				(struct sockaddr *)&from, &from_len);
				if (len < 0)
				{
					if (ff_neterrno() == AVERROR(EAGAIN) ||
					ff_neterrno() == AVERROR(EINTR))
						continue;
					return AVERROR(EIO);
				}
				break;
			}
			/* then RTP */
			if (p[0].revents & POLLIN)
			{
				from_len = sizeof(from);
				len = recvfrom (s->rtp_fd, buf, size, 0,
				(struct sockaddr *)&from, &from_len);
				if (len < 0)
				{
					if (ff_neterrno() == AVERROR(EAGAIN) ||
					ff_neterrno() == AVERROR(EINTR))
						continue;
					return AVERROR(EIO);
				}
				break;
			}
		}
		else if (n < 0)
		{
			if (ff_neterrno() == AVERROR(EINTR))
				continue;
			return AVERROR(EIO);
		}
	}
#endif
	return len;
}