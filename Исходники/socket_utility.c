int recv_data2(int fd,char * buffer,int buffer_len, struct sockaddr* from, socklen_t* fromlen)
{
	return recvfrom(fd, buffer, buffer_len, 0, from, fromlen);
}