/*
 * processRPCCall() is called after some validations.  The assumption is that
 * the request is an HTTP post of content-type text/xml with a content-length
 * that is less than the maximum the library can handle.
 *
 * The caller should check the error status, and if the error was other than
 * a network type, respond back to the client to let them know the call failed.
 */
void
processRPCCall(
    xmlrpc_env *     const envP,
    IN HANDLE        hReqQueue,
    IN PHTTP_REQUEST pRequest
    )
{
    HTTP_RESPONSE   response;
    DWORD           result;
    DWORD           bytesSent;
    PUCHAR          pEntityBuffer;
    ULONG           EntityBufferLength;
    ULONG           BytesRead;
#define MAX_ULONG_STR ((ULONG) sizeof("4294967295"))
    CHAR            szContentLength[MAX_ULONG_STR];
    CHAR            szServerHeader[20];
    HTTP_DATA_CHUNK dataChunk;
    ULONG           TotalBytesRead = 0;
    xmlrpc_mem_block * body;
    xmlrpc_mem_block * output;

    BytesRead  = 0;
    body       = NULL;
    output     = NULL;

    // Allocate some space for an entity buffer.
    EntityBufferLength = 2048;  
    pEntityBuffer      = (PUCHAR) ALLOC_MEM( EntityBufferLength );
    if (pEntityBuffer == NULL)
    {
        xmlrpc_faultf(envP, "Out of Memory");
        goto Done;
    }

    // NOTE: If we had passed the HTTP_RECEIVE_REQUEST_FLAG_COPY_BODY
    //       flag with HttpReceiveHttpRequest(), the entity would have
    //       been a part of HTTP_REQUEST (using the pEntityChunks field).
    //       Since we have not passed that flag, we can be assured that 
    //       there are no entity bodies in HTTP_REQUEST.
    if(pRequest->Flags & HTTP_REQUEST_FLAG_MORE_ENTITY_BODY_EXISTS)
    {
        //Allocate some space for an XMLRPC memory block.
        body = xmlrpc_mem_block_new(envP, 0);
        if (envP->fault_occurred) 
            goto Done;

        // The entity body can be sent over multiple calls. Let's collect all
        // of these in a buffer and send the buffer to the xmlrpc-c library 
        do
        {
            // Read the entity chunk from the request.
            BytesRead = 0; 
            result = HttpReceiveRequestEntityBody(
                hReqQueue,
                pRequest->RequestId,
                0,
                pEntityBuffer,
                EntityBufferLength,
                &BytesRead,
                NULL
                );
            switch(result)
            {
                case NO_ERROR:
                    if(BytesRead != 0)
                    {
                        XMLRPC_MEMBLOCK_APPEND(char, envP, body, 
                                               pEntityBuffer, BytesRead);
                        if(envP->fault_occurred)
                            goto Done;                      
                    }
                    break;

                case ERROR_HANDLE_EOF:
                    // We have read the last request entity body. We can now 
                    // process the suppossed XMLRPC data.
                    if(BytesRead != 0)
                    {
                        XMLRPC_MEMBLOCK_APPEND(char, envP, body, 
                                               pEntityBuffer, BytesRead);
                        if(envP->fault_occurred)
                            goto Done;
                    }

                    // We will send the response over multiple calls. 
                    // This is achieved by passing the 
                    // HTTP_SEND_RESPONSE_FLAG_MORE_DATA flag.
                    
                    // NOTE: Since we are accumulating the TotalBytesRead in 
                    //       a ULONG, this will not work for entity bodies that
                    //       are larger than 4 GB. To work with large entity
                    //       bodies, we would have to use a ULONGLONG.
                    TraceA("xmlrpc_server RPC2 handler processing "
                           "RPC request.");
                                        
                    // Process the RPC.
                    xmlrpc_registry_process_call2(
                        envP, global_registryP,
                        XMLRPC_MEMBLOCK_CONTENTS(char, body),
                        XMLRPC_MEMBLOCK_SIZE(char, body),
                        NULL,
                        &output);
                    if (envP->fault_occurred) 
                        goto Done;

                    // Initialize the HTTP response structure.
                    INITIALIZE_HTTP_RESPONSE(&response, 200, "OK");

                    //Add the content-length
                    StringCchPrintfA(szContentLength,MAX_ULONG_STR, "%lu",
                                     XMLRPC_MEMBLOCK_SIZE(char, output));
                    ADD_KNOWN_HEADER(
                            response, 
                            HttpHeaderContentLength, 
                            szContentLength );

                    //Add the content-type
                    ADD_KNOWN_HEADER(response, HttpHeaderContentType,
                                     "text/xml");
                    
                    StringCchPrintfA(szServerHeader,20,
                                     "xmlrpc-c %s",XMLRPC_C_VERSION);
                    ADD_KNOWN_HEADER(response, HttpHeaderServer,
                                     szServerHeader);

                    //send the response
                    result = HttpSendHttpResponse(
                        hReqQueue,           // ReqQueueHandle
                        pRequest->RequestId, // Request ID
                        HTTP_SEND_RESPONSE_FLAG_MORE_DATA,
                        &response,           // HTTP response
                        NULL,                // pReserved1
                        &bytesSent,          // bytes sent (optional)
                        NULL,                // pReserved2
                        0,                   // Reserved3
                        NULL,                // LPOVERLAPPED
                        NULL                 // pReserved4
                        );
                    if(result != NO_ERROR)
                    {
                        TraceW(L"HttpSendHttpResponse failed with %lu",
                               result);
                        xmlrpc_env_set_fault_formatted(
                            envP, XMLRPC_NETWORK_ERROR,
                            "HttpSendHttpResponse failed with %lu", result);
                        goto Done;
                    }

                    // Send entity body from a memory chunk.
                    dataChunk.DataChunkType = HttpDataChunkFromMemory;
                    dataChunk.FromMemory.BufferLength =
                        (ULONG)XMLRPC_MEMBLOCK_SIZE(char, output);
                    dataChunk.FromMemory.pBuffer =
                        XMLRPC_MEMBLOCK_CONTENTS(char, output);

                    result = HttpSendResponseEntityBody(
                        hReqQueue,
                        pRequest->RequestId,
                        0,                    // This is the last send.
                        1,                    // Entity Chunk Count.
                        &dataChunk,
                        NULL,
                        NULL,
                        0,
                        NULL,
                        NULL
                        );
                    if(result != NO_ERROR)
                    {
                        TraceW(L"HttpSendResponseEntityBody failed "
                               L"with %lu", result);
                        xmlrpc_env_set_fault_formatted(
                                envP, XMLRPC_NETWORK_ERROR,
                                "HttpSendResponseEntityBody failed with %lu",
                                result);
                        goto Done;
                    }
                    goto Done;
                    break;
                default:
                    TraceW(L"HttpReceiveRequestEntityBody failed with %lu",
                           result);
                    xmlrpc_env_set_fault_formatted(
                                envP, XMLRPC_NETWORK_ERROR,
                                "HttpReceiveRequestEntityBody failed "
                                "with %lu", result);
                    goto Done;
            }
        } while(TRUE);
    }