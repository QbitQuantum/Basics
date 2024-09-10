void recv_fp(int sockfd) {
	ssize_t		n;
	char		buf[MAXLINE];
	char *res = "new";
	char fp[FP_LEN+1];
	char filename[MAXLINE];
	fp[FP_LEN] = '\0';

	char	recvline[MAXLINE];
	struct sockaddr_in	cliaddr;
	socklen_t	cliaddrlen = sizeof(cliaddr);


	memset(recvline, 0, sizeof(recvline));
	n = Recvfrom(sockfd, recvline, MAXLINE, 0,  (SA *) &cliaddr, &cliaddrlen);

	memcpy(fp, recvline, FP_LEN);
	memcpy(filename, &recvline[FP_LEN], n - FP_LEN);
	filename[n - FP_LEN] = '\0';
	printf("**File FP: %s, File name: %s**\n", fp, filename);

	// look up this fp for dedu in the hash table
	int exists = isExistsFP(fp);
	// printf("recv_fp: isExistsFP=%d\n", exists);
	if(exists){
		res = "duplicated";
		Sendto(sockfd, res, strlen(res), 0, (SA *) &cliaddr, cliaddrlen);
		// addFilename2FP(fp, filename);
	}else{
		Sendto(sockfd, res, strlen(res), 0, (SA *) &cliaddr, cliaddrlen);
		// addFilename2FP(fp, filename);
		insertFP(fp); // just 1 to indicate
	}
}