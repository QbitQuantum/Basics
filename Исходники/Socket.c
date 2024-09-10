/* WARNING: all parameters MUST be valid,
 *          NULL pointers lead to a crash.
 */
ret_t
cherokee_socket_read (cherokee_socket_t *socket,
		      char              *buf,
		      int                buf_size,
		      size_t            *pcnt_read)
{
	ret_t   ret;
	ssize_t len;

	*pcnt_read = 0;

	/* There must be something to read, otherwise behaviour is undefined
	 * and as we don't want this case, we have to enforce assertions.
	 */
	return_if_fail (buf != NULL && buf_size > 0, ret_error);

	if (unlikely (socket->status == socket_closed)) {
		TRACE(ENTRIES, "Reading a closed socket: fd=%d (TLS=%d)\n", SOCKET_FD(socket), (socket->is_tls == TLS));
		return ret_eof;
	}

	if (likely (socket->is_tls != TLS)) {
		/* Plain read
		 */
		len = recv (SOCKET_FD(socket), buf, buf_size, 0);

		if (likely (len > 0)) {
			*pcnt_read = len;
			return ret_ok;
		}

		if (len == 0) {
			socket->status = socket_closed;
			return ret_eof;
		}

		{	/* len < 0 */
			int err = SOCK_ERRNO();

			TRACE(ENTRIES",read", "Socket read error fd=%d: '%s'\n",
			      SOCKET_FD(socket), strerror(errno));

			switch (err) {
#if defined(EWOULDBLOCK) && (EWOULDBLOCK != EAGAIN)
			case EWOULDBLOCK:
#endif
			case EINTR:
			case EAGAIN:
				return ret_eagain;

			case EPIPE:
#ifdef ENOTCONN
			case ENOTCONN:
#endif
			case ECONNRESET:
				socket->status = socket_closed;
			case ETIMEDOUT:
			case EHOSTUNREACH:
				return ret_error;
			}

			LOG_ERRNO (errno, cherokee_err_error,
				   CHEROKEE_ERROR_SOCKET_READ, SOCKET_FD(socket));
		}
		return ret_error;

	} else if (socket->cryptor != NULL) {
		ret = cherokee_cryptor_socket_read (socket->cryptor,
						    buf, buf_size, pcnt_read);
		switch (ret) {
		case ret_ok:
		case ret_error:
		case ret_eagain:
			return ret;
		case ret_eof:
			socket->status = socket_closed;
			return ret_eof;
		default:
			RET_UNKNOWN(ret);
			return ret;
		}
	}

	return ret_error;
}