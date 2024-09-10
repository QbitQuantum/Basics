/*
** A "local" function of main().  Handles a #messageType# message arrived on
** #sd# accompanied by #dataSize# bytes of data.
*/
static void
ProcessRequest(Socket *sd,
               MessageType messageType,
               size_t dataSize) {

  char *contents;
  DataDescriptor contentsDescriptor = SIMPLE_DATA(CHAR_TYPE, 0);
  AutoFetchInfo *expandedAutoFetches;
  unsigned long expiration;
  DataDescriptor expirationDescriptor = SIMPLE_DATA(UNSIGNED_LONG_TYPE, 1);
  int i;
  struct state stateDesc;
  char *stateNames;
  DataDescriptor stateNamesDescriptor = SIMPLE_DATA(CHAR_TYPE, 0);

  switch(messageType) {

  case FETCH_STATE:
    if(!RecvData(*sd,
                 &stateDesc,
                 stateDescriptor,
                 stateDescriptorLength,
                 PktTimeOut(*sd))) {
      DROP_SOCKET(sd);
      ERROR("ProcessRequest: state receive failed\n");
      return;
    }
    contents = (char *)malloc(stateDesc.rec_count * MAX_RECORD_SIZE);
    if(contents == NULL) {
      (void)SendMessage(*sd, MEMORY_FAILED, PktTimeOut(*sd));
      ERROR("ProcessRequest: out of memory\n");
    }
    else {
      if(ReadState(FileOfState(memoryDir, stateDesc.id),
                   contents,
                   stateDesc.rec_count,
                   stateDesc.rec_count * MAX_RECORD_SIZE,
                   stateDesc.seq_no,
                   &stateDesc.time_out,
                   &stateDesc.seq_no,
                   &stateDesc.rec_count,
                   &stateDesc.rec_size)) {
        if(stateDesc.rec_count > 0) {
          contentsDescriptor.repetitions =
            stateDesc.rec_size * stateDesc.rec_count;
          (void)SendMessageAndDatas(*sd,
                                    STATE_FETCHED,
                                    &stateDesc,
                                    stateDescriptor,
                                    stateDescriptorLength,
                                    contents,
                                    &contentsDescriptor,
                                    1,
                                    PktTimeOut(*sd));
        }
        else {
          (void)SendMessageAndData(*sd,
                                   STATE_FETCHED,
                                   &stateDesc,
                                   stateDescriptor,
                                   stateDescriptorLength,
                                   PktTimeOut(*sd));
        }
      }
      else {
        (void)SendMessage(*sd, MEMORY_FAILED, PktTimeOut(*sd));
        if(errno == EMFILE) {
          CheckConnections();
        }
      }
      free(contents);
    }
    break;

  case STORE_STATE:
    if(!RecvData(*sd,
                 &stateDesc,
                 stateDescriptor,
                 stateDescriptorLength,
                 PktTimeOut(*sd))) {
      DROP_SOCKET(sd);
      ERROR("ProcessRequest: state receive failed\n");
      return;
    }
    contentsDescriptor.repetitions = stateDesc.rec_size * stateDesc.rec_count;
    contents = (char *)malloc(contentsDescriptor.repetitions + 1);
    if(contents == NULL) {
      (void)SendMessage(*sd, MEMORY_FAILED, PktTimeOut(*sd));
      ERROR("ProcessRequest: out of memory\n");
    }
    else {
      contents[contentsDescriptor.repetitions] = '\0';
      if(!RecvData(*sd,
                   contents,
                   &contentsDescriptor,
                   1,
                   PktTimeOut(*sd))) {
        DROP_SOCKET(sd);
        ERROR("ProcessRequest: data receive failed\n");
      }
      else {
        (void)SendMessage(*sd,
                          KeepState(&memLogLocation,
                                    &stateDesc,
                                    contents,
                                    contentsDescriptor.repetitions) ?
                          STATE_STORED : MEMORY_FAILED,
                          PktTimeOut(*sd));
        for(i = 0; i < autoFetchCount; i++) {
          if(strstr(autoFetches[i].stateNames, stateDesc.id) != NULL) {
            if(!SendMessageAndDatas(autoFetches[i].clientSock,
                                    STATE_FETCHED,
                                    &stateDesc,
                                    stateDescriptor,
                                    stateDescriptorLength,
                                    contents,
                                    &contentsDescriptor,
                                    1,
                                    PktTimeOut(autoFetches[i].clientSock))) {
              DROP_SOCKET(&autoFetches[i].clientSock);
              free(autoFetches[i].stateNames);
              autoFetches[i] = autoFetches[--autoFetchCount];
            }
          }
        }
      }
      free(contents);
    }
    break;

  case AUTOFETCH_BEGIN:
    stateNamesDescriptor.repetitions = dataSize;
    stateNames = (char *)malloc(dataSize);
    if(stateNames == NULL) {
      (void)SendMessage(*sd, MEMORY_FAILED, PktTimeOut(*sd));
      DROP_SOCKET(sd);
      ERROR("ProcessRequest: out of memory\n");
    }
    else if(!RecvData(*sd,
                      stateNames,
                      &stateNamesDescriptor,
                      1,
                      PktTimeOut(*sd))) {
      (void)SendMessage(*sd, MEMORY_FAILED, PktTimeOut(*sd));
      DROP_SOCKET(sd);
      free(stateNames);
      ERROR("ProcessRequest: data receive failed\n");
    }
    else if(*stateNames == '\0') {
      free(stateNames);
      EndAutoFetch(*sd);
      (void)SendMessage(*sd, AUTOFETCH_ACK, PktTimeOut(*sd));
    }
    else {
      for(i=0; (i < autoFetchCount) && (autoFetches[i].clientSock != *sd); i++)
        ; /* Nothing more to do. */
      if(i == autoFetchCount) {
        expandedAutoFetches =
          REALLOC(autoFetches, (autoFetchCount + 1) * sizeof(AutoFetchInfo));
        if(expandedAutoFetches == NULL) {
          (void)SendMessage(*sd, MEMORY_FAILED, PktTimeOut(*sd));
          DROP_SOCKET(sd);
          ERROR("ProcessRequest: out of memory\n");
          break;
        }
        autoFetches = expandedAutoFetches;
        autoFetches[i].clientSock = *sd;
        autoFetchCount++;
      }
      else {
        free(autoFetches[i].stateNames);
      }
      autoFetches[i].stateNames = stateNames;
      (void)SendMessage(*sd, AUTOFETCH_ACK, PktTimeOut(*sd));
    }
    break;

  case MEMORY_CLEAN:
    if(!RecvData(*sd, &expiration, &expirationDescriptor, 1, PktTimeOut(*sd))) {
      DROP_SOCKET(sd);
      ERROR("ProcessRequest: data receive failed\n");
    }
    else {
      (void)SendMessage(*sd, MEMORY_CLEANED, PktTimeOut(*sd));
      (void)DoClean(expiration);
    }
    break;

#ifdef WITH_NETLOGGER	  
  case MEMORY_LOGDEST: /* config message contains log location */
	  if(!RecvData(*sd,
		  &memLogLocation,
		  loglocationDescriptor,
		  loglocationDescriptorLength,
		  PktTimeOut(*sd))) {
		  DROP_SOCKET(sd);
		  ERROR("ProcessRequest: loglocation receive failed\n");
		  return;
	  }else
	  {
		  (void)SendMessage(*sd, MEMORY_LOGDEST_ACK, PktTimeOut(*sd));
	  }
	  LOG2("ProcessRequest: loglocation %d .%s.\n", memLogLocation.loc_type, memLogLocation.path);
 
	  break;
#endif /* WITH_NETLOGGER */	  	

  default:
    DROP_SOCKET(sd);
    ERROR1("ProcessRequest: unknown message %d\n", messageType);

  }

}