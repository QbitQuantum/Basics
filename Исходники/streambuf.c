static int stream_readL(lua_State *L) {
	struct stream *stream;
	u8_t buf[1024];
	u8_t *buf_ptr, *body_ptr;
	size_t header_len;
	ssize_t n;

	/*
	 * 1: Stream (self)
	 * 2: Playback (self)
	 */

	stream = lua_touserdata(L, 1);


	/* shortcut, just read to streambuf */
	if (stream->num_crlf == 4) {
		n = streambuf_feed_fd(stream->fd, L);
		if (n == 0) {
			/* closed */
			lua_pushboolean(L, FALSE);
			return 1;
		}

		if (n == -ENOSPC) {
			lua_pushinteger(L, 0);
			return 1;
		}

		if (n < 0) {
			CLOSESOCKET(stream->fd);

			lua_pushnil(L);
			lua_pushstring(L, strerror(n));
			return 2;

		}

		lua_pushinteger(L, n);
		return 1;
	}

	/* read buffer, but we must not overflow the stream fifo */
	n = streambuf_get_freebytes();
	if (n > (ssize_t)sizeof(buf)) {
		n = sizeof(buf);
	}

	n = recv(stream->fd, buf, sizeof(buf), 0);

	/* socket closed */
	if (n == 0) {
		lua_pushboolean(L, FALSE);
		return 1;
	}

	/* socket error */
	if (n < 0) {
		// XXXX do we need to handle timeout here?
		CLOSESOCKET(stream->fd);

		lua_pushnil(L);
		lua_pushstring(L, strerror(SOCKETERROR));
		return 2;
	}

	buf_ptr = buf;


	/* read http header */
	if (stream->num_crlf < 4) {
		stream->body = realloc(stream->body, stream->body_len + n);
		body_ptr = stream->body + stream->body_len;
		stream->body_len += n;

		while (n) {
			*body_ptr++ = *buf_ptr;

			if (*buf_ptr == '\n' || *buf_ptr == '\r') {
				stream->num_crlf++;
			}
			else {
				stream->num_crlf = 0;
			}

			buf_ptr++;
			n--;

			if (stream->num_crlf == 4) {
				header_len = body_ptr - stream->body;

				//LOG_DEBUG(log_audio_decode, "headers %d %*s\n", header_len, header_len, stream->body);

				/* Send headers to SqueezeCenter */
				lua_getfield(L, 2, "_streamHttpHeaders");
				lua_pushvalue(L, 2);
				lua_pushlstring(L, (char *)stream->body, header_len);
				lua_call(L, 2, 0);

				/* do not free the header here - leave it to disconnect -
				 * so that it can be used by the proxy code
				 */

				/* Send headers to proxy clients */
				proxy_chunk(stream->body, header_len, L);

				break;
			}
		}
	}

	/* we need to loop when playing sound effects, so we need to remember where the stream starts */
	streambuf_lptr = streambuf_fifo.wptr;

	/* feed remaining buffer */
	streambuf_feedL(buf_ptr, n, L);

	lua_pushboolean(L, TRUE);
	return 1;
}