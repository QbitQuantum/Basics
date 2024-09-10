bool CRTSPClient::OpenStream(char* url)
{
  LogDebug("CRTSPClient::OpenStream()");
  m_session=NULL;
	
  strcpy(m_url,url);
  // Open the URL, to get a SDP description: 
  char* sdpDescription= getSDPDescriptionFromURL(m_ourClient, url, ""/*username*/, ""/*password*/,""/*proxyServerName*/, 0/*proxyServerPortNum*/,1234/*desiredPortNum*/);
  if (sdpDescription == NULL) 
  {
    LogDebug("Failed to get a SDP description from URL %s %s",url ,m_env->getResultMsg() );
    shutdown();
    return false;
  }
  //LogDebug("Opened URL %s %s",url,sdpDescription);

  char* range=strstr(sdpDescription,"a=range:npt=");
  if (range!=NULL)
  {
    char *pStart = range+strlen("a=range:npt=");
    char *pEnd = strstr(range,"-") ;
    if (pEnd!=NULL)
    {
      pEnd++ ;
      double Start=atof(pStart) ;
      double End=atof(pEnd) ;

      LogDebug("rangestart:%f rangeend:%f", Start,End);
      m_duration=((End-Start)*1000.0);
    }
  }
  // Create a media session object from this SDP description:
  m_session = MediaSession::createNew(*m_env, sdpDescription);
  delete[] sdpDescription;
  if (m_session == NULL) 
  {
    LogDebug("Failed to create a MediaSession object from the SDP description:%s ",m_env->getResultMsg());
    shutdown();
    return false;
  } 
  else if (!m_session->hasSubsessions()) 
  {
    LogDebug("This session has no media subsessions");
    shutdown();
    return false;
  }

  // Then, setup the "RTPSource"s for the session:
  MediaSubsessionIterator iter(*m_session);
  MediaSubsession *subsession;
  Boolean madeProgress = False;
  char const* singleMediumToTest = singleMedium;
  while ((subsession = iter.next()) != NULL) 
  {
    // If we've asked to receive only a single medium, then check this now:
    if (singleMediumToTest != NULL) 
    {
      if (strcmp(subsession->mediumName(), singleMediumToTest) != 0) 
      {
        LogDebug("Ignoring %s %s %s" , subsession->mediumName(),subsession->codecName(),singleMedium);
        continue;
      } 
      else 
      {
        // Receive this subsession only
        singleMediumToTest = "xxxxx";
        // this hack ensures that we get only 1 subsession of this type
      }
    }
    if (desiredPortNum != 0) 
    {
      subsession->setClientPortNum(desiredPortNum);
      desiredPortNum += 2;
    }

    if (createReceivers) 
    {
      if (!subsession->initiate(simpleRTPoffsetArg)) 
      {
        LogDebug("Unable to create receiver for %s %s %s" ,subsession->mediumName(),subsession->codecName(),m_env->getResultMsg());
      } 
      else 
      {
        LogDebug("Created receiver for %s %s %d %d " ,subsession->mediumName(),subsession->codecName(),subsession->clientPortNum(),subsession->clientPortNum()+1 );
        madeProgress = True;

        if (subsession->rtpSource() != NULL) 
        {
          // Because we're saving the incoming data, rather than playing
          // it in real time, allow an especially large time threshold
          // (1 second) for reordering misordered incoming packets:
          
          int socketNum= subsession->rtpSource()->RTPgs()->socketNum();
          LogDebug("rtsp:increaseReceiveBufferTo to 2000000 for s:%d",socketNum);
          increaseReceiveBufferTo( *m_env, socketNum, 2000000 );

          unsigned const thresh = 1000000; // 1 second 
          subsession->rtpSource()->setPacketReorderingThresholdTime(thresh);

          if (socketInputBufferSize > 0) 
          {
            // Set the RTP source's input buffer size as specified:
            int socketNum= subsession->rtpSource()->RTPgs()->socketNum();
            unsigned curBufferSize= getReceiveBufferSize(*m_env, socketNum);
            unsigned newBufferSize= setReceiveBufferTo(*m_env, socketNum, socketInputBufferSize);
            LogDebug( "Changed socket receive buffer size for the %s %s %d %d",
            subsession->mediumName(),subsession->codecName(),curBufferSize,newBufferSize);
          }
        }
      }
    } 
    else 
    {
      if (subsession->clientPortNum() == 0) 
      {
        LogDebug("No client port was specified for the %s %s",subsession->mediumName(),subsession->codecName());
      } 
      else 
      {	
        madeProgress = True;
      }
    }
  }
  if (!madeProgress) 
  {
    shutdown();
    return false;
  }
	
  // Perform additional 'setup' on each subsession, before playing them:
  if (!setupStreams())
  {
    return false;
  }

  // Create output files:
  // Create and start "FileSink"s for each subsession:
  madeProgress = False;
  iter.reset();
  while ((subsession = iter.next()) != NULL) 
  {
    if (subsession->readSource() == NULL) continue; // was not initiated
		
    CMemorySink* fileSink= CMemorySink::createNew(*m_env,m_buffer,fileSinkBufferSize);
    subsession->sink = fileSink;
    if (subsession->sink == NULL) 
    {
      LogDebug("Failed to create FileSink %s",m_env->getResultMsg());
      shutdown();
      return false;
    } 
    LogDebug("Created output sink:");;
    subsession->sink->startPlaying(*(subsession->readSource()),subsessionAfterPlaying,subsession);
				  
    // Also set a handler to be called if a RTCP "BYE" arrives
    // for this subsession:
    if (subsession->rtcpInstance() != NULL) 
    {
      subsession->rtcpInstance()->setByeHandler(subsessionByeHandler,subsession);
    }
    madeProgress = True;
  }

  return true;
}