int handlehost(struct HTTPConnection * p)
{
  int dispatchfd,hssum,hrsum,sendnum;
  struct epoll_event reqev;
  struct ProxyConnection * proxy;
  struct DispatchConnection * dispatch;
  char * readBuf;
  proxy = (struct ProxyConnection *)p;
  int parseResult, proxyclosed;
  char requestbuf[1024];
  if(proxy == NULL){
    logwarn("invalid handle pointer.\n");
    return -1;
  }
  /*
    check the proxy buffer, allocate if buffer is NULL.

  */
  if(proxy->con.buf == NULL){
    proxy->con.buf = initHTTPBuffer(4096*4);
    if(proxy->con.buf == NULL){
      logerr("allocate for proxy buffer.\n");
      return -1;
    }
  }
  if(proxy->con.events & EPOLLIN){
    proxyclosed = 0;
    proxy->con.events &= ~EPOLLIN;
    readBuf = proxy->con.buf->rdBuf + proxy->con.buf->bufferedBytes;
    hrsum = recvfromhost(proxy->con.fd, readBuf, &proxyclosed);
    if(hrsum > 0){
      printf("recv %d bytes from host.\n", hrsum);
      proxy->con.buf->bufferedBytes += hrsum;
      if(proxy->header.parsePass != 1){
	parseResult = parseRequest(proxy->con.buf->rdBuf, &(proxy->header));
	printf("request's host is %s.\n", proxy->header.host);
	if(parseResult == 0){
	  printf("http header length is %d.\n", proxy->header.length);
	  printf("http uri is %s.\n", proxy->header.uri);
	}
      }
      if(proxy->dispatch == NULL){
	if(proxy->header.host[0] != '\0'){
	  if((dispatch = FindDispatchConnect(dispatchlist, proxy->header.host, PROXY_FINISHED)) != NULL){
	    /*
	      The dispatch connection to the specified host already existed.
	    */

	    printf("host %s connection already existed.\n", proxy->header.host);
	    attachProxyDispatch(proxy, dispatch);
	    dispatch->status = PROXY_USED;
	  }
	  else{
	    dispatchfd = NULLFD;
	    if(connecthost(proxy->header.host, proxy->header.port, &dispatchfd) == -1){
	      if(dispatchfd != NULLFD){
		close(dispatchfd);
		rmfromepoll(epfd, proxy->con.fd);
		freeProxyConnect(proxy);
	      }
	      return -1;
	    }
	    printf("connect success.\n");
	    setnonblock(dispatchfd);
	    if(addtoepoll(epfd, dispatchfd, ETINOUT) !=0 ){
	      logerr("add remote fd to epoll error", errno);
	      return -1;
	    }
	    List * pl;
	    struct DispatchConnection * dispatchcon;
	    pl = getDispatchResource(&freeDispatchlist, dispatchfd, handleremote);
	    dispatchcon = (struct DispatchConnection *)(pl->item);
	    AddConnectToManager(dispatchfd, dispatchcon);
	    addToList(&dispatchlist, pl);
	    strcpy(dispatchcon->host, proxy->header.host);
	    attachProxyDispatch(proxy, dispatchcon);
	  }
	}
      }
      if(proxy->header.parsePass == 1 && proxy->con.buf->bufferedBytes >= proxy->header.length){
	notifyProxyRequest(proxy);
      }
    }
    if(proxyclosed == 1){
      /*
	avoid web browser open a connection, but send no data and close after.

      */

      if(proxy->con.buf->bufferedBytes == 0) proxy->status = PROXY_FREE; 
      else if(proxy->status == PROXY_USED) proxy->status = PROXY_CLOSED;
      else if(proxy->status == PROXY_FINISHED) proxy->status = PROXY_FREE;
    }
  }
  if(proxy->con.events & EPOLLOUT){
    dispatch = proxy->dispatch;
    if(proxy->con.buf != NULL && proxy->con.buf->wrBuf != NULL){
      /*
	when the dispatch response is recived and the socket is ready for write,
	proxy sends the response to host.

      */

      sendnum = proxy->con.buf->outBytes;
      if(proxy->con.buf->wrReady == 1 && sendnum > 0){
	proxyclosed = 0;
	hssum = sendtohost(proxy->con.fd, proxy->con.buf->wrBuf, sendnum, &proxyclosed);
	if(hssum == sendnum){
	  printf("send %d bytes to host.\n", hssum);
	  sprintf(requestbuf, "%d %s %s %s.\n", dispatch->header.status, proxy->header.method, proxy->header.uri, proxy->header.version);
	  loginfo(requestbuf);
	  notifyProxyFinished(proxy);
	  cleanDispatchResponse(dispatch);
	}
	else{
	  if(proxyclosed == 1){
	    notifyProxyFinished(proxy);
	    detachProxyDispatch(proxy, dispatch);
	  }
	  else{
	    proxy->con.events &= ~EPOLLOUT;
	    printf("send error and bytes %d.\n", hssum);
	  }
	}
      }
    }
  }
  if(proxy->status == PROXY_FREE){
    /*
      when the host close the connection and proxy send the response to host,
      the proxy could also close the connection to free the socket.

    */
    
    rmfromepoll(epfd, proxy->con.fd);
    freeProxyConnect(proxy);
    freeResource(&proxylist, &freeProxylist, (ListItem *)proxy);
  }
  return 0;
}