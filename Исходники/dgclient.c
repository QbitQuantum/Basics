/* This routine does the first phase of the client-server Setup.
 * On successfule return, the out parameter sockfd will have the 
 * connection socket fd.
 * */
int connection_setup(int *sockfd, ifi_t *ifi_array[], int num_ifi,
    circ_buffer_t *rcv_buf, client_config_t *config)
{
  packet_t *send_pkt;
  int n, optval=1;
  char in_packet[PACKET_LEN],client_ip[IP_MAX];	
  struct sockaddr_in serv_addr, cliaddr, tempaddr;
  unsigned int ack_seq;
  unsigned short curr_win;
  bool is_error = FALSE;
  packet_info_t *rcv_pkt_info, *send_pkt_info = calloc(1, sizeof(packet_info_t));
  
  *sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

  if(server_on_same_subnet(config->server_ip,ifi_array, num_ifi, client_ip))
  {	
    printf("server on same subnet, SO_DONTROUTE set\n");
    //printf("client ip set to: %s\n",client_ip);
    setsockopt(*sockfd,SOL_SOCKET, SO_DONTROUTE, &optval, sizeof(optval));
  }	
  //update  cli_ip after if it's on the same host or n/w

  bzero(&cliaddr, sizeof(cliaddr));
  cliaddr.sin_family = AF_INET;
  cliaddr.sin_port = 0;
  inet_pton(AF_INET,client_ip,&cliaddr.sin_addr);
  Bind(*sockfd, (SA*) &cliaddr, sizeof(cliaddr));

  //cli addr and port using getsockname
  int cli_port;
  char cli_ip[IP_MAX];
  socklen_t len = sizeof(tempaddr);
  bzero(&tempaddr, sizeof(tempaddr));
  getsockname(*sockfd, (SA*) &tempaddr, &len);
  Inet_ntop(AF_INET, &tempaddr.sin_addr, cli_ip, IP_MAX);
  printf("[Info]client bound to ip:%s\n",cli_ip);
  cli_port = ntohs(tempaddr.sin_port);

  //connect
  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(config->server_port);
  Inet_pton(AF_INET, config->server_ip, &serv_addr.sin_addr);
  Connect(*sockfd, (SA *)&serv_addr, sizeof(serv_addr));

  assert(send_pkt_info);

  Signal(SIGALRM, sig_alarm);
  rtt_newpack(&rttinfo);          /* initialize for this packet */

  /* Prepare to send file name */
  send_pkt_info->seq = 0;
  send_pkt_info->ack = 0;
  send_pkt_info->window_size = config->window_size;
  SET_FILE_FLAG(send_pkt_info);
  send_pkt_info->data = strdup(config->file_name);
  send_pkt_info->data_len = strlen(config->file_name) + 1;

  printf("[Info] Sending file name %s to server ..\n", send_pkt_info->data);

sendagain:
  send_pkt_info->timestamp = rtt_ts(&rttinfo);
  send_pkt = build_packet(send_pkt_info);

  Write(*sockfd, (char *)send_pkt, send_pkt_info->data_len+HEADER_SIZE);

  /* set alarm for RTO seconds using setitimer */
  set_alarm(rtt_start(&rttinfo));
  if (sigsetjmp(jmpbuf, 1) != 0)
  {
    if (rtt_timeout(&rttinfo))
    {
      printf("[Error] Timed out Sending File Name, giving Up\n");
      free_pkt_info(send_pkt_info);
      free(send_pkt);
      errno = ETIMEDOUT;
      return -1;
    }
    printf("[Timeout] Retransmitting file name, next RTO:%d ms\n", rttinfo.rtt_rto);
    free(send_pkt);
    goto sendagain;
  }

  /* Now Attempt to read the Port message from the Server */
  while (1)
  {
    if ((n = read(*sockfd, in_packet, PACKET_LEN)) < 0)
    {
      if (errno == EINTR) 
        continue;
      else
        err_sys("[Error] Read Error while waiting for Port number");
    }

    rcv_pkt_info = get_packet_info(in_packet, n);

    if (consume_random_packet(rcv_pkt_info, config->prob_loss, TRUE))
    {
      free_pkt_info(rcv_pkt_info);
      continue;
    }

    if (IS_ACK(rcv_pkt_info) && (rcv_pkt_info->ack == (send_pkt_info->seq+1)))
    {
      break;
    }
    else
    {
      free_pkt_info(rcv_pkt_info);
      continue;
    }
  }

  set_alarm(0);     /* Turn off the Alarm */

  free_pkt_info(send_pkt_info);
  free(send_pkt);

  assert(rcv_pkt_info->data_len == sizeof(short));
  /* Fetch the new port from the server message */
  memcpy(&serv_addr.sin_port, rcv_pkt_info->data, sizeof(short));
  
  printf("[Info] Received new Port number %hu from Server.\n", ntohs(serv_addr.sin_port));

  /* Connect to the new port of the server child process */
  if (connect(*sockfd, (SA *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("[Error] Connect failure to server child: [%s : %hu]\n", config->server_ip, ntohs(serv_addr.sin_port));
    return -1;
  }

  printf("[Info] Connected to server's child process.\n");

  /* Advance the Circular buffer's read/write pointers to rcv_pkt_info->seq+1.
   * Basically, we are simulating the producer/consumer behavior here, in that we 
   * have written and read from the buffer.
   * Note: The server has to continue the file transfer starting from rcv_pkt_info->seq+1
   * as we will not accept anything lower than this sequence for this session
   * This is similar to the SYN+ACK in TCP
   */
  rcv_buf->next_read_seq = rcv_buf->next_contig_write_seq = rcv_pkt_info->seq+1;
  printf("rcv_buf->next_read_seq = rcv_buf->next_contig_write_seq = %u", rcv_pkt_info->seq+1);

  curr_win = window_size(rcv_buf); 
  ack_seq = NEXT_ACK(rcv_buf); 

  /* Exit if the file does not exist on the server after sending ACK.
   * In the event this ACK is lost, the server ichild timeout mechanism will kick in
   * and eventually it will timeout and give up
   */
  if(is_error = IS_ERR(rcv_pkt_info))
  {
    printf("[Info] Received Error message from server [Seq: %u] Responding with [Ack:%u] [Window Size:%hu]\n", 
        rcv_pkt_info->seq, ack_seq, curr_win);
  }
  else
  {
    printf("[Info] Received Port message [Seq: %u] Responding with [Ack:%u] [Window Size:%hu]\n", 
        rcv_pkt_info->seq, ack_seq, curr_win);
  }

  /* Simulate Loss On Tx */
  if (!consume_random_packet(rcv_pkt_info, config->prob_loss, FALSE))
  {
    send_ack(*sockfd, curr_win, rcv_pkt_info->seq, ack_seq, rcv_pkt_info->timestamp, config->prob_loss);
  }

  free_pkt_info(rcv_pkt_info);
  
  if(is_error)
  {
      printf("[Error] File %s does not exist, terminating..\n", config->file_name);
      errno = EBADF;
      return -1;
  }
  
  printf("[Info] Successful Connection Setup with [%s:%u], ready for file reception\n", 
      config->server_ip, ntohs(serv_addr.sin_port));
  return 0;

}