void conn_data_handler P1(int, fd)
{
    int conn_index;
    int buf_index;
    int num_bytes;
    int msgtype;
    int leftover;
    char *buf;
    int res, msglen, expecting;
    long unread_bytes;

    if ((conn_index = index_by_fd(fd)) == -1) {
	fprintf(stderr, "conn_data_handler: invalid fd.\n");
	return;
    }
    debug(512, ("conn_data_handler: read on fd %d\n", fd));

    /* append new data to end of leftover data (if any) */
    leftover = all_conns[conn_index].leftover;
    buf = (char *) &all_conns[conn_index].buf[0];
    num_bytes = OS_socket_read(fd, buf + leftover, (IN_BUF_SIZE - 1) - leftover);

    switch (num_bytes) {
    case -1:
	switch (errno) {
#ifdef WIN32
	case WSAEWOULDBLOCK:
#endif
	case EWOULDBLOCK:
	    debug(512, ("conn_data_handler: read on fd %d: Operation would block.\n",
			fd));
	    break;
	default:
	    perror("conn_data_handler: read");
	    terminate(conn_index);
	    break;
	}
	break;
    case 0:
	if (all_conns[conn_index].state == CONN_CLOSED)
	    fprintf(stderr, "get_user_data: tried to read from closed fd.\n");
	terminate(conn_index);
	break;
    default:
	debug(512, ("conn_data_handler: read %d bytes on fd %d\n", num_bytes, fd));
	num_bytes += leftover;
	buf_index = 0;
	expecting = 0;
	while (num_bytes > sizeof(int) && buf_index < (IN_BUF_SIZE - 1)) {
	    /* get message type */
	    memcpy((char *) &msgtype, (char *) &buf[buf_index], sizeof(int));
	    debug(512, ("conn_data_handler: message type: %d\n", msgtype));

	    if (msgtype == NAMEBYIP) {
		if (buf[buf_index + sizeof(int)] == '\0') {
		    /* no data here...resync */
		    buf_index++;
		    num_bytes--;
		    continue;
		}
		if (expecting && num_bytes < expecting) {
		    /*
		     * message truncated...back up to DATALEN message; exit
		     * loop...and try again later
		     */
		    buf_index -= (sizeof(int) + sizeof(int));
		    num_bytes += (sizeof(int) + sizeof(int));
		    break;
		}
		res = name_by_ip(conn_index, &buf[buf_index]);
	    } else if (msgtype == IPBYNAME) {
		if (buf[buf_index + sizeof(int)] == '\0') {
		    /* no data here...resync */
		    buf_index++;
		    num_bytes--;
		    continue;
		}
		if (expecting && num_bytes < expecting) {
		    /*
		     * message truncated...back up to DATALEN message; exit
		     * loop...and try again later
		     */
		    buf_index -= (sizeof(int) + sizeof(int));
		    num_bytes += (sizeof(int) + sizeof(int));
		    break;
		}
		res = ip_by_name(conn_index, &buf[buf_index]);
	    } else if (msgtype == DATALEN) {
		if (num_bytes > (sizeof(int) + sizeof(int))) {
		    memcpy((char *) &expecting, (char *) &buf[buf_index + sizeof(int)], sizeof(int));
		    /*
		     * advance to next message
		     */
		    buf_index += (sizeof(int) + sizeof(int));
		    num_bytes -= (sizeof(int) + sizeof(int));
		    if (expecting > IN_BUF_SIZE || expecting <= 0) {
			fprintf(stderr, "conn_data_handler: bad data length %d\n", expecting);
			expecting = 0;
		    }
		    continue;
		} else {
		    /*
		     * not enough bytes...assume truncated; exit loop...we'll
		     * handle this message later
		     */
		    break;
		}
	    } else {
		fprintf(stderr, "conn_data_handler: unknown message type %08x\n", msgtype);
		/* advance through buffer */
		buf_index++;
		num_bytes--;
		continue;
	    }

	    msglen = (int) (sizeof(int) + strlen(&buf[buf_index + sizeof(int)]) +1);
	    if (res) {
		/*
		 * ok...advance to next message
		 */
		buf_index += msglen;
		num_bytes -= msglen;
	    } else if (msglen < num_bytes || (expecting && expecting == msglen)) {
		/*
		 * failed...
		 */

		/*
		 * this was a complete message...advance to the next one
		 */
		msglen = (int) (sizeof(int) + strlen(&buf[buf_index + sizeof(int)]) +1);
		buf_index += msglen;
		num_bytes -= msglen;
		expecting = 0;
	    }
	    else if (!OS_socket_ioctl(fd, FIONREAD, &unread_bytes) &&
		     unread_bytes > 0) {
		/*
		 * msglen == num_bytes could be a complete message... if
		 * there's unread data we'll assume it was truncated
		 */
		break;
	    } else {
		/*
		 * nothing more?  then discard message (it was the last one)
		 */
		buf_index = 0;
		num_bytes = 0;
		break;
	    }
	}

	/* keep track of leftover buffer contents */
	if (num_bytes && buf_index)
	    memmove(buf, &buf[buf_index], num_bytes);
	buf[num_bytes] = '\0';
	all_conns[conn_index].leftover = num_bytes;

	break;
    }
}