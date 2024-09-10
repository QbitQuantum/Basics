/* sqEncryptSSL: Encrypt data for SSL transmission.
	Arguments:
		handle - the SSL handle
		srcBuf - the unencrypted input data
		srcLen - the size of the input data
		dstBuf - the output buffer for the encrypted contents
		dstLen - the size of the output buffer
	Returns: The size of the output generated or an error code.
*/
sqInt sqEncryptSSL(sqInt handle, char* srcBuf, sqInt srcLen, char *dstBuf, sqInt dstLen) {
	SECURITY_STATUS ret;
	sqInt total;
	sqSSL *ssl = sslFromHandle(handle);

	if(ssl == NULL || ssl->state != SQSSL_CONNECTED) return SQSSL_INVALID_STATE;

	if(ssl->loglevel) printf("sqEncryptSSL: Encrypting %d bytes\n", srcLen);

	if(srcLen > (int)ssl->sslSizes.cbMaximumMessage) 
		return SQSSL_INPUT_TOO_LARGE;

	ssl->inbuf[0].BufferType = SECBUFFER_STREAM_HEADER;
	ssl->inbuf[0].cbBuffer = ssl->sslSizes.cbHeader;
	ssl->inbuf[0].pvBuffer = dstBuf;

	ssl->inbuf[1].BufferType = SECBUFFER_DATA;
	ssl->inbuf[1].cbBuffer = srcLen;
	ssl->inbuf[1].pvBuffer = dstBuf + ssl->inbuf[0].cbBuffer;

	ssl->inbuf[2].BufferType = SECBUFFER_STREAM_TRAILER;
	ssl->inbuf[2].cbBuffer = ssl->sslSizes.cbTrailer;
	ssl->inbuf[2].pvBuffer = dstBuf + ssl->inbuf[0].cbBuffer + ssl->inbuf[1].cbBuffer;

	ssl->inbuf[3].BufferType = SECBUFFER_EMPTY;
	ssl->inbuf[3].cbBuffer = 0;
	ssl->inbuf[3].pvBuffer = NULL;  

	ssl->sbdIn.cBuffers = 4;

	/* Check to ensure that encrypted contents fits dstBuf.
	   Fail with BUFFER_TOO_SMALL to allow caller to retry. */
	total = ssl->inbuf[0].cbBuffer + ssl->inbuf[1].cbBuffer + ssl->inbuf[2].cbBuffer;
	if(dstLen < total) return SQSSL_BUFFER_TOO_SMALL;

	memcpy(ssl->inbuf[1].pvBuffer, srcBuf, srcLen);

	if(ssl->loglevel) printf("Header: %d; Data: %d; Trailer: %d\n", 
			ssl->inbuf[0].cbBuffer, ssl->inbuf[1].cbBuffer, ssl->inbuf[2].cbBuffer);

	ret = EncryptMessage(&ssl->sslCtxt, 0, &ssl->sbdIn, 0);

	if (ret != SEC_E_OK) {
		if(ssl->loglevel) printf("EncryptMessage returned: %x\n", ret);
		return SQSSL_GENERIC_ERROR;
	}

	/* Return total amount of encrypted contents.
	   Must recompute total here since trailer may be overestimated */
	total = ssl->inbuf[0].cbBuffer + ssl->inbuf[1].cbBuffer + ssl->inbuf[2].cbBuffer;
	return total;
}