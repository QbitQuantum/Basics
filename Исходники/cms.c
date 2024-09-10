SECURITY_STATUS ReadDecrypt (void)

// calls recv() - blocking socket read
// http://msdn.microsoft.com/en-us/library/ms740121(VS.85).aspx

// The encrypted message is decrypted in place, overwriting the original contents of its buffer.
// http://msdn.microsoft.com/en-us/library/aa375211(VS.85).aspx

{
  SecBuffer       ExtraBuffer;
  SecBuffer       *pDataBuffer, *pExtraBuffer;

  SECURITY_STATUS scRet;            // unsigned long cbBuffer;    // Size of the buffer, in bytes
  SecBufferDesc   Message;        // unsigned long BufferType;  // Type of the buffer (below)
  SecBuffer       Buffers[4];    // void    SEC_FAR * pvBuffer;   // Pointer to the buffer

  DWORD           cbIoBuffer, cbData, length;
  PBYTE           buff;
  int             i;

  // Read data from server until done.
  cbIoBuffer = 0;
  scRet = 0;
  
  while(TRUE) // Read some data.
  {
    if( cbIoBuffer == 0 || scRet == SEC_E_INCOMPLETE_MESSAGE ) // get the data
    {
      cbDataIn = recv(s, pbBufferIn + cbIoBuffer, cbBufferLen - cbIoBuffer, 0);
      if(cbDataIn == SOCKET_ERROR)
      {
        printf("**** Error %d reading data from server\n", WSAGetLastError());
        scRet = SEC_E_INTERNAL_ERROR;
        break;
      }
      else if(cbDataIn == 0) // Server disconnected.
      {
        if(cbIoBuffer)
        {
          printf("**** Server unexpectedly disconnected\n");
          scRet = SEC_E_INTERNAL_ERROR;
          return scRet;
        }
        else
        break; // All Done
      }
      else // success
      {
        cbIoBuffer += cbDataIn;
      }
    }

    // Decrypt the received data.
    Buffers[0].pvBuffer     = pbBufferIn;
    Buffers[0].cbBuffer     = cbIoBuffer;
    Buffers[0].BufferType   = SECBUFFER_DATA;  // Initial Type of the buffer 1
    Buffers[1].BufferType   = SECBUFFER_EMPTY; // Initial Type of the buffer 2
    Buffers[2].BufferType   = SECBUFFER_EMPTY; // Initial Type of the buffer 3
    Buffers[3].BufferType   = SECBUFFER_EMPTY; // Initial Type of the buffer 4

    Message.ulVersion       = SECBUFFER_VERSION;    // Version number
    Message.cBuffers        = 4;                                    // Number of buffers - must contain four SecBuffer structures.
    Message.pBuffers        = Buffers;                        // Pointer to array of buffers
    
    scRet = sspi->DecryptMessage(&hContext, &Message, 0, NULL);
    
    if( scRet == SEC_I_CONTEXT_EXPIRED ) break; // Server signalled end of session
    
    //      if( scRet == SEC_E_INCOMPLETE_MESSAGE - Input buffer has partial encrypted record, read more
    if( scRet != SEC_E_OK &&
        scRet != SEC_I_RENEGOTIATE &&
        scRet != SEC_I_CONTEXT_EXPIRED )
    { printf("**** DecryptMessage ");
      return scRet; }

    // Locate data and (optional) extra buffers.
    pDataBuffer  = NULL;
    pExtraBuffer = NULL;
    
    for(i = 1; i < 4; i++)
    {
      if( pDataBuffer  == NULL && Buffers[i].BufferType == SECBUFFER_DATA  ) pDataBuffer  = &Buffers[i];
      if( pExtraBuffer == NULL && Buffers[i].BufferType == SECBUFFER_EXTRA ) pExtraBuffer = &Buffers[i];
    }

    if (pDataBuffer!=NULL)
    {
      cbDataIn=pDataBuffer->cbBuffer;
      if (cbDataIn!=0)
      {
        memcpy (pbDataIn, pDataBuffer->pvBuffer, cbDataIn);
      }
    }
      
    // Move any "extra" data to the input buffer.
    if(pExtraBuffer)
    {
      printf ("extra");
      MoveMemory(pbBufferIn, pExtraBuffer->pvBuffer, pExtraBuffer->cbBuffer);
      cbIoBuffer = pExtraBuffer->cbBuffer; // printf("cbIoBuffer= %d  \n", cbIoBuffer);
    }
    else
    cbIoBuffer = 0;
  printf ("\nhello");
  }

  return SEC_E_OK;
}