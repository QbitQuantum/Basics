/*
  Decrypts data and write to SSL stream
  SYNOPSIS
    ma_schannel_write_decrypt
    pvio              pointer to Communication IO structure
    phContext        a context handle
    DecryptLength    size of decrypted buffer
    ReadBuffer       Buffer for decrypted data
    ReadBufferSize   size of ReadBuffer

  DESCRIPTION
    Write encrypted data to SSL stream.

  RETURN
    SEC_E_OK         on success
    SEC_E_*          if an error occured
*/ 
size_t ma_schannel_write_encrypt(MARIADB_PVIO *pvio,
                                 uchar *WriteBuffer,
                                 size_t WriteBufferSize)
{
  SECURITY_STATUS scRet;
  SecBufferDesc Message;
  SecBuffer Buffers[4];
  DWORD cbMessage;
  PBYTE pbMessage;
  SC_CTX *sctx= (SC_CTX *)pvio->ctls->ssl;
  size_t payload;

  payload= MIN(WriteBufferSize, sctx->IoBufferSize);

  memcpy(&sctx->IoBuffer[sctx->Sizes.cbHeader], WriteBuffer, payload);
  pbMessage = sctx->IoBuffer + sctx->Sizes.cbHeader; 
  cbMessage = (DWORD)payload;
  
  Buffers[0].pvBuffer     = sctx->IoBuffer;
  Buffers[0].cbBuffer     = sctx->Sizes.cbHeader;
  Buffers[0].BufferType   = SECBUFFER_STREAM_HEADER;    // Type of the buffer

  Buffers[1].pvBuffer     = &sctx->IoBuffer[sctx->Sizes.cbHeader];
  Buffers[1].cbBuffer     = (DWORD)payload;
  Buffers[1].BufferType   = SECBUFFER_DATA;

  Buffers[2].pvBuffer     = &sctx->IoBuffer[sctx->Sizes.cbHeader] + payload;
  Buffers[2].cbBuffer     = sctx->Sizes.cbTrailer;
  Buffers[2].BufferType   = SECBUFFER_STREAM_TRAILER;

  Buffers[3].pvBuffer     = SECBUFFER_EMPTY;                    // Pointer to buffer 4
  Buffers[3].cbBuffer     = SECBUFFER_EMPTY;                    // length of buffer 4
  Buffers[3].BufferType   = SECBUFFER_EMPTY;                    // Type of the buffer 4


  Message.ulVersion       = SECBUFFER_VERSION;
  Message.cBuffers        = 4;
  Message.pBuffers        = Buffers;
  if ((scRet = EncryptMessage(&sctx->ctxt, 0, &Message, 0))!= SEC_E_OK)
    return -1;
  
  if (pvio->methods->write(pvio, sctx->IoBuffer, Buffers[0].cbBuffer + Buffers[1].cbBuffer + Buffers[2].cbBuffer))
    return payload; 
  return 0;
}