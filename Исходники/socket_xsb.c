static int socket_connect(CTXTdeclc int *rc, int timeout) {
  int error;
  socklen_t len;
  SOCKET sock_handle;
  int domain, portnum;
  SOCKADDR_IN socket_addr;
    
  domain = (int)ptoc_int(CTXTc 2);
  sock_handle = (SOCKET) ptoc_int(CTXTc 3);
  portnum = (int)ptoc_int(CTXTc 4);

  /** this may not set domain to a valid value; in this case the connect() will fail */
  translate_domain(domain, &domain);
    
  /*** prepare to connect ***/
  FillWithZeros(socket_addr);
  socket_addr.sin_port = htons((unsigned short)portnum);
  socket_addr.sin_family = AF_INET;
  socket_addr.sin_addr.s_addr =
    inet_addr((char*)get_host_IP(ptoc_string(CTXTc 5)));

     
  if (timeout > 0) {
    /* Set up timeout */
	  

    if(! SET_SOCKET_BLOCKING(sock_handle, block_false)) {
      xsb_error("Cannot save options");
      return TIMER_SETUP_ERR;
    }
	  
    /* This will return immediately */
    *rc = connect(sock_handle,(PSOCKADDR)&socket_addr,sizeof(socket_addr));
    error = XSB_SOCKET_ERRORCODE;

    /* restore flags */
    if(! SET_SOCKET_BLOCKING(sock_handle, block_true)) {
      xsb_error("Cannot restore the flags: %d (0x%x)", XSB_SOCKET_ERRORCODE, XSB_SOCKET_ERRORCODE);
      return TIMER_SETUP_ERR;
    }
	  
    /* return and indicate an error immediately unless the connection
     * was successful or the connect is still in progress. */
    if(*rc < 0 && error != EINPROGRESS && error != EWOULDBLOCK) {
      *rc = error;
      return NORMAL_TERMINATION; /* Since it didn't time out */
    }
	  
    /* Wait until the connect is completed (or a timeout occurs) */
    error = write_select(sock_handle, timeout);
	  
    if(error == 0) {
      closesocket(sock_handle);
      *rc = XSB_SOCKET_ERRORCODE;
      return TIMED_OUT;
    }
	  
    /* Get the return code from the connect */
    len=sizeof(error);
    error = GETSOCKOPT(sock_handle, SOL_SOCKET, SO_ERROR, &error, &len);
    if(error < 0) {
      xsb_error("GETSOCKOPT failed");
      *rc = error;
      return NORMAL_TERMINATION; /* Since it didn't time out */
    }
	  
    /* error=0 means success, otherwise it contains the errno */
    if(error) {
      *rc = error;
      return NORMAL_TERMINATION; /* Since it didn't time out */
    }
	  
    *rc = (int)sock_handle;
    return NORMAL_TERMINATION;
  } else {
    *rc = connect(sock_handle,(PSOCKADDR)&socket_addr,sizeof(socket_addr));
    return NORMAL_TERMINATION;
  }
}