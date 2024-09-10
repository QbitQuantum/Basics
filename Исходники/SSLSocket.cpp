int SSLSocket::checkSSL(int ret) {
	if(!ssl) {
		return -1;
	}
	if(ret <= 0) {
		/* inspired by boost.asio (asio/ssl/detail/impl/engine.ipp, function engine::perform) and
		the SSL_get_error doc at <https://www.openssl.org/docs/ssl/SSL_get_error.html>. */
		auto err = SSL_get_error(ssl, ret);
		switch(err) {
		case SSL_ERROR_NONE:		// Fallthrough - YaSSL doesn't for example return an openssl compatible error on recv fail
		case SSL_ERROR_WANT_READ:	// Fallthrough
		case SSL_ERROR_WANT_WRITE:
			return -1;
		case SSL_ERROR_ZERO_RETURN:
			throw SocketException(STRING(CONNECTION_CLOSED));
		case SSL_ERROR_SYSCALL:
			{
				auto sys_err = ERR_get_error();
				if(sys_err == 0) {
					if(ret == 0) {
						dcdebug("TLS error: call ret = %d, SSL_get_error = %d, ERR_get_error = %d\n", ret, err, sys_err);
						throw SSLSocketException(STRING(CONNECTION_CLOSED));
					}
					sys_err = getLastError();
				}
				throw SSLSocketException(sys_err);
			}
		default:
			/* don't bother getting error messages from the codes because 1) there is some
			additional management necessary (eg SSL_load_error_strings) and 2) openssl error codes
			aren't shown to the end user; they only hit standard output in debug builds. */
			dcdebug("TLS error: call ret = %d, SSL_get_error = %d, ERR_get_error = %d\n", ret, err, ERR_get_error());
			throw SSLSocketException(STRING(TLS_ERROR));
		}
	}
	return ret;
}