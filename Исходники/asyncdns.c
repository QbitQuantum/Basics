int async_resolve_host(char *host, int port, struct sockaddr_in *sockaddr, int msec_timeout, int *active) {
	msec_timeout = msec_timeout;
	active = active;
	struct hostent *hostinfo = gethostbyname(host);
	if (hostinfo == NULL) {
		int local_h_errno = h_errno;
		LOGf("gethostbyname(%s) returned %s", host, hstrerror(local_h_errno));
		return 1; // error
	}
	sockaddr->sin_family = AF_INET;
	sockaddr->sin_port = htons(port);
	sockaddr->sin_addr = *(struct in_addr *)hostinfo->h_addr;
	// LOGf("Not using async resolver! Resolved %s to %s\n", host, inet_ntoa(sockaddr->sin_addr));
	return 0;
}