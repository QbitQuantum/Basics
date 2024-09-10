void SctpSocket::OnRead()
{
/*
	int sctp_recvmsg(int sd, void * msg, size_t * len,
		struct sockaddr * from, socklen_t * fromlen,
		struct sctp_sndrcvinfo * sinfo, int * msg_flags);

	DESCRIPTION
	sctp_recvmsg  is  a  wrapper library function that can be used to receive a message from a socket while using the advanced
	features of SCTP.  sd is the socket descriptor on which the message pointed to by msg of length len is received.

	If from is not NULL, the source address of the message is filled in. The argument fromlen  is  a  value-result  parameter.
	initialized  to  the  size  of the buffer associated with from , and modified on return to indicate the actual size of the
	address stored.

	sinfo is a pointer to a sctp_sndrcvinfo structure to be filled upon receipt of the message.  msg_flags is a pointer  to  a
	integer that is filled with any message flags like MSG_NOTIFICATION or MSG_EOR.

*/
	struct sockaddr sa;
	socklen_t sa_len = 0;
	struct sctp_sndrcvinfo sinfo;
	int flags = 0;
	int n = sctp_recvmsg(GetSocket(), m_buf, SCTP_BUFSIZE_READ, &sa, &sa_len, &sinfo, &flags);
	if (n == -1)
	{
		Handler().LogError(this, "SctpSocket", Errno, StrError(Errno), LOG_LEVEL_FATAL);
		SetCloseAndDelete();
	}
	else
	{
		OnReceiveMessage(m_buf, n, &sa, sa_len, &sinfo, flags);
	}
}