/*virtual*/ int CDMASMSInterface::onNewATResponseLine(ATCommandsInterface* pInst, const char* line)
{
  if(m_state == SMS_SEND_CMD_SENT)
  {
    DBG("SMS Send: %s", line);
  }
  else if(m_state == SMS_GET_TX_STATUS_CMD_SENT)
  {
    if(!strcmp(line, "sent"))
    {
      m_txState = SMS_SENT;
      m_state = SMS_CMD_PROCESSED;
    }
    else if(!strcmp(line, "failed"))
    {
      m_txState = SMS_FAILED;
      m_state = SMS_CMD_PROCESSED;
    }
    else if(!strcmp(line, "none"))
    {
      m_txState = SMS_NONE;
      m_state = SMS_CMD_PROCESSED;
    }
    else if(!strcmp(line, "pending"))
    {
      m_txState = SMS_PENDING;
      m_state = SMS_CMD_PROCESSED;
    }
  }
  else if(m_state == SMS_GET_CMD_SENT)
  {
    DBG("Header: %s", line);
    
    if(m_msisdn[0]=='\0')
    {
      sscanf(line, "From: %16s", m_msisdn);
    }
    
    m_headersToRead--;
    
    if(m_headersToRead==0) //End of headers
    {
      if(m_msisdn[0]!='\0') //Checks that the incoming number has been retrieved
      {
        m_state = SMS_GET_HDR_RECEIVED;
      }
      else
      {
        m_state = SMS_IDLE; //Error, signal it
      }
    }
  }
  else if(m_state == SMS_GET_HDR_RECEIVED)
  {
    DBG("Message: %s", line);
    size_t cpyLen = MIN( std::strlen(line), m_maxMsgLength - 1 );
    std::memcpy( m_msg, line, cpyLen );
    m_msg[cpyLen] = '\0';
    m_state = SMS_CMD_PROCESSED;
  }
  else if(m_state == SMS_GET_COUNT_CMD_SENT)
  {
    DBG("Inbox: %s", line);
    int index;
    size_t count;
    if((strlen(line) > 16) && sscanf(line + 16, "{Index = %d}: %d", &index, &count) == 2)
    {
      if((index > 0) && (index <=4))
      {
        m_msgInListsCount[index-1] = count;
      }
      if(index == 4)
      {
        m_state = SMS_CMD_PROCESSED;
      }
    }
  }
  return OK;
}