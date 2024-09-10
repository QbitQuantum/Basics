int32
yahoo_io_thread( void * _data )
{
	YahooConnection * conn = (YahooConnection*)_data;
	
/*	conn->fID = yahoo_init_with_attributes(
		conn->fYahooID, conn->fPassword,
		//"local_host", local_host,
		"pager_port", 23,
		NULL
	);
*/	
	conn->fID = yahoo_init(
		conn->fYahooID, conn->fPassword
	);
	
	LOG(kProtocolName, liDebug, "yahoo_io_thread: id: %s, pass: %s", conn->fYahooID, conn->fPassword );
	
	gYahooConnections[conn->fID] = conn;
	
	yahoo_login( conn->fID, YAHOO_STATUS_AVAILABLE );

	int lfd=0;
	
	fd_set inp, outp;
	struct timeval tv;
	
	LOG(kProtocolName, liDebug, "yahoo_io_thread: Starting loop");
	
	while( conn->IsAlive() ) {
		FD_ZERO(&inp);
		FD_ZERO(&outp);
		tv.tv_sec=1;
		tv.tv_usec=0;
		lfd=0;
		
		for(int i=0; i<conn->CountConnections(); i++) {
			struct fd_conn *c = conn->ConnectionAt(i);
			
			if(c->remove) {
//				LOG(kProtocolName, liDebug, "yahoo_io_thread: Removing id:%d fd:%d", c->id, c->fd);
				conn->RemoveConnection(c);
				free(c);
			} else {
				if(c->cond & YAHOO_INPUT_READ) {
					FD_SET(c->fd, &inp);
				}
				if(c->cond & YAHOO_INPUT_WRITE) {
					FD_SET(c->fd, &outp);
				}
				if(lfd < c->fd)
					lfd = c->fd;
			}
		}
		
		select(lfd + 1, &inp, &outp, NULL, &tv);
		time(&curTime);
		
		for(int i=0; i<conn->CountConnections(); i++) {
			struct fd_conn *c = conn->ConnectionAt(i);
			if(c->remove)
				continue;
			if(FD_ISSET(c->fd, &inp)) {
//				LOG(kProtocolName, liDebug, "yahoo_io_thread: data to read");
				yahoo_callback(c, YAHOO_INPUT_READ);
				FD_CLR(c->fd, &inp);
			}
			if(FD_ISSET(c->fd, &outp)) {
				//LOG(kProtocolName, liDebug, "yahoo_io_thread: data to write");
				yahoo_callback(c, YAHOO_INPUT_WRITE);
				FD_CLR(c->fd, &outp);
			}
		}
		
		if(expired(pingTimer))
			yahoo_ping_timeout_callback(conn->fID, pingTimer);
	}
	LOG(kProtocolName, liDebug, "yahoo_io_thread: Exited loop");
	
	while( conn->CountConnections() > 0 ) {
		struct fd_conn * c = conn->ConnectionAt(0);
		conn->RemoveConnection(c);
		close(c->fd);
		FREE(c);
	}
	
	return 0;
}