/* httpread_read_handler -- called when socket ready to read
 *
 * Note: any extra data we read past end of transmitted file is ignored;
 * if we were to support keeping connections open for multiple files then
 * this would have to be addressed.
 */
static void httpread_read_handler(int sd, void *eloop_ctx, void *sock_ctx)
{
	struct httpread *h = sock_ctx;
	int nread;
	char *rbp;      /* pointer into read buffer */
	char *hbp;      /* pointer into header buffer */
	char *bbp;      /* pointer into body buffer */
	char readbuf[HTTPREAD_READBUF_SIZE];  /* temp use to read into */

	if (httpread_debug >= 20)
		wpa_printf(MSG_DEBUG, "ENTER httpread_read_handler(%p)", h);

	/* read some at a time, then search for the interal
	 * boundaries between header and data and etc.
	 */
	nread = read(h->sd, readbuf, sizeof(readbuf));
	if (nread < 0)
		goto bad;
	if (nread == 0) {
		/* end of transmission... this may be normal
		 * or may be an error... in some cases we can't
		 * tell which so we must assume it is normal then.
		 */
		if (!h->got_hdr) {
			/* Must at least have completed header */
			wpa_printf(MSG_DEBUG, "httpread premature eof(%p)", h);
			goto bad;
		}
		if (h->chunked || h->got_content_length) {
			/* Premature EOF; e.g. dropped connection */
			wpa_printf(MSG_DEBUG,
				   "httpread premature eof(%p) %d/%d",
				   h, h->body_nbytes,
				   h->content_length);
			goto bad;
		}
		/* No explicit length, hopefully we have all the data
		 * although dropped connections can cause false
		 * end
		 */
		if (httpread_debug >= 10)
			wpa_printf(MSG_DEBUG, "httpread ok eof(%p)", h);
			h->got_body = 1;
			goto got_file;
	}
	rbp = readbuf;

	/* Header consists of text lines (terminated by both CR and LF)
	 * and an empty line (CR LF only).
	 */
	if (!h->got_hdr) {
		hbp = h->hdr + h->hdr_nbytes;
		/* add to headers until:
		 *      -- we run out of data in read buffer
		 *      -- or, we run out of header buffer room
		 *      -- or, we get double CRLF in headers
		 */
		for (;;) {
			if (nread == 0)
				goto get_more;
			if (h->hdr_nbytes == HTTPREAD_HEADER_MAX_SIZE) {
				goto bad;
			}
			*hbp++ = *rbp++;
			nread--;
			h->hdr_nbytes++;
			if (h->hdr_nbytes >= 4 &&
			    hbp[-1] == '\n' &&
			    hbp[-2] == '\r' &&
			    hbp[-3] == '\n' &&
			    hbp[-4] == '\r' ) {
				h->got_hdr = 1;
				*hbp = 0;       /* null terminate */
				break;
			}
		}
		/* here we've just finished reading the header */
		if (httpread_hdr_analyze(h)) {
			wpa_printf(MSG_DEBUG, "httpread bad hdr(%p)", h);
			goto bad;
		}
		if (h->max_bytes == 0) {
			if (httpread_debug >= 10)
				wpa_printf(MSG_DEBUG,
					   "httpread no body hdr end(%p)", h);
			goto got_file;
		}
		if (h->got_content_length && h->content_length == 0) {
			if (httpread_debug >= 10)
				wpa_printf(MSG_DEBUG,
					   "httpread zero content length(%p)",
					   h);
			goto got_file;
		}
	}

	/* Certain types of requests never have data and so
	 * must be specially recognized.
	 */
	if (!os_strncasecmp(h->hdr, "SUBSCRIBE", 9) ||
	    !os_strncasecmp(h->hdr, "UNSUBSCRIBE", 11) ||
	    !os_strncasecmp(h->hdr, "HEAD", 4) ||
	    !os_strncasecmp(h->hdr, "GET", 3)) {
		if (!h->got_body) {
			if (httpread_debug >= 10)
				wpa_printf(MSG_DEBUG,
					   "httpread NO BODY for sp. type");
		}
		h->got_body = 1;
		goto got_file;
	}

	/* Data can be just plain binary data, or if "chunked"
	 * consists of chunks each with a header, ending with
	 * an ending header.
	 */
	if (nread == 0)
		goto get_more;
	if (!h->got_body) {
		/* Here to get (more of) body */
		/* ensure we have enough room for worst case for body
		 * plus a null termination character
		 */
		if (h->body_alloc_nbytes < (h->body_nbytes + nread + 1)) {
			char *new_body;
			int new_alloc_nbytes;

			if (h->body_nbytes >= h->max_bytes)
				goto bad;
			new_alloc_nbytes = h->body_alloc_nbytes +
				HTTPREAD_BODYBUF_DELTA;
			/* For content-length case, the first time
			 * through we allocate the whole amount
			 * we need.
			 */
			if (h->got_content_length &&
			    new_alloc_nbytes < (h->content_length + 1))
				new_alloc_nbytes = h->content_length + 1;
			if ((new_body = os_realloc(h->body, new_alloc_nbytes))
			    == NULL)
				goto bad;

			h->body = new_body;
			h->body_alloc_nbytes = new_alloc_nbytes;
		}
		/* add bytes */
		bbp = h->body + h->body_nbytes;
		for (;;) {
			int ncopy;
			/* See if we need to stop */
			if (h->chunked && h->in_chunk_data == 0) {
				/* in chunk header */
				char *cbp = h->body + h->chunk_start;
				if (bbp-cbp >= 2 && bbp[-2] == '\r' &&
				    bbp[-1] == '\n') {
					/* end of chunk hdr line */
					/* hdr line consists solely
					 * of a hex numeral and CFLF
					 */
					if (!isxdigit(*cbp))
						goto bad;
					h->chunk_size = strtoul(cbp, NULL, 16);
					/* throw away chunk header
					 * so we have only real data
					 */
					h->body_nbytes = h->chunk_start;
					bbp = cbp;
					if (h->chunk_size == 0) {
						/* end of chunking */
						/* trailer follows */
						h->in_trailer = 1;
						if (httpread_debug >= 20)
							wpa_printf(
								MSG_DEBUG,
								"httpread end chunks(%p)", h);
						break;
					}
					h->in_chunk_data = 1;
					/* leave chunk_start alone */
				}
			} else if (h->chunked) {
				/* in chunk data */
				if ((h->body_nbytes - h->chunk_start) ==
				    (h->chunk_size + 2)) {
					/* end of chunk reached,
					 * new chunk starts
					 */
					/* check chunk ended w/ CRLF
					 * which we'll throw away
					 */
					if (bbp[-1] == '\n' &&
					    bbp[-2] == '\r') {
					} else
						goto bad;
					h->body_nbytes -= 2;
					bbp -= 2;
					h->chunk_start = h->body_nbytes;
					h->in_chunk_data = 0;
					h->chunk_size = 0; /* just in case */
				}
			} else if (h->got_content_length &&
				   h->body_nbytes >= h->content_length) {
				h->got_body = 1;
				if (httpread_debug >= 10)
					wpa_printf(
						MSG_DEBUG,
						"httpread got content(%p)", h);
				goto got_file;
			}
			if (nread <= 0)
				break;
			/* Now transfer. Optimize using memcpy where we can. */
			if (h->chunked && h->in_chunk_data) {
				/* copy up to remainder of chunk data
				 * plus the required CR+LF at end
				 */
				ncopy = (h->chunk_start + h->chunk_size + 2) -
					h->body_nbytes;
			} else if (h->chunked) {
				/*in chunk header -- don't optimize */
				*bbp++ = *rbp++;
				nread--;
				h->body_nbytes++;
				continue;
			} else if (h->got_content_length) {
				ncopy = h->content_length - h->body_nbytes;
			} else {
				ncopy = nread;
			}
			/* Note: should never be 0 */
			if (ncopy > nread)
				ncopy = nread;
			os_memcpy(bbp, rbp, ncopy);
			bbp += ncopy;
			h->body_nbytes += ncopy;
			rbp += ncopy;
			nread -= ncopy;
		}       /* body copy loop */
	}       /* !got_body */
	if (h->chunked && h->in_trailer) {
		/* If "chunked" then there is always a trailer,
		 * consisting of zero or more non-empty lines
		 * ending with CR LF and then an empty line w/ CR LF.
		 * We do NOT support trailers except to skip them --
		 * this is supported (generally) by the http spec.
		 */
		bbp = h->body + h->body_nbytes;
		for (;;) {
			int c;
			if (nread <= 0)
				break;
			c = *rbp++;
			nread--;
			switch (h->trailer_state) {
			case trailer_line_begin:
				if (c == '\r')
					h->trailer_state = trailer_empty_cr;
				else
					h->trailer_state = trailer_nonempty;
				break;
			case trailer_empty_cr:
				/* end empty line */
				if (c == '\n') {
					h->trailer_state = trailer_line_begin;
					h->in_trailer = 0;
					if (httpread_debug >= 10)
						wpa_printf(
							MSG_DEBUG,
							"httpread got content(%p)", h);
					h->got_body = 1;
					goto got_file;
				}
				h->trailer_state = trailer_nonempty;
				break;
			case trailer_nonempty:
				if (c == '\r')
					h->trailer_state = trailer_nonempty_cr;
				break;
			case trailer_nonempty_cr:
				if (c == '\n')
					h->trailer_state = trailer_line_begin;
				else
					h->trailer_state = trailer_nonempty;
				break;
			}
		}
	}
	goto get_more;

bad:
	/* Error */
	wpa_printf(MSG_DEBUG, "httpread read/parse failure (%p)", h);
	(*h->cb)(h, h->cookie, HTTPREAD_EVENT_ERROR);
	return;

get_more:
	return;

got_file:
	if (httpread_debug >= 10)
		wpa_printf(MSG_DEBUG,
			   "httpread got file %d bytes type %d",
			   h->body_nbytes, h->hdr_type);
	/* Null terminate for convenience of some applications */
	if (h->body)
		h->body[h->body_nbytes] = 0; /* null terminate */
	h->got_file = 1;
	/* Assume that we do NOT support keeping connection alive,
	 * and just in case somehow we don't get destroyed right away,
	 * unregister now.
	 */
	if (h->sd_registered)
		eloop_unregister_sock(h->sd, EVENT_TYPE_READ);
	h->sd_registered = 0;
	/* The application can destroy us whenever they feel like...
	 * cancel timeout.
	 */
	if (h->to_registered)
		eloop_cancel_timeout(httpread_timeout_handler, NULL, h);
	h->to_registered = 0;
	(*h->cb)(h, h->cookie, HTTPREAD_EVENT_FILE_READY);
}