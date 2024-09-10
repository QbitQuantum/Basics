void
create_listens(char hostname[], char port[], int af) {

  struct addrinfo hints;
  struct addrinfo *local_res;
  struct addrinfo *local_res_temp;
  int count, error;
  int on = 1;
  SOCKET temp_socket;
  struct listen_elt *temp_elt;

  if (debug) {
    fprintf(stderr,
	    "%s: called with host '%s' port '%s' family %s(%d)\n",
	    __FUNCTION__,
            hostname,
	    port,
	    inet_ftos(af),
            af);
    fflush(stderr);
  }
 memset(&hints,0,sizeof(hints));
  hints.ai_family = af;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;

  count = 0;
  do {
    error = getaddrinfo((char *)hostname,
                        (char *)port,
                        &hints,
                        &local_res);
    count += 1;
    if (error == EAI_AGAIN) {
      if (debug) {
        fprintf(stderr,
		"%s: Sleeping on getaddrinfo EAI_AGAIN\n",
		__FUNCTION__);
        fflush(stderr);
      }
      sleep(1);
    }
  } while ((error == EAI_AGAIN) && (count <= 5));

  if (error) {
    if (debug) {
      
      fprintf(stderr,
	      "%s: could not resolve remote '%s' port '%s' af %d\n"
	      "\tgetaddrinfo returned %s (%d)\n",
	      __FUNCTION__,
	      hostname,
	      port,
	      af,
	      gai_strerror(error),
	      error);
      
    }
    return;
  }

  if (debug) {
    dump_addrinfo(stderr, local_res, hostname, port, af);
  }

  local_res_temp = local_res;

  while (local_res_temp != NULL) {

    temp_socket = socket(local_res_temp->ai_family,SOCK_STREAM,0);

    if (temp_socket == INVALID_SOCKET) {
      if (debug) {
	fprintf(stderr,
		"%s could not allocate a socket: %s (errno %d)\n",
		__FUNCTION__,
		strerror(errno),
		errno);
	fflush(stderr);
      }
      local_res_temp = local_res_temp->ai_next;
      continue;
    }

    /* happiness and joy, keep going */
    if (setsockopt(temp_socket,
		   SOL_SOCKET, 
		   SO_REUSEADDR, 
		   (char *)&on , 
		   sizeof(on)) == SOCKET_ERROR) {
      if (debug) {
	fprintf(stderr,
		"%s: warning: could not set SO_REUSEADDR: %s (errno %d)\n",
		__FUNCTION__,
		strerror(errno),
		errno);
	fflush(stderr);
      }
    }
    /* still happy and joyful */

    if ((bind(temp_socket,
	      local_res_temp->ai_addr, 
	      local_res_temp->ai_addrlen) != SOCKET_ERROR) &&
	(listen(temp_socket,128) != SOCKET_ERROR))  {

      /* OK, now add to the list */
      temp_elt = (struct listen_elt *)malloc(sizeof(struct listen_elt));
      if (temp_elt) {
	temp_elt->fd = temp_socket;
	if (listen_list) {
	  temp_elt->next = listen_list;
	}
	else {
	  temp_elt->next = NULL;
	}
	listen_list = temp_elt;
      }
      else {
	fprintf(stderr,
		"%s: could not malloc a listen_elt\n",
		__FUNCTION__);
	fflush(stderr);
	exit(1);
      }
    }
    else {
      /* we consider a bind() or listen() failure a transient and try
	 the next address */
      if (debug) {
	fprintf(stderr,
		"%s: warning: bind or listen call failure: %s (errno %d)\n",
		__FUNCTION__,
		strerror(errno),
		errno);
	fflush(stderr);
      }
      close(temp_socket);
    }
    local_res_temp = local_res_temp->ai_next;
  }

}