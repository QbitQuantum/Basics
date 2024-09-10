/* Callback function executed when something is received on fd */
int receive_callback(int file, void *arg) {
  char buf[sizeof(struct rudp_packet)];
  struct sockaddr_in sender;
  size_t sender_length = sizeof(struct sockaddr_in);
  recvfrom(file, &buf, sizeof(struct rudp_packet), 0, (struct sockaddr *)&sender, &sender_length);

  struct rudp_packet *received_packet = malloc(sizeof(struct rudp_packet));
  if(received_packet == NULL) {
    fprintf(stderr, "receive_callback: Error allocating packet\n");
    return -1;
  }
  memcpy(received_packet, &buf, sizeof(struct rudp_packet));
  
  struct rudp_hdr rudpheader = received_packet->header;
  char type[5];
  short t = rudpheader.type;
  if(t == 1)
    strcpy(type, "DATA");
  else if(t == 2)
    strcpy(type, "ACK");
  else if(t == 4)
    strcpy(type, "SYN");
  else if(t==5)
    strcpy(type, "FIN");
  else
    strcpy(type, "BAD");

  printf("Received %s packet from %s:%d seq number=%u on socket=%d\n",type, 
       inet_ntoa(sender.sin_addr), ntohs(sender.sin_port),rudpheader.seqno,file);

  /* Locate the correct socket in the socket list */
  if(socket_list_head == NULL) {
    fprintf(stderr, "Error: attempt to receive on invalid socket. No sockets in the list\n");
    return -1;
  }
  else {
    /* We have sockets to check */
    struct rudp_socket_list *curr_socket = socket_list_head;
    while(curr_socket != NULL) {
      if((int)curr_socket->rsock == file) {
        break;
      }
      curr_socket = curr_socket->next;
    }
    if((int)curr_socket->rsock == file) {
      /* We found the correct socket, now see if a session already exists for this peer */
      if(curr_socket->sessions_list_head == NULL) {
        /* The list is empty, so we check if the sender has initiated the protocol properly (by sending a SYN) */
        if(rudpheader.type == RUDP_SYN) {
          /* SYN Received. Create a new session at the head of the list */
          u_int32_t seqno = rudpheader.seqno + 1;
          create_receiver_session(curr_socket, seqno, &sender);
          /* Respond with an ACK */
          struct rudp_packet *p = create_rudp_packet(RUDP_ACK, seqno, 0, NULL);
          send_packet(true, (rudp_socket_t)file, p, &sender);
          free(p);
        }
        else {
          /* No sessions exist and we got a non-SYN, so ignore it */
        }
      }
      else {
        /* Some sessions exist to be checked */
        bool_t session_found = false;
        struct session *curr_session = curr_socket->sessions_list_head;
        struct session *last_session;
        while(curr_session != NULL) {
          if(curr_session->next == NULL) {
            last_session = curr_session;
          }
          if(compare_sockaddr(&curr_session->address, &sender) == 1) {
            /* Found an existing session */
            session_found = true;
            break;
          }

          curr_session = curr_session->next;
        }
        if(session_found == false) {
          /* No session was found for this peer */
          if(rudpheader.type == RUDP_SYN) {
            /* SYN Received. Send an ACK and create a new session */
            u_int32_t seqno = rudpheader.seqno + 1;
            create_receiver_session(curr_socket, seqno, &sender);          
            struct rudp_packet *p = create_rudp_packet(RUDP_ACK, seqno, 0, NULL);
            send_packet(true, (rudp_socket_t)file, p, &sender);
            free(p);
          }
          else {
            /* Session does not exist and non-SYN received - ignore it */
          }
        }
        else {
          /* We found a matching session */ 
          if(rudpheader.type == RUDP_SYN) {
            if(curr_session->receiver == NULL || curr_session->receiver->status == OPENING) {
              /* Create a new receiver session and ACK the SYN*/
              struct receiver_session *new_receiver_session = malloc(sizeof(struct receiver_session));
              if(new_receiver_session == NULL) {
                fprintf(stderr, "receive_callback: Error allocating receiver session\n");
                return -1;
              }
              new_receiver_session->expected_seqno = rudpheader.seqno + 1;
              new_receiver_session->status = OPENING;
              new_receiver_session->session_finished = false;
              curr_session->receiver = new_receiver_session;

              u_int32_t seqno = curr_session->receiver->expected_seqno;
              struct rudp_packet *p = create_rudp_packet(RUDP_ACK, seqno, 0, NULL);
              send_packet(true, (rudp_socket_t)file, p, &sender);
              free(p);
            }
            else {
              /* Received a SYN when there is already an active receiver session, so we ignore it */
            }
          }
          if(rudpheader.type == RUDP_ACK) {
            u_int32_t ack_sqn = received_packet->header.seqno;
            if(curr_session->sender->status == SYN_SENT) {
              /* This an ACK for a SYN */
              u_int32_t syn_sqn = curr_session->sender->seqno;
              if( (ack_sqn - 1) == syn_sqn) {
                /* Delete the retransmission timeout */
                event_timeout_delete(timeout_callback, curr_session->sender->syn_timeout_arg);
                struct timeoutargs *t = (struct timeoutargs *)curr_session->sender->syn_timeout_arg;
                free(t->packet);
                free(t->recipient);
                free(t);
                curr_session->sender->status = OPEN;
                while(curr_session->sender->data_queue != NULL) {
                  /* Check if the window is already full */
                  if(curr_session->sender->sliding_window[RUDP_WINDOW-1] != NULL) {
                    break;
                  }
                  else {
                    int index;
                    int i;
                    /* Find the first unused window slot */
                    for(i = RUDP_WINDOW-1; i >= 0; i--) {
                      if(curr_session->sender->sliding_window[i] == NULL) {
                        index = i;
                      }
                    }
                    /* Send packet, add to window and remove from queue */
                    u_int32_t seqno = ++syn_sqn;
                    int len = curr_session->sender->data_queue->len;
                    char *payload = curr_session->sender->data_queue->item;
                    struct rudp_packet *datap = create_rudp_packet(RUDP_DATA, seqno, len, payload);
                    curr_session->sender->seqno += 1;
                    curr_session->sender->sliding_window[index] = datap;
                    curr_session->sender->retransmission_attempts[index] = 0;
                    struct data *temp = curr_session->sender->data_queue;
                    curr_session->sender->data_queue = curr_session->sender->data_queue->next;
                    free(temp->item);
                    free(temp);

                    send_packet(false, (rudp_socket_t)file, datap, &sender);
                  }
                }
              }
            }
            else if(curr_session->sender->status == OPEN) {
              /* This is an ACK for DATA */
              if(curr_session->sender->sliding_window[0] != NULL) {
                if(curr_session->sender->sliding_window[0]->header.seqno == (rudpheader.seqno-1)) {
                  /* Correct ACK received. Remove the first window item and shift the rest left */
                  event_timeout_delete(timeout_callback, curr_session->sender->data_timeout_arg[0]);
                  struct timeoutargs *args = (struct timeoutargs *)curr_session->sender->data_timeout_arg[0];
                  free(args->packet);
                  free(args->recipient);
                  free(args);
                  free(curr_session->sender->sliding_window[0]);

                  int i;
                  if(RUDP_WINDOW == 1) {
                    curr_session->sender->sliding_window[0] = NULL;
                    curr_session->sender->retransmission_attempts[0] = 0;
                    curr_session->sender->data_timeout_arg[0] = NULL;
                  }
                  else {
                    for(i = 0; i < RUDP_WINDOW - 1; i++) {
                      curr_session->sender->sliding_window[i] = curr_session->sender->sliding_window[i+1];
                      curr_session->sender->retransmission_attempts[i] = curr_session->sender->retransmission_attempts[i+1];
                      curr_session->sender->data_timeout_arg[i] = curr_session->sender->data_timeout_arg[i+1];

                      if(i == RUDP_WINDOW-2) {
                        curr_session->sender->sliding_window[i+1] = NULL;
                        curr_session->sender->retransmission_attempts[i+1] = 0;
                        curr_session->sender->data_timeout_arg[i+1] = NULL;
                      }
                    }
                  }

                  while(curr_session->sender->data_queue != NULL) {
                    if(curr_session->sender->sliding_window[RUDP_WINDOW-1] != NULL) {
                      break;
                    }
                    else {
                      int index;
                      int i;
                      /* Find the first unused window slot */
                      for(i = RUDP_WINDOW-1; i >= 0; i--) {
                        if(curr_session->sender->sliding_window[i] == NULL) {
                          index = i;
                        }
                      }                      
                      /* Send packet, add to window and remove from queue */
                      curr_session->sender->seqno = curr_session->sender->seqno + 1;                      
                      u_int32_t seqno = curr_session->sender->seqno;
                      int len = curr_session->sender->data_queue->len;
                      char *payload = curr_session->sender->data_queue->item;
                      struct rudp_packet *datap = create_rudp_packet(RUDP_DATA, seqno, len, payload);
                      curr_session->sender->sliding_window[index] = datap;
                      curr_session->sender->retransmission_attempts[index] = 0;
                      struct data *temp = curr_session->sender->data_queue;
                      curr_session->sender->data_queue = curr_session->sender->data_queue->next;
                      free(temp->item);
                      free(temp);
                      send_packet(false, (rudp_socket_t)file, datap, &sender);
                    }
                  }
                  if(curr_socket->close_requested) {
                    /* Can the socket be closed? */
                    struct session *head_sessions = curr_socket->sessions_list_head;
                    while(head_sessions != NULL) {
                      if(head_sessions->sender->session_finished == false) {
                        if(head_sessions->sender->data_queue == NULL &&  
                           head_sessions->sender->sliding_window[0] == NULL && 
                           head_sessions->sender->status == OPEN) {
                          head_sessions->sender->seqno += 1;                      
                          struct rudp_packet *p = create_rudp_packet(RUDP_FIN, head_sessions->sender->seqno, 0, NULL);
                          send_packet(false, (rudp_socket_t)file, p, &head_sessions->address);
                          free(p);
                          head_sessions->sender->status = FIN_SENT;
                        }
                      }
                      head_sessions = head_sessions->next;
                    }
                  }
                }
              }
            }
            else if(curr_session->sender->status == FIN_SENT) {
              /* Handle ACK for FIN */
              if( (curr_session->sender->seqno + 1) == received_packet->header.seqno) {
                event_timeout_delete(timeout_callback, curr_session->sender->fin_timeout_arg);
                struct timeoutargs *t = curr_session->sender->fin_timeout_arg;
                free(t->packet);
                free(t->recipient);
                free(t);
                curr_session->sender->session_finished = true;
                if(curr_socket->close_requested) {
                  /* See if we can close the socket */
                  struct session *head_sessions = curr_socket->sessions_list_head;
                  bool_t all_done = true;
                  while(head_sessions != NULL) {
                    if(head_sessions->sender->session_finished == false) {
                      all_done = false;
                    }
                    else if(head_sessions->receiver != NULL && head_sessions->receiver->session_finished == false) {
                      all_done = false;
                    }
                    else {
                      free(head_sessions->sender);
                      if(head_sessions->receiver) {
                        free(head_sessions->receiver);
                      }
                    }

                    struct session *temp = head_sessions;
                    head_sessions = head_sessions->next;
                    free(temp);
                  }
                  if(all_done) {
                    if(curr_socket->handler != NULL) {
                      curr_socket->handler((rudp_socket_t)file, RUDP_EVENT_CLOSED, &sender);
                      event_fd_delete(receive_callback, (rudp_socket_t)file);
                      close(file);
                      free(curr_socket);
                    }
                  }
                }
              }
              else {
                /* Received incorrect ACK for FIN - ignore it */
              }
            }
          }
          else if(rudpheader.type == RUDP_DATA) {
            /* Handle DATA packet. If the receiver is OPENING, it can transition to OPEN */
            if(curr_session->receiver->status == OPENING) {
              if(rudpheader.seqno == curr_session->receiver->expected_seqno) {
                curr_session->receiver->status = OPEN;
              }
            }

            if(rudpheader.seqno == curr_session->receiver->expected_seqno) {
              /* Sequence numbers match - ACK the data */
              u_int32_t seqno = rudpheader.seqno + 1;
              curr_session->receiver->expected_seqno = seqno;
              struct rudp_packet *p = create_rudp_packet(RUDP_ACK, seqno, 0, NULL);
  
              send_packet(true, (rudp_socket_t)file, p, &sender);
              free(p);
              
              /* Pass the data up to the application */
              if(curr_socket->recv_handler != NULL)
                curr_socket->recv_handler((rudp_socket_t)file, &sender, 
                              (void*)&received_packet->payload, received_packet->payload_length);
            }
            /* Handle the case where an ACK was lost */
            else if(SEQ_GEQ(rudpheader.seqno, (curr_session->receiver->expected_seqno - RUDP_WINDOW)) &&
                SEQ_LT(rudpheader.seqno, curr_session->receiver->expected_seqno)) {
              u_int32_t seqno = rudpheader.seqno + 1;
              struct rudp_packet *p = create_rudp_packet(RUDP_ACK, seqno, 0, NULL);
              send_packet(true, (rudp_socket_t)file, p, &sender);
              free(p);
            }
          }
          else if(rudpheader.type == RUDP_FIN) {
            if(curr_session->receiver->status == OPEN) {
              if(rudpheader.seqno == curr_session->receiver->expected_seqno) {
                /* If the FIN is correct, we can ACK it */
                u_int32_t seqno = curr_session->receiver->expected_seqno + 1;
                struct rudp_packet *p = create_rudp_packet(RUDP_ACK, seqno, 0, NULL);
                send_packet(true, (rudp_socket_t)file, p, &sender);
                free(p);
                curr_session->receiver->session_finished = true;

                if(curr_socket->close_requested) {
                  /* Can we close the socket now? */
                  struct session *head_sessions = curr_socket->sessions_list_head;
                  int all_done = true;
                  while(head_sessions != NULL) {
                    if(head_sessions->sender->session_finished == false) {
                      all_done = false;
                    }
                    else if(head_sessions->receiver != NULL && head_sessions->receiver->session_finished == false) {
                      all_done = false;
                    }
                    else {
                      free(head_sessions->sender);
                      if(head_sessions->receiver) {
                        free(head_sessions->receiver);
                      }
                    }
                    
                    struct session *temp = head_sessions;
                    head_sessions = head_sessions->next;
                    free(temp);
                  }
                  if(all_done) {
                    if(curr_socket->handler != NULL) {
                      curr_socket->handler((rudp_socket_t)file, RUDP_EVENT_CLOSED, &sender);
                      event_fd_delete(receive_callback, (rudp_socket_t)file);
                      close(file);
                      free(curr_socket);
                    }
                  }
                }
              }
              else {
                /* FIN received with incorrect sequence number - ignore it */
              }
            }
          }
        }
      }
    }
  }

  free(received_packet);
  return 0;
}