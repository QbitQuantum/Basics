void EspNewIncomingConnectionStream::actOnReceive(IpcConnection *connection)
{
  // check for OS errors
  if (getState() == ERROR_STATE)
  {
    ex_assert(FALSE,"Error while receiving first message from client");
  }

  // check for protocol errors
  bool willPassTheAssertion = 
             (getType() == IPC_MSG_SQLESP_DATA_REQUEST OR
              getType() == IPC_MSG_SQLESP_CANCEL_REQUEST) AND
              getVersion() == CurrEspRequestMessageVersion AND
              moreObjects();
  if (!willPassTheAssertion)
  {
    char *doCatchBugCRx = getenv("ESP_BUGCATCHER_CR_NONUMBER");
    if (!doCatchBugCRx ||
        *doCatchBugCRx != '0')
    {
      connection->dumpAndStopOtherEnd(true, false);
      environment_->getControlConnection()->
        castToGuaReceiveControlConnection()->
        getConnection()->dumpAndStopOtherEnd(true, false);
    }
  }

  ex_assert((getType() == IPC_MSG_SQLESP_DATA_REQUEST OR
             getType() == IPC_MSG_SQLESP_CANCEL_REQUEST) AND
	    getVersion() == CurrEspRequestMessageVersion AND
	    moreObjects(),
	    "Invalid first message from client");

  // take a look at the type of the first object in the message
  IpcMessageObjType nextObjType = getNextObjType();
  switch (nextObjType)
  {
    case ESP_OPEN_HDR:
    case ESP_LATE_CANCEL_HDR:
      {
        ExFragKey key;
        Lng32 remoteInstNum;
        NABoolean isParallelExtract = false; 

        // peek at the message header to see for whom it is
        if (nextObjType == ESP_OPEN_HDR)
        {
          ExEspOpenReqHeader reqHdr((NAMemory *) NULL);
	   
	  *this >> reqHdr;
	  key = reqHdr.key_;
	  remoteInstNum = reqHdr.myInstanceNum_;
	  if (reqHdr.getOpenType() == ExEspOpenReqHeader::PARALLEL_EXTRACT) 
          {
            isParallelExtract = true;
	  }
	}
        else
	{
          // note that the late cancel request may or may not
	  // arrive as the first request (only in the former case
	  // will we reach here)
	  ExEspLateCancelReqHeader reqHdr((NAMemory *) NULL);
	   
	  *this >> reqHdr;
	  key = reqHdr.key_;
	  remoteInstNum = reqHdr.myInstanceNum_;
	}

        if (!isParallelExtract) 
        {
          ExFragInstanceHandle handle =
	    espFragInstanceDir_->findHandle(key);

	  if (handle != NullFragInstanceHandle)
	  {
            // the send bottom node # myInstanceNum of this downloaded fragment
            // is the true recipient of this open request
            ex_split_bottom_tcb * receivingTcb =
              espFragInstanceDir_->getTopTcb(handle);
            ex_send_bottom_tcb *receivingSendTcb =
              receivingTcb->getSendNode(remoteInstNum);

            // Check the connection for a co-located client, and if so,
            // tell the split bottom, because it may prefer this send 
            // bottom when using skew buster uniform distribution.
            if (espFragInstanceDir_->
                  getEnvironment()->
                  getMyOwnProcessId(IPC_DOM_GUA_PHANDLE).match(
                    connection->getOtherEnd().getNodeName(),
                    connection->getOtherEnd().getCpuNum()))
              receivingTcb->setLocalSendBottom(remoteInstNum);

            // Portability note for the code above: we pass IPC_DOM_GUA_PHANDLE
            // for IpcEnvironment::getMyOwnProcessId, even though that method
            // can be called with the default param (IpcNetworkDomain 
            // IPC_DOM_INVALID).  In fact it would  probably be better 
            // to call the object without specifying the IpcNetworkDomain so
            // that it can decide for itself what domain it is using.
            // But there is a problem with the Windows implementation
            // of IpcEnvironment::getMyOwnProcessId, it seems to assume
            // that its domain is IPC_DOM_INTERNET and so this will 
            // cause the botch of an assertion that its control connection 
            // (which is type EspGuaControlConnection) can be cast to a 
            // SockControlConnection.  When this problem is fixed, the 
            // IPC_DOM_GUA_PHANDLE param above can be removed.  Also,
            // when this code is ported to run it a domain other than
            // "guardian", it will be necessary to fix this and to
            // fix IpcEnvironment::getMyOwnProcessId to work properly on
            // windows.

            receivingSendTcb->setClient(connection);
            receivingSendTcb->routeMsg(*this);
          }
	  else
	  {
            connection->dumpAndStopOtherEnd(true, false);
	    ex_assert(FALSE,"entry not found, set diagnostics area and reply");
	  }

        } // normal case, not parallel extract

        else 
        {
          // The OPEN request is from a parallel extract consumer. The
          // incoming request contains a user ID which we will compare
          // against the current user ID for this ESP.

          // NOTE: The user ID for the extract security check is
          // currently sent and compared as a C string. On Linux it is
          // possible to send and compare integers which would lead to
          // simpler code. The code to send/compare strings is still
          // used because it works on all platforms.

          char errorStr[150];

	  // check if next msg is of securityInfo type. 
          ex_assert(moreObjects(), "expected object not received");
          ex_assert(getNextObjType() == ESP_SECURITY_INFO,
	            "received message for unknown message type");
          
	  // unpack security info
	  ExMsgSecurityInfo secInfo(environment_->getHeap());
	  *this >> secInfo;

          // Get the auth ID of this ESP in text form and compare it
          // to the auth ID that arrived in the message. Skip this
          // step in the debug build if an environment variable is
          // set.
          NABoolean doAuthIdCheck = TRUE;
          Int32 status = 0;
#ifdef _DEBUG
          const char *envvar = getenv("NO_EXTRACT_AUTHID_CHECK");
          if (envvar && envvar[0])
            doAuthIdCheck = FALSE;
#endif
          if (doAuthIdCheck)
          {
            // Get user ID from ExMsgSecurityInfo -> (secUserID)
            // the user ID is the integer value made into a string
            // Convert it back into its integer value
            short userIDLen = (short) str_len(secInfo.getAuthID());
            Int32 secUserID = str_atoi(secInfo.getAuthID(), userIDLen);

            // Get the current user ID
            Int32 curUserID = ComUser::getSessionUser(); 

            // Report an error if the user ID is not valid
            if (curUserID == NA_UserIdDefault || secUserID == NA_UserIdDefault)
            {
              str_cpy_c(errorStr,
                        "Producer ESP could not authenticate the consumer, "
                        "no valid current user.");
              status = -1;
            }

            // Make sure user id passed in ExMsgSecurityInfo matches
            // the user id associated with the current session

#if defined(_DEBUG)
            NABoolean doDebug = (getenv("DBUSER_DEBUG") ? TRUE : FALSE);
            if (doDebug)
              printf("[DBUSER:%d] ESP extract user ID: "
                     "local [%d], msg [%d]\n",
                     (int) getpid(), curUserID, secUserID);
#endif

              // Compare user ID, Report an error, if comparison fails
              if (curUserID != secUserID)
              {
                str_cpy_c(errorStr,
                          "Producer ESP could not authenticate the consumer, "
                          "user named passed in ExMsgSecurityInfo is not the "
                          "current user");
                status = -1;
              }

          } // if (doAuthIdCheck)
		   
          // get the split bottom TCB that matches the securityKey
          ex_split_bottom_tcb *receivingTcb = NULL;
          if (status == 0) 
          {
            receivingTcb = espFragInstanceDir_->getExtractTop(secInfo.getSecurityKey());
            if (receivingTcb == NULL) 
            {
              str_cpy_c(errorStr, "Producer ESP could not locate extract node");
              status = -1;
            }
          }

	  // get the sendBottom TCB if not already connected to a client
	  ex_send_bottom_tcb *receivingSendTcb = NULL;
	  if (status == 0)
	  {
	    receivingSendTcb = receivingTcb->getConsumerSendBottom();
	    if (receivingSendTcb == NULL) 
	    {
	      str_cpy_c(errorStr, "Producer ESP already connected to a client");
	      status = -1;
	    }
	  }

          // send the error message to the consumer 
	  if (status != 0) 
	  {
            clearAllObjects();
            setType(IPC_MSG_SQLESP_DATA_REPLY);

            NAMemory *heap = environment_->getHeap();

	    IpcMessageObj* baseObj =
	      new(heap)IpcMessageObj(IPC_SQL_DIAG_AREA, CurrEspReplyMessageVersion);
	    *this << *baseObj;

	    // prepare proper error message
	    char phandle[100];
	    MyGuaProcessHandle myHandle;
            myHandle.toAscii(phandle, 100);

	    ComDiagsArea *diags = ComDiagsArea::allocate(heap);
            *diags << DgSqlCode(-EXE_PARALLEL_EXTRACT_OPEN_ERROR)
                   << DgString0(phandle)
                   << DgString1(errorStr);
	    *this  << *diags;

	    diags->decrRefCount();

            send(TRUE /* TRUE indicates waited */);
          }

          // if everything okay, then make the connection
	  if (status == 0) 
          {
            receivingSendTcb->setClient(connection);
            receivingSendTcb->routeMsg(*this);
          }
        } // parallel extract case
      } // open or cancel header