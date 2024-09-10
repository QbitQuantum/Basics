OM_uint32 gss_wrap (OM_uint32 *minor_status,gss_ctx_id_t context_handle,
		    int conf_req_flag,gss_qop_t qop_req,
		    gss_buffer_t input_message_buffer,int *conf_state,
		    gss_buffer_t output_message_buffer)
{
  OM_uint32 major_status;
  SecBuffer buf[3];
  SecBufferDesc bufs;
  SecPkgContext_Sizes sizes;
  *minor_status = NIL;		/* never any minor status */
  *conf_state = conf_req_flag;	/* same as requested */
  if ((major_status =		/* get trailer and padding sizes */
       QueryContextAttributes (context_handle,SECPKG_ATTR_SIZES,&sizes)) ==
      SEC_E_OK) {
				/* create big enough output buffer */
    output_message_buffer->value =
      fs_get (sizes.cbSecurityTrailer + input_message_buffer->length +
	      sizes.cbBlockSize);
    /* MSDN claims that for EncryptMessage() in Kerberos, you need an
     * uninitialized SECBUFFER_STREAM_HEADER; a SECBUFFER_DATA that "contains
     * the message to be encrypted.  The message is encrypted in place,
     * overwirting the original contents of its buffer"; an uninitialized
     * SECBUFFER_STREAM_TRAILER, and an uninitialized SECBUFFER_EMPTY.  I've
     * never been able to get it to work that way.
     */
    bufs.cBuffers = 3;		/* set up buffer descriptor */
    bufs.pBuffers = buf;
    bufs.ulVersion = SECBUFFER_VERSION;
    buf[0].BufferType = SECBUFFER_TOKEN;
    buf[0].pvBuffer = output_message_buffer->value;
    buf[0].cbBuffer = sizes.cbSecurityTrailer;
				/* I/O buffer */
    buf[1].BufferType = SECBUFFER_DATA;
    buf[1].pvBuffer = ((char *) buf[0].pvBuffer) + buf[0].cbBuffer;
    buf[1].cbBuffer = input_message_buffer->length;
    memcpy (buf[1].pvBuffer,input_message_buffer->value,buf[1].cbBuffer);
    buf[2].BufferType = SECBUFFER_PADDING;
    buf[2].pvBuffer = ((char *) buf[1].pvBuffer) + buf[1].cbBuffer;
    buf[2].cbBuffer = sizes.cbBlockSize;
    if ((major_status = EncryptMessage (context_handle,qop_req,&bufs,0)) ==
	GSS_S_COMPLETE) {
				/* slide data as necessary (how annoying!) */
      unsigned long i = sizes.cbSecurityTrailer - buf[0].cbBuffer;
      if (i) buf[1].pvBuffer =
	       memmove (((char *) buf[0].pvBuffer) + buf[0].cbBuffer,
			buf[1].pvBuffer,buf[1].cbBuffer);
      if (i += (input_message_buffer->length - buf[1].cbBuffer))
	buf[1].pvBuffer = memmove (((char *)buf[1].pvBuffer) + buf[1].cbBuffer,
		   buf[2].pvBuffer,buf[2].cbBuffer);
      output_message_buffer->length = buf[0].cbBuffer + buf[1].cbBuffer +
	buf[2].cbBuffer;
    }
    else fs_give (&output_message_buffer->value);
  }
  return major_status;		/* return status */
}