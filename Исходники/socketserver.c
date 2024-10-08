/************************************************************************
 * This function deals with the incoming client requests in a loop until
 * the user requests to stop the server, or until the remote side closes
 * the connection. The implementation follows the idea of a state machine
 * with the four different states:
 *   state = 0 means we are waiting for a request to come in, or we are
 *             in the process of reading the first 8 bytes (the "def" part)
 *   state = 1 means we are in the process of reading the remainder of
 *             the request (the "buf" part")
 *   state = 2 means we are in the process of writing the response (def)
 *   state = 3 means ... writing the 2nd. part of the response ("buf")
 *
 * On top of those 4 states, we maintain two variables "bytesDone" and
 * "bytesTotal" that determine how many bytes we've read/written within
 * the current state, and how many bytes we need to process in total,
 * and a variable "curPtr" which points to the memory region we currently
 * need to read into, or write from. Whether any action is actually taken
 * inside the while loop also depends on the state of the socket which
 * we find out using "select" (and then set "canRead" + "canWrite" flags).
 *
 * Depending on the nature of the request, we might skip states 1 and 3.
 * This is the case if there is no "buf" attached to the message, or if
 * an outgoing message can be merged in to a single packet.
 * 
 * The actual processing of the message happens before moving to state 2
 * and consists of 
 *   1) possibly swapping the message to native endianness
 *   2) calling dmarequest or the user-supplied callback function
 *   3) possibly swapping back to remote endianness
 ************************************************************************/
void *_buffer_socket_func(void *arg) {
	SOCKET sock;
	ft_buffer_server_t *SC;
	int mergePackets;
	messagedef_t reqdef;
	message_t request;
	message_t *response = NULL;
	int state=0; /* 0 = reading def, 1=reading buf, 2=writing def, 3=writing buf */
	int bytesDone, bytesTotal;
	char mergeBuffer[MERGE_THRESHOLD];
	char *curPtr;	/* points at buffer that needs to be filled or written out */
	int swap = 0;	
	int canRead, canWrite;
	UINT16_T reqCommand;
	UINT32_T respBufSize;
	fd_set readSet, writeSet;

	if (arg==NULL) return NULL;
		
	/* copy over necessary variables and free the given structure */
	SC 			 = ((ft_buffer_socket_t *) arg)->server;
	sock 		 = ((ft_buffer_socket_t *) arg)->clientSocket;
	mergePackets = ((ft_buffer_socket_t *) arg)->mergePackets;
	free(arg);
	
	if (SC->verbosity > 0) {
		printf("Started new client thread with packet merging = %i\n", mergePackets);
	}
	
    pthread_mutex_lock(&SC->lock);
    SC->numClients++;
    pthread_mutex_unlock(&SC->lock);

	request.def = &reqdef;
	request.buf = NULL;
	bytesDone = 0;
	bytesTotal = sizeof(messagedef_t);
	curPtr = (char *) request.def;

	while (SC->keepRunning) {
		int sel, res, n;
		struct timeval tv = {0, 10000}; /* 10ms */
	
		FD_ZERO(&readSet);
		FD_ZERO(&writeSet);
		if (state < 2) {
			FD_SET(sock, &readSet);
		} else {
			FD_SET(sock, &writeSet);
		}
		sel = select((int) sock+1, &readSet, &writeSet, NULL, &tv);
		if (sel == 0) continue;
		if (sel < 0) {
			fprintf(stderr, "Error in 'select' operation - closing client connection.\n");
			break;
		}
		canRead = FD_ISSET(sock, &readSet);
		canWrite = FD_ISSET(sock, &writeSet);
		
		if (canRead) {
			n = recv(sock, curPtr + bytesDone, bytesTotal - bytesDone, 0);
			if (n<=0) {
				/* socket was closed */
				if (SC->verbosity>0) {
					printf("Remote side closed client connection\n");
				}
				break;
			}
			bytesDone+=n;
			if (bytesDone<bytesTotal) continue;
			
			if (state == 0) {
				/* we've read the request.def completely */
				if (reqdef.version==VERSION_OE) {
					swap = 1;
					ft_swap16(2, &reqdef.version); /* version + command */
					ft_swap32(1, &reqdef.bufsize);
					reqCommand = reqdef.command;		
				}
				if (reqdef.version!=VERSION) {
					fprintf(stderr,"Incorrect version requested - closing socket.\n");
					break;
				}
				if (reqdef.bufsize > 0) {
					request.buf = malloc(reqdef.bufsize);
					if (request.buf == NULL) {
						fprintf(stderr, "Out of memory\n");
						break;
					}
					curPtr = request.buf;
					bytesDone = 0;
					bytesTotal = reqdef.bufsize;
					state = 1;
					continue;
				} 
			} else {
				/* Reaching this point means that the state=1, and that we've 
				   read request.buf completely, so swap the endianness if 
				   necessary, and then move on to handling the request.
				*/	
				if (swap) ft_swap_buf_to_native(reqCommand, reqdef.bufsize, request.buf);
			}
			
			/* Request has been read completely, now deal with it */
			if (SC->callback != NULL) {
				/* User supplied a callback function in ft_start_buffer_server */
				res = SC->callback(&request, &response, SC->user_data);
				if (res != 0 || response == NULL || response->def == NULL) {
					fprintf(stderr, "buffer_socket_func: an unexpected error occurred in user-defined request handler\n");
					break;
				}
			} else {
				/* No callback, use normal dmarequest */
				res = dmarequest(&request, &response);
				if (res != 0 || response == NULL || response->def == NULL) {
					fprintf(stderr, "buffer_socket_func: an unexpected error occurred in dmarequest\n");
					break;
				}
			}
			
			/* Ok, the request has been handled, results are in response.
			   We can free the memory pointed to by request.buf ...
			*/
			if (request.buf != NULL) {
				free(request.buf);
				request.buf = NULL;
			}
			
			/* ... swap the response to the remote endianness, if necessary ... */
			respBufSize = response->def->bufsize;
			if (swap) ft_swap_from_native(reqCommand, response);
		
			/* ... and then start writing back the response. To reduce latency,
			   we try to merge response->def and response->buf if they are small, 
			   so we can send it in one go over TCP. To fit the merged packet into 
			   our state machine logic, we apply a trick and jump to state=3 directly,
			   where "curPtr" points to the merged packet.
			   Otherwise, we move to state=2, transmit response->def, move to state=3,
			   and there transmit response->buf.
			*/
			if (mergePackets && respBufSize > 0 && respBufSize + sizeof(messagedef_t) <= MERGE_THRESHOLD) {
				memcpy(mergeBuffer, response->def, sizeof(messagedef_t));
				memcpy(mergeBuffer + sizeof(messagedef_t), response->buf, respBufSize);
				
				curPtr = mergeBuffer;
				bytesDone = 0;
				bytesTotal = respBufSize + sizeof(messagedef_t);
				state = 3;
			} else {
				curPtr = (char *) response->def;
				bytesDone = 0;
				bytesTotal = sizeof(messagedef_t);
				state = 2;
			}
			canWrite = 1;
		}
		
		if (state >= 2 && canWrite) {
			n = send(sock, curPtr + bytesDone, bytesTotal - bytesDone, 0);
			if (n<=0) {
				/* socket was closed */
				fprintf(stderr, "Cannot write to socket -- closing client connection.\n");
				break;
			}
			bytesDone+=n;
			if (bytesDone < bytesTotal) continue;
			if (state==2 && respBufSize > 0) {
				curPtr = (char *) response->buf;
				bytesDone = 0;
				bytesTotal = respBufSize;
				state = 3;
				continue;
			}
			/* Reaching this point means we are done with writing out the response,
			   so we will now free the allocated memory, and reset to state=0.
			*/
			if (response->buf) free(response->buf);
			free(response->def);
			free(response);
			response = NULL;
			state = 0;
			curPtr = (char *) request.def;
			bytesDone = 0;
			bytesTotal = sizeof(messagedef_t);
		}
	}
	
    pthread_mutex_lock(&SC->lock);
    SC->numClients--;
    pthread_mutex_unlock(&SC->lock);
	
	closesocket(sock);
	if (request.buf!=NULL) free(request.buf);
    if (response!=NULL) {
		if (response->buf!=NULL) free(response->buf);
		if (response->def!=NULL) free(response->def);
		free(response);
	}
	
	return NULL;
}