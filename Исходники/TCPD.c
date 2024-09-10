/* Remove ACKed segment from send buffer */
TCP_buffer* removeFromSendBuffer (TCP_buffer* bufptr, int sock, struct sockaddr_in timer, int ackno){
  TCP_buffer* p = bufptr;
  TCP_buffer* prev = NULL; 
  struct timeval tim;
  double t1;
    
  /* TODO: Circular buffer */
  
  /* Search for corresponding segment using ACK no*/
  while (p != NULL && (p->ts.hdr.seq + p->len - TCP_HEADER_SIZE) != ackno){
    prev = p;
    /*
    printf("Traversing seq = %d len = %d\n",p->ts.hdr.seq, p->len);
    */
    p = p->next;
  }
  /* Segment found in buffer. Should always be true!*/
  if (p != NULL){
    if (p == bufptr)  bufptr = p->next;
    else  prev->next = p->next;
    p->next = NULL;
    printf("Removed ACKed segment seq = %d\n",p->ts.hdr.seq);
    /* Update M for RTO */
    
    if (p->txCount == 1){
      gettimeofday(&tim, NULL);
      t1 = tim.tv_sec + (tim.tv_usec/1000000.0);
      M = t1 - p->lastTxTime; 
    }
    /*
     * printf("Updating M.. lastTime = %.2f\n",p->lastTxTime);
    */
    /* Send remove request to timer */
    sendTimerRemoveRequest (sock, timer, &(p->ts));
    /* Update send window */
    
    updateWindow (&sendWindow, p->ts.hdr.seq, p->len - TCP_HEADER_SIZE);
    
    free (p);
    sBufCount--;
    if (sBufCount == 0) return NULL;
    /*
    if (bufptr == NULL) printf("Send buffer empty\n");
    */
  }
  /* Should never happen */
  else {
    printf("Segment not found in buffer for ACK = %d\n",ackno);
  }
  return bufptr;
}