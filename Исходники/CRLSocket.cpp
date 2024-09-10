CCRLSocket::CCRLSocket() {
	int buffer_size = 1024 * 1024 * 16;
	SetSockOpt(SO_RCVBUF, &buffer_size, sizeof(int));
}