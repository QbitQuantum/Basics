void SchannelContext::encryptAndSendData(const SafeByteArray& data) 
{	
	if (m_streamSizes.cbMaximumMessage == 0)
		return;

	SecBuffer outBuffers[4]	= {0};

	// Calculate the largest required size of the send buffer
	size_t messageBufferSize = (data.size() > m_streamSizes.cbMaximumMessage) 
							 ? m_streamSizes.cbMaximumMessage 
							 : data.size();

	// Allocate a packet for the encrypted data
	SafeByteArray sendBuffer;
	sendBuffer.resize(m_streamSizes.cbHeader + messageBufferSize + m_streamSizes.cbTrailer);

	size_t bytesSent = 0;
	do 
	{
		size_t bytesLeftToSend = data.size() - bytesSent;

		// Calculate how much of the send buffer we'll be using for this chunk
		size_t bytesToSend = (bytesLeftToSend > m_streamSizes.cbMaximumMessage) 
						   ? m_streamSizes.cbMaximumMessage 
						   : bytesLeftToSend;
		
		// Copy the plain text data into the send buffer
		memcpy(&sendBuffer[0] + m_streamSizes.cbHeader, &data[0] + bytesSent, bytesToSend);

		outBuffers[0].pvBuffer	 = &sendBuffer[0];
		outBuffers[0].cbBuffer	 = m_streamSizes.cbHeader;
		outBuffers[0].BufferType = SECBUFFER_STREAM_HEADER;

		outBuffers[1].pvBuffer	 = &sendBuffer[0] + m_streamSizes.cbHeader;
		outBuffers[1].cbBuffer	 = (unsigned long)bytesToSend;
		outBuffers[1].BufferType = SECBUFFER_DATA;

		outBuffers[2].pvBuffer	 = &sendBuffer[0] + m_streamSizes.cbHeader + bytesToSend;
		outBuffers[2].cbBuffer	 = m_streamSizes.cbTrailer;
		outBuffers[2].BufferType = SECBUFFER_STREAM_TRAILER;

		outBuffers[3].pvBuffer   = 0;
		outBuffers[3].cbBuffer   = 0;
		outBuffers[3].BufferType = SECBUFFER_EMPTY;

		SecBufferDesc outBufferDesc = {0};
		outBufferDesc.cBuffers   = 4;
		outBufferDesc.pBuffers   = outBuffers;
		outBufferDesc.ulVersion  = SECBUFFER_VERSION;

		SECURITY_STATUS status = EncryptMessage(m_ctxtHandle, 0, &outBufferDesc, 0);
		if (status != SEC_E_OK) 
		{
			indicateError();
			return;
		}

		sendDataOnNetwork(&sendBuffer[0], outBuffers[0].cbBuffer + outBuffers[1].cbBuffer + outBuffers[2].cbBuffer);
		bytesSent += bytesToSend;

	} while (bytesSent < data.size());
}