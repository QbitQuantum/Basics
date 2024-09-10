DWORD
SendHttpResponse(    
    IN PHTTP_REQUEST	pRequest,
	IN PHTTP_IO_CONTEXT pContext,
    IN USHORT			StatusCode,
    IN PSTR				pReason,
    IN PSTR				pEntityString,
	IN PSTR				pContentLength
    )
{    
    HTTP_DATA_CHUNK dataChunk;
    DWORD           result;
	PHTTP_LISTENER listener = pContext->listener;
	PHTTP_IO_CONTEXT pResponseContext = GetIOContext();

	//
    // Initialize the HTTP response structure.
    //	
    pResponseContext->Reponse.StatusCode = (StatusCode);     
	pResponseContext->Reponse.pReason = (pReason);        
    pResponseContext->Reponse.ReasonLength = (USHORT) strlen(pReason);  

    //
    // Add a known header.
    //
    //ADD_KNOWN_HEADER
	pResponseContext->Reponse.Headers.KnownHeaders[HttpHeaderContentType].pRawValue = "text/html"; 
	pResponseContext->Reponse.Headers.KnownHeaders[HttpHeaderContentType].RawValueLength = (USHORT)strlen("text/html");

	DEBUG_ASSERT(pEntityString);

	dataChunk.DataChunkType						= HttpDataChunkFromMemory;
    dataChunk.FromMemory.pBuffer				= pEntityString;
    dataChunk.FromMemory.BufferLength			= (ULONG) strlen(pEntityString);
    pResponseContext->Reponse.EntityChunkCount  = 1;
    pResponseContext->Reponse.pEntityChunks		= &dataChunk;		
		   
    // 
    // Since we are sending all the entity body in one call, we don't have 
    // to specify the Content-Length.
    //	
	pResponseContext->operationState = HTTP_LISTENER_STATE_RESPONSE;
	
	// Enqueue async IO Request.
	StartThreadpoolIo(listener->pthreadPoolIO);
    result = HttpSendHttpResponse(
                    listener->hRequestQueue,		// ReqQueueHandle
                    pRequest->RequestId,			// Request ID
                    0,								// Flags
                    &pResponseContext->Reponse,		// HTTP response
                    NULL,							// cache policy
                    NULL,							// bytes sent   (OPTIONAL)
                    NULL,							// pReserved2   (must be NULL)
                    0,								// Reserved3    (must be 0)
                    pResponseContext,				// LPOVERLAPPED (OPTIONAL)
                    NULL							// pReserved4   (must be NULL)
                    );

	if(result != NO_ERROR && result != ERROR_IO_PENDING)
	{
		// need to call this whenever an async I/O operation fails synchronously
		CancelThreadpoolIo(listener->pthreadPoolIO); 
		LOG_ERROR(L"\nSynchronous completion response processing error - %lu", result);
		return result;
	}
	else if(result == NO_ERROR)
	{		
		// Synchronous completion		
		CancelThreadpoolIo(listener->pthreadPoolIO);
		HttpInputQueueEnqueue(listener, 
							  pResponseContext);
	}
	else
	{	
		DEBUG_ASSERT(result == ERROR_IO_PENDING)	
	}

    return NO_ERROR;
}