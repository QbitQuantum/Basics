long ssl_sout (SSLSTREAM *stream,char *string,unsigned long size)
{
  SecBuffer buf[4];
  SecBufferDesc msg;
  char *s;
  size_t n;
  if (!stream->tcpstream) return NIL;
				/* until request satisfied */
  for (s = stream->ibuf,n = 0; size;) {
				/* header */
    buf[0].BufferType = SECBUFFER_STREAM_HEADER;
    memset (buf[0].pvBuffer = stream->obuf,0,
	    buf[0].cbBuffer = stream->sizes.cbHeader);
				/* message (up to maximum size) */
    buf[1].BufferType = SECBUFFER_DATA;
    memcpy (buf[1].pvBuffer = stream->obuf + stream->sizes.cbHeader,string,
	    buf[1].cbBuffer = min (size,SSLBUFLEN));
				/* trailer */
    buf[2].BufferType = SECBUFFER_STREAM_TRAILER;
    memset (buf[2].pvBuffer = ((char *) buf[1].pvBuffer) + buf[1].cbBuffer,0,
	    buf[2].cbBuffer = stream->sizes.cbTrailer);
				/* spare */
    buf[3].BufferType = SECBUFFER_EMPTY;
    msg.ulVersion = SECBUFFER_VERSION;
    msg.cBuffers = 4;		/* number of SecBuffers */
    msg.pBuffers = buf;		/* first SecBuffer */
    string += buf[1].cbBuffer;
    size -= buf[1].cbBuffer;	/* this many bytes processed */
				/* encrypt and send message */
    if ((EncryptMessage
	 (&stream->context,0,&msg,NIL) != SEC_E_OK) ||
	!tcp_sout (stream->tcpstream,stream->obuf,
		   buf[0].cbBuffer + buf[1].cbBuffer + buf[2].cbBuffer))
      return ssl_abort (stream);/* encryption or sending failed */
  }
  return LONGT;
}