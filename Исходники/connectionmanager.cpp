void ConnectionManager::sendDatagram(const char* buf, size_t len, int controlFd)
{
	char control[sizeof(struct cmsghdr)+10];
	struct msghdr msg;
	struct cmsghdr *cmsg;
	struct iovec iov;

	/* Response data */
	iov.iov_base = const_cast<char*>(buf);
	iov.iov_len = len;

	/* compose the message */
	memset(&msg, 0, sizeof(msg));
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	/* send controlFd */
	if (controlFd > 0) {
		msg.msg_control = control;
		msg.msg_controllen = sizeof(control);
		cmsg = CMSG_FIRSTHDR(&msg);
		cmsg->cmsg_level = SOL_SOCKET;
		cmsg->cmsg_type = SCM_RIGHTS;
		cmsg->cmsg_len = CMSG_LEN(sizeof(controlFd));
		memcpy(reinterpret_cast<void *>(CMSG_DATA(cmsg)), &controlFd, sizeof(controlFd));
		msg.msg_controllen = cmsg->cmsg_len;
	}

	if (sendmsg(connectionFd, &msg, MSG_DONTWAIT) < 0) {
		TWARN("sendmsg error %s", strerror(errno));
		connectionClose();
		//close(connFd);
		return;
	}
}