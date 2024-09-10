/*	Write to the socket
**
** According to Solaris 2.3 man on write:
**
**    o	If O_NONBLOCK and O_NDELAY are clear, write() blocks
**	until the data can be accepted.
**
**    o	If O_NONBLOCK or O_NDELAY is set, write()  does  not
**	block  the  process.   If  some  data  can be written
**	without blocking the process, write() writes what  it
**	can  and returns the number of bytes written.  Other-
**	wise, if O_NONBLOCK is set, it returns - 1  and  sets
**	errno to EAGAIN or if O_NDELAY is set, it returns 0.
**
** According to SunOS 4.1.1 man on write:
**
**   +	If the descriptor is  marked  for  non-blocking  I/O
**	using  fcntl()  to  set  the FNONBLOCK or O_NONBLOCK
**	flag (defined in  <sys/fcntl.h>),  write()  requests
**	for  {PIPE_BUF}  (see  pathconf(2V))  or fewer bytes
**	either  succeed  completely  and  return  nbyte,  or
**	return -1 and set errno to EAGAIN. A write() request
**	for greater than {PIPE_BUF} bytes  either  transfers
**	what it can and returns the number of bytes written,
**	or transfers no data and returns -1 and  sets  errno
**	to  EAGAIN.  If  a  write()  request is greater than
**	{PIPE_BUF} bytes and all data previously written  to
**	the  pipe  has been read, write() transfers at least
**	{PIPE_BUF} bytes.
*/
PRIVATE int HTWriter_write (HTOutputStream * me, const char * buf, int len)
{
    HTHost * host = me->host;
    SOCKET soc = HTChannel_socket(HTHost_channel(host));
    HTNet * net = HTHost_getWriteNet(host);
    int b_write;
    char * wrtp;
    const char *limit = buf+len;

    /* If we don't have a Net object then return right away */
    if (!net) {
        HTTRACE(STREAM_TRACE, "Write Socket No Net object %d (offset %d)\n" _ soc _ me->offset);
        return HT_ERROR;
    }

#ifdef NOT_ASCII
    if (len && !me->ascbuf) {			      /* Generate new buffer */
        const char *orig = buf;
        char *dest;
        int cnt;
        if ((me->ascbuf = (char  *) HT_MALLOC(len)) == NULL)
            HT_OUTOFMEM("HTWriter_write");
        dest = me->ascbuf;
        for (cnt=0; cnt<len; cnt++) {
            *dest = TOASCII(*orig);
            dest++, orig++;
        }
        wrtp = me->ascbuf;
        limit = me->ascbuf+len;
    }
#else
    if (!me->offset)
        wrtp = (char *) buf;
    else {
        wrtp = (char *) buf + me->offset;
        len -= me->offset;
        me->offset = 0;
    }
#endif

    /* Write data to the network */
    while (wrtp < limit) {
        if ((b_write = NETWRITE(soc, wrtp, len)) < 0) {
#ifdef EAGAIN
            if (socerrno == EAGAIN || socerrno == EWOULDBLOCK)/* POSIX, SVR4 */
#else
            if (socerrno == EWOULDBLOCK)			      /* BSD */
#endif
            {
                HTHost_register(host, net, HTEvent_WRITE);
                me->offset = wrtp - buf;
                HTTRACE(STREAM_TRACE, "Write Socket WOULD BLOCK %d (offset %d)\n" _ soc _ me->offset);
                return HT_WOULD_BLOCK;
#ifdef EINTR
            } else if (socerrno == EINTR) {
                /*
                **	EINTR	A signal was caught during the  write  opera-
                **		tion and no data was transferred.
                */
                HTTRACE(STREAM_TRACE, "Write Socket call interrupted - try again\n");
                continue;
#endif
            } else {
                host->broken_pipe = YES;
#ifdef EPIPE
                if (socerrno == EPIPE) {
                    /* JK: an experimental bug solution proposed by
                               Olga and Mikhael */
                    HTTRACE(STREAM_TRACE, "Write Socket got EPIPE\n");
                    HTHost_unregister(host, net, HTEvent_WRITE);
                    HTHost_register(host, net, HTEvent_CLOSE);
                    /* @@ JK: seems that some functions check the errors
                       as part of the flow control */
                    HTRequest_addSystemError(net->request, ERR_FATAL, socerrno, NO,
                                             "NETWRITE");
                    return HT_CLOSED;
                }
#endif /* EPIPE */
                /* all errors that aren't EPIPE */
                HTRequest_addSystemError(net->request, ERR_FATAL, socerrno, NO,
                                         "NETWRITE");
                return HT_ERROR;
            }
        }

        /* We do this unconditionally, should we check to see if we ever blocked? */
        HTTRACEDATA(wrtp, b_write, "Writing to socket %d" _ soc);
        HTNet_addBytesWritten(net, b_write);
        wrtp += b_write;
        len -= b_write;
        HTTRACE(STREAM_TRACE, "Write Socket %d bytes written to %d\n" _ b_write _ soc);
        {
            HTAlertCallback *cbf = HTAlert_find(HT_PROG_WRITE);
            if (cbf) {
                int tw = HTNet_bytesWritten(net);
                (*cbf)(net->request, HT_PROG_WRITE,
                       HT_MSG_NULL, NULL, &tw, NULL);
            }
        }
    }
#ifdef NOT_ASCII
    HT_FREE(me->ascbuf);
#endif
    return HT_OK;
}