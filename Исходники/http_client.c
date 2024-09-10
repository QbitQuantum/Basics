int
http_stream_read(char *buf,
                 int len,
                 int *err)
{    
    struct _stream *s = &http_stream;
    int total = 0;
    int cnt, code;

    if (!s->open) {
        return -1;  // Shouldn't happen, but...
    }
    while (len) {
        while (s->avail == 0) {
            // Need to wait for some data to arrive
            __tcp_poll();
            if (s->sock.state != _ESTABLISHED) {
                if (s->sock.state == _CLOSE_WAIT) {
                    // This connection is breaking
                    if (s->sock.data_bytes == 0 && s->sock.rxcnt == 0) {
                        __tcp_close(&s->sock);
                        return total;
                    }  
                } else if (s->sock.state == _CLOSED) {
                    	// The connection is gone
                    	s->open = false;
                    	return -1;
                } else {	
                    *err = HTTP_IO;
                    return -1;
		}
            }
            s->actual_len = __tcp_read(&s->sock, s->data, sizeof(s->data));
            if (s->actual_len > 0) {
                s->bufp = s->data;
                s->avail = s->actual_len;
                if (s->pos == 0) {
                    // First data - need to scan HTTP response header
                    if (strncmp(s->bufp, "HTTP/", 5) == 0) {
                        // Should look like "HTTP/1.1 200 OK"
                        s->bufp += 5;
                        s->avail -= 5;
                        // Find first space
                        while ((s->avail > 0) && (*s->bufp != ' ')) {
                            s->bufp++;  
                            s->avail--;
                        }
                        // Now the integer response
                        code = 0;
                        while ((s->avail > 0) && (*s->bufp == ' ')) {
                            s->bufp++;  
                            s->avail--;
                        }
                        while ((s->avail > 0) && isdigit(*s->bufp)) {
                            code = (code * 10) + (*s->bufp - '0');
                            s->bufp++;  
                            s->avail--;
                        }
                        // Make sure it says OK
                        while ((s->avail > 0) && (*s->bufp == ' ')) {
                            s->bufp++;  
                            s->avail--;
                        }
                        if (strncmp(s->bufp, "OK", 2)) {
                            *err = HTTP_BADHDR;
                            return -1;
                        }
                        // Find \r\n\r\n - end of HTTP preamble
                        while (s->avail > 4) {
                            // This could be done faster, but not simpler
                            if (strncmp(s->bufp, "\r\n\r\n", 4) == 0) {
                                s->bufp += 4;
                                s->avail -= 4;
#if 0 // DEBUG - show header
                                *(s->bufp-2) = '\0';
                                diag_printf(s->data);
#endif
                                break;
                            }
                            s->avail--;
                            s->bufp++;
                        }
                        s->pos++;
                    } else {
                        // Unrecognized response
                        *err = HTTP_BADHDR;
                        return -1;
                    }
                }
            } else if (s->actual_len < 0) {
                *err = HTTP_IO;
                return -1;
            }
        }
        cnt = min(len, s->avail);
        memcpy(buf, s->bufp, cnt);
        s->avail -= cnt;
        s->bufp += cnt;
        buf += cnt;
        total += cnt;
        len -= cnt;
    }
    return total;
}