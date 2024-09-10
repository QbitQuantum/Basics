/*
 * NAME
 *   run - connect thread routine
 * DESC
 *  - When success: delete arg
 *  - When fail: arg valid => delete arg, clientHandler valid => delete clientHandler
 */
void * ConnectToServerBySockfd::run(void * arg)
{
	/* Check */
	if (NULL == arg) {
		return (void *)-error::INVALIDSOCKARG;
	}
	/* Dump */
	SockConnParams * cps = static_cast<SockConnParams *>(arg);
	ClientHandler * clientHandler = cps->clientHandler();
	if (NULL == clientHandler) {
		delete cps;
		cps = NULL;
		return (void *)-error::NOCLICB;
	}
	/* Real dump*/
	ConnectHandler conHandler;
	int sockfd;
	NetProtocol target;
	if (0x00000001 != this->ver()) {
		sockfd = cps->sockfd();
		memcpy(&target, cps->target(), sizeof(NetProtocol));
		memcpy(&(conHandler.info), &target, sizeof(NetProtocol));
		conHandler.sockfd = sockfd;
	} else {
		sockfd = -1;
	}
	uint32_t timeout = cps->timeout();
	conHandler.code = 0;
	int code = 0;
	char msg[128];
	std::string ip;
	struct timeval tv_select;
	int ret;
	fd_set fdwrite;
	SockClientRecviveParams * rcvparams = NULL;
	do {
		if (0x00000001 == this->ver()) {
			ip = cps->ip();
			strncpy(target.ip, ip.c_str(), OYWS_MAXIPLEN);
			target.port = cps->port();
			snprintf(msg, 127, "To connect server: %s:%u", target.ip,
				target.port);
			msg[127] = '\0';
			OYWL_INFOSTR(msg);
			/* FIXME valid ip first */
			sockfd = GetSockfdByHost(target);
			if (sockfd < 0) {
				goto retry_later;
			} else {
				memcpy(&(conHandler.info), &target, sizeof(NetProtocol));
				conHandler.sockfd = sockfd;
			}
		}
		/* Wait(select) writeable */
		FD_ZERO(&fdwrite);
		FD_SET(sockfd, &fdwrite);
		tv_select.tv_sec = timeout;
		tv_select.tv_usec = 0;
		ret = select(sockfd + 1, NULL, &fdwrite, NULL, &tv_select);
		/* FIXME: handle EINTR here and other .. (block)
		 * or EAGAIN of noneblock */
		if (ret < 0) {
			ret = errno;
			code = -ret;
			if (0x00000001 == this->ver()) {
				goto retry_later;
			} else {
				goto select_fail;
			}
		} else if (0 == ret) {
			/* timeout */
			code = -ETIMEDOUT;
			if (0x00000001 == this->ver()) {
				goto retry_later;
			} else {
				goto select_to;
			}
		} else {
			/* final check sokcet error */
			int errlen = sizeof(ret);
#			if !defined(WIN32)
			getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &ret,
				(socklen_t *)&errlen);
#			else
			getsockopt(sockfd, SOL_SOCKET, SO_ERROR,
				reinterpret_cast<char *>(&ret),
				(socklen_t *)&errlen);
#			endif

			if (0 != ret) {
				/* connect fail */
				errno = ret;
				code = -ret;
				snprintf(msg, 127, "FAIL: select: %s", strerror(ret));
				msg[127] = '\0';
				if (0x00000001 == this->ver()) {
					goto retry_later;
				} else {
					goto select_fail;
				}
			}
		}
		break;/* ok */
retry_later:
		if (sockfd > 0) {
			CloseSocket(sockfd);
			sockfd = -1;
		}
		usleep(10 * 1e6);
		usleep(10 * 1e6);
		usleep(10 * 1e6);
	} while(true);
	/* Final ok */
#	if defined(__APPLE__)
	{
	int set = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));
	}
#	endif /* defined(__APPLE__) */
	{
	rcvparams = new SockClientRecviveParams(sockfd, clientHandler, target);
	/* start on received thread */
	ret = ClientHelper::startReceiveFromPeer(rcvparams);
	if (0 != ret) {
		OYWL_ERRSN("startReceiveFromPeer() fail", ret);
		code = ret;
		delete rcvparams;
		rcvparams = NULL;
	} else {
		/* success */
		code = 0;
	}
	rcvparams = NULL;
	}
	/* Feedback */
	conHandler.code = code;
	clientHandler->didConnect(conHandler);
	if (0 != code) {
		OYWL_SN0("Will delete clientHandler by code", code);
		delete clientHandler;
		clientHandler = NULL;
	}
	/* Final delete */
	if (NULL != cps) {
		OYWL_S0("Will delete cps");
		delete cps;
		cps = NULL;
	}
	return reinterpret_cast<void *>(0);/* Success */
select_to:
select_fail:
	if (NULL != clientHandler) {
		conHandler.code = code;
		clientHandler->didConnect(conHandler);
		OYWL_S0("Will delete clientHandler by not nil");
		delete clientHandler;
		clientHandler = NULL;
	}
	if (NULL != rcvparams) {
		delete rcvparams;
		rcvparams = NULL;
	}
	/* Final delete */
	if (NULL != cps) {
		OYWL_S0("Will delete cps");
		delete cps;
		cps = NULL;
	}
	return (void *)-1;
}