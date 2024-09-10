int main(int argc, char **argv) {
  struct nfq_handle *h;
  struct nfq_q_handle *qh;
  struct nfnl_handle *nh;
  struct termios tio, old_tio;
  fd_set readfds;
  int fd;
  int rv;
  int ret;
  char buf[4096] __attribute__ ((aligned));
  int run = 1;
  
  // opening library handle
  h = nfq_open();
  if (!h) {
    fprintf(stderr, "error during nfq_open()\n");
    exit(1);
  }
  
  // unbinding existing nf_queue handler for AF_INET (if any)
  if (nfq_unbind_pf(h, AF_INET) < 0) {
    fprintf(stderr, "error during nfq_unbind_pf()\n");
    exit(1);
  }
  
  // binding nfnetlink_queue as nf_queue handler for AF_INET
  if (nfq_bind_pf(h, AF_INET) < 0) {
    fprintf(stderr, "error during nfq_bind_pf()\n");
    exit(1);
  }
  
  // binding this socket to queue '1'
  qh = nfq_create_queue(h,  1, &cb, NULL);
  if (!qh) {
    fprintf(stderr, "error during nfq_create_queue()\n");
    exit(1);
  }
  
  // setting copy_packet mode
  if (nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff) < 0) {
    fprintf(stderr, "can't set packet_copy mode\n");
    exit(1);
  }

  /* get the terminal settings for stdin */
  tcgetattr(STDIN_FILENO, &tio);
  old_tio = tio;
  
  /* disable canonical mode (buffered i/o) and local echo */
  tio.c_lflag &=(~ICANON & ~ECHO);
  
  /* set the new settings immediately */
  tcsetattr(STDIN_FILENO,TCSANOW,&tio);
  
  fd = nfq_fd(h);

  while(run) {
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    FD_SET(fd, &readfds);
  
    ret = select( fd + 1, &readfds, NULL, NULL, NULL);
    if(ret >= 0) {
      if(FD_ISSET(0, &readfds)) {
	int ch = fgetc(stdin);

	// q - quit
	if(ch == 'q') {
	  puts("quit");
	  run = 0;
	}
	
	// i - ignore request
	if((ch == 'i') && pending) {
	  puts("ignored");
	  free(pending);
	  pending = NULL;
	}
	
	// a - accept request
	if((ch == 'a') && pending) {
	  puts("accepted");
	  allowed = realloc(allowed, (allowed_len+1) * sizeof(device_t));
	  allowed[allowed_len++] = *pending;
	  free(pending);
	  pending = NULL;
	}

	// d - deny request
	if((ch == 'd') && pending) {
	  puts("denied");
	  denied = realloc(denied, (denied_len+1) * sizeof(device_t));
	  denied[denied_len++] = *pending;
	  free(pending);
	  pending = NULL;
	}
	
	// s - show
	if(ch == 's') {
	  puts("");
	  int d, i;

	  printf("Allowed:\n");
	  for(d=0;d<allowed_len;d++) {
	    for (i = 0; i < 5; i++)
	      printf("%02x:", allowed[d].hw_addr[i]);
	    printf("%02x\n", allowed[d].hw_addr[5]);
	  }
	  
	  printf("Denied:\n");
	  for(d=0;d<denied_len;d++) {
	    for (i = 0; i < 5; i++)
	      printf("%02x:", denied[d].hw_addr[i]);
	    printf("%02x\n", denied[d].hw_addr[5]);
	  }
	}
      }
      if(FD_ISSET(fd, &readfds)) {
	rv = recv(fd, buf, sizeof(buf), 0);
	nfq_handle_packet(h, buf, rv);
      }
    }
  }
      
  nfq_destroy_queue(qh);
  
  nfq_close(h);

  /* restore the former settings */
  tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
  
  exit(0);
}