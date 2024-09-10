// Our workhorse. Implementations call this to get the next HTTP request
ULONG
RequestQueue::GetNextRequest(HTTP_REQUEST_ID  RequestId
                            ,ULONG            Flags
                            ,PHTTP_REQUEST    RequestBuffer
                            ,ULONG            RequestBufferLength
                            ,PULONG           Bytes)
{
  ULONG result = NO_ERROR;
  Request* request = nullptr;

  if(RequestId == 0)
  {
    // Get a new request from the incoming queue
    AutoCritSec lock(&m_lock);

    if(m_incoming.empty())
    {
      lock.Unlock();
      // Wait for event of incoming request
      DWORD result = WaitForSingleObject(m_event,INFINITE);
      lock.Relock();

      // Still no request in the queue, or event interrupted
      if(m_incoming.empty() || result == WAIT_ABANDONED || result == WAIT_FAILED)
      {
        return ERROR_HANDLE_EOF;
      }
    }

    // Move request to servicing queue
    request = m_incoming.front();
    m_incoming.pop_front();
    m_servicing.push_back(request);
    request->SetStatus(RQ_READING);

    // BitBlitting our request!
    memcpy_s(RequestBuffer,RequestBufferLength,request->GetV2Request(),sizeof(HTTP_REQUEST_V2));

    for(int index = 0;index < RequestBuffer->RequestInfoCount;++index)
    {
      if(RequestBuffer->pRequestInfo[index].InfoType == HttpRequestInfoTypeAuth)
      {
        PHTTP_REQUEST_AUTH_INFO info = (PHTTP_REQUEST_AUTH_INFO)RequestBuffer->pRequestInfo[index].pInfo;
        if(info->AccessToken)
        {
          // Taking a duplicate token
          HANDLE token = NULL;
          if(DuplicateTokenEx(request->GetAccessToken()
                             ,TOKEN_DUPLICATE | TOKEN_IMPERSONATE | TOKEN_ALL_ACCESS | TOKEN_READ | TOKEN_WRITE
                             ,NULL
                             ,SecurityImpersonation
                             ,TokenImpersonation
                             ,&token) == FALSE)
          {
            token = NULL;
          }
          // Set cloned token in the request buffer
          info->AccessToken = token;
        }
      }
    }

  }
  else
  {
    // Check that we are restarting this request
    if(RequestId != RequestBuffer->RequestId)
    {
      return ERROR_INVALID_PARAMETER;
    }
    // This is our request. Flags will be set!
    request = reinterpret_cast<Request*>(RequestId);
  }

  // Reading chunks
  if(Flags)
  {
    // Read a one chunk from the stream
    LONG length  = (LONG)RequestBufferLength - sizeof(HTTP_REQUEST_V2) - 16;
    PVOID buffer = (PUCHAR)RequestBuffer     + sizeof(HTTP_REQUEST_V2) + 16;

    // Buffer must at least be capable to receive one standard message
    // Otherwise the caller must use "HttpReceiveRequestEntityBody" !!
    if(length < MESSAGE_BUFFER_LENGTH)
    {
      return ERROR_MORE_DATA;
    }

    // Get the buffer
    int result = HttpReceiveRequestEntityBody(this,RequestId,Flags,buffer,length,Bytes,NULL);
    if(result == NO_ERROR)
    {
      // If no problem, set as first chunk in the request structure
      request->ReceiveChunk(buffer,length);
    }
  }

  // Reflect total bytes read
  if(Bytes)
  {
    *Bytes = request->GetBytes();
  }
  return result;
}