int SSL_SOCKET :: s_ssend(char* b,int sz)
	{
	// QueryContextAttributes
	// Encrypt Message
	// ssend

	SecPkgContext_StreamSizes Sizes;
	SECURITY_STATUS ss = 0;
	ss = QueryContextAttributes(&hCtx,SECPKG_ATTR_STREAM_SIZES,&Sizes);
	if (FAILED(ss))
		return -1;

	Z<SecBuffer> Buffers(100);
	int mPos = 0;
	for(;;)
		{
		Z<char> mmsg(Sizes.cbMaximumMessage*2);
		Z<char> mhdr(Sizes.cbHeader*2);
		Z<char> mtrl(Sizes.cbTrailer*2);

		unsigned int dwMessage = sz - mPos;
		if (dwMessage == 0)
			break; // all ok!

		if (dwMessage > Sizes.cbMaximumMessage)
			{
			dwMessage = Sizes.cbMaximumMessage;
			}
		memcpy(mmsg,b + mPos,dwMessage);
		mPos += dwMessage;


		Buffers[0].pvBuffer     = mhdr;
		Buffers[0].cbBuffer     = Sizes.cbHeader;
		Buffers[0].BufferType   = SECBUFFER_STREAM_HEADER;
		Buffers[2].pvBuffer     = mtrl;
		Buffers[2].cbBuffer     = Sizes.cbTrailer;
		Buffers[2].BufferType   = SECBUFFER_STREAM_TRAILER;
		Buffers[3].pvBuffer     = 0;
		Buffers[3].cbBuffer     = 0;
		Buffers[3].BufferType   = SECBUFFER_EMPTY;
		Buffers[1].pvBuffer     = mmsg;
		Buffers[1].cbBuffer     = dwMessage;
		Buffers[1].BufferType   = SECBUFFER_DATA;

		sbin.ulVersion = SECBUFFER_VERSION;
		sbin.pBuffers = Buffers;
		sbin.cBuffers = 4;

		ss = EncryptMessage(&hCtx,0,&sbin,0);
		if (FAILED(ss))
			return -1;


		// Send this message
		int rval;
		rval = ssend_p((char*)Buffers[0].pvBuffer,Buffers[0].cbBuffer);
		if (rval != Buffers[0].cbBuffer)
			return rval;
		rval = ssend_p((char*)Buffers[1].pvBuffer,Buffers[1].cbBuffer);
		if (rval != Buffers[1].cbBuffer)
			return rval;
		rval = ssend_p((char*)Buffers[2].pvBuffer,Buffers[2].cbBuffer);
		if (rval != Buffers[2].cbBuffer)
			return rval;
		}

	return sz;
	}