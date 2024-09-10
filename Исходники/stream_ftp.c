/*
 * read a line of text
 *
 * return -1 on error or bytecount
 */
static int readline(char *buf,int max,struct stream_priv_s *ctl)
{
    int x,retval = 0;
    char *end,*bp=buf;
    int eof = 0;

    do {
      if (ctl->cavail > 0) {
	x = (max >= ctl->cavail) ? ctl->cavail : max-1;
	end = memccpy(bp,ctl->cget,'\n',x);
	if (end != NULL)
	  x = end - bp;
	retval += x;
	bp += x;
	*bp = '\0';
	max -= x;
	ctl->cget += x;
	ctl->cavail -= x;
	if (end != NULL) {
	  bp -= 2;
	  if (strcmp(bp,"\r\n") == 0) {
	    *bp++ = '\n';
	    *bp++ = '\0';
	    --retval;
	  }
	  break;
	}
      }
      if (max == 1) {
	*buf = '\0';
	break;
      }
      if (ctl->cput == ctl->cget) {
	ctl->cput = ctl->cget = ctl->buf;
	ctl->cavail = 0;
	ctl->cleft = BUFSIZE;
      }
      if(eof) {
	if (retval == 0)
	  retval = -1;
	break;
      }

      if(!fd_can_read(ctl->handle, 15)) {
        mp_msg(MSGT_OPEN,MSGL_ERR, "[ftp] read timed out\n");
        retval = -1;
        break;
      }

      if ((x = recv(ctl->handle,ctl->cput,ctl->cleft,0)) == -1) {
	mp_msg(MSGT_STREAM,MSGL_ERR, "[ftp] read error: %s\n",strerror(errno));
	retval = -1;
	break;
      }
      if (x == 0)
	eof = 1;
      ctl->cleft -= x;
      ctl->cavail += x;
      ctl->cput += x;
    } while (1);

    return retval;
}