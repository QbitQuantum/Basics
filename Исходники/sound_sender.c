JNIEXPORT jint JNICALL
Java_com_ghostagent_SoundManagementNative_connect(JNIEnv *env, jobject obj,
						  jint sockfd, jint timeout,
						  jstring address, jint port)
{
	const char *cp;
	struct sockaddr_in addr;
	int flags;
	int ret;
	fd_set wset;
	struct timeval tv;
	int error;
	socklen_t len;

	cp = (*env)->GetStringUTFChars(env, address, NULL);
	if (cp == NULL)
		return -1;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(cp);

	(*env)->ReleaseStringUTFChars(env, address, cp);

	flags = fcntl(sockfd, F_GETFL);
	if (flags < 0)
		return -1;

	if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) < 0)
		return -1;

	ret = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if (ret == 0) {
		fcntl(sockfd, F_SETFL, flags);
		return 0;
	}
	if (errno != EINPROGRESS) {
		fcntl(sockfd, F_SETFL, flags);
		return -1;
	}

	FD_ZERO(&wset);
	FD_SET(sockfd, &wset);

	memset(&tv, 0, sizeof(tv));
	tv.tv_sec = (time_t)timeout;

	if (select(sockfd + 1, NULL, &wset, NULL, &tv) <= 0) {
		fcntl(sockfd, F_SETFL, flags);
		return -1;
	}

	len = sizeof(error);
	ret = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len);
	if (ret < 0 || error != 0) {
		fcntl(sockfd, F_SETFL, flags);
		return -1;
	}

	fcntl(sockfd, F_SETFL, flags);
	return 0;
}