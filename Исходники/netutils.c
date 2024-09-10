/* connects to a host on a specified tcp port, sends a string, and gets a
	 response. loops on select-recv until timeout or eof to get all of a
	 multi-packet answer */
int
process_tcp_request2 (const char *server_address, int server_port,
	const char *send_buffer, char *recv_buffer, int recv_size)
{

	int result;
	int send_result;
	int recv_result;
	int sd;
	struct timeval tv;
	fd_set readfds;
	int recv_length = 0;

	result = np_net_connect (server_address, server_port, &sd, IPPROTO_TCP);
	if (result != STATE_OK)
		return STATE_CRITICAL;

	send_result = send (sd, send_buffer, strlen (send_buffer), 0);
	if (send_result<0 || (size_t)send_result!=strlen(send_buffer)) {
		printf ("%s\n", _("Send failed"));
		result = STATE_WARNING;
	}

	while (1) {
		/* wait up to the number of seconds for socket timeout
		   minus one for data from the host */
		tv.tv_sec = socket_timeout - 1;
		tv.tv_usec = 0;
		FD_ZERO (&readfds);
		FD_SET (sd, &readfds);
		select (sd + 1, &readfds, NULL, NULL, &tv);

		/* make sure some data has arrived */
		if (!FD_ISSET (sd, &readfds)) {	/* it hasn't */
			if (!recv_length) {
				strcpy (recv_buffer, "");
				printf ("%s\n", _("No data was received from host!"));
				result = STATE_WARNING;
			}
			else {										/* this one failed, but previous ones worked */
				recv_buffer[recv_length] = 0;
			}
			break;
		}
		else {											/* it has */
			recv_result =
				recv (sd, recv_buffer + recv_length,
					(size_t)recv_size - recv_length - 1, 0);
			if (recv_result == -1) {
				/* recv failed, bail out */
				strcpy (recv_buffer + recv_length, "");
				result = STATE_WARNING;
				break;
			}
			else if (recv_result == 0) {
				/* end of file ? */
				recv_buffer[recv_length] = 0;
				break;
			}
			else {										/* we got data! */
				recv_length += recv_result;
				if (recv_length >= recv_size - 1) {
					/* buffer full, we're done */
					recv_buffer[recv_size - 1] = 0;
					break;
				}
			}
		}
		/* end if(!FD_ISSET(sd,&readfds)) */
	}
	/* end while(1) */

	close (sd);
	return result;
}