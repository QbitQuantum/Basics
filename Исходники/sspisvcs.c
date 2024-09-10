int SSPI_send(SocketClass *self, const void *buffer, int len)
{
	CSTR func = "SSPI_send";

	if (0 != (self->sspisvcs & SchannelService))
	{
		SecPkgContext_StreamSizes	sizes;
		int	ttllen, wrtlen, slen;
		LPVOID	lpHead;
		LPVOID	lpMsg;
		LPVOID	lpTrail;
		SecBuffer	sb[4];
		SecBufferDesc	sbd;
		SchannelSpec *ssd = (SchannelSpec *) self->ssd;

		QueryContextAttributes(&ssd->hCtxt, SECPKG_ATTR_STREAM_SIZES, &sizes);
		slen = len;
		ttllen = sizes.cbHeader + len + sizes.cbTrailer;
		if (ttllen > sizes.cbMaximumMessage)
		{
			ttllen = sizes.cbMaximumMessage;
			slen = ttllen - sizes.cbHeader - sizes.cbTrailer;
		}
		lpHead = malloc(ttllen);
		lpMsg = (char *) lpHead + sizes.cbHeader;
		memcpy(lpMsg, buffer, slen);
		lpTrail = (char *) lpMsg + slen;

		sb[0].cbBuffer	= sizes.cbHeader;
		sb[0].pvBuffer	= lpHead;
		sb[0].BufferType = SECBUFFER_STREAM_HEADER;
		sb[1].cbBuffer	= slen;
		sb[1].pvBuffer	= lpMsg;
		sb[1].BufferType = SECBUFFER_DATA;
		sb[2].cbBuffer	= sizes.cbTrailer;
		sb[2].pvBuffer	= lpTrail;
		sb[2].BufferType = SECBUFFER_STREAM_TRAILER;
	/*	sb[3].cbBuffer	= 16;
		sb[3].pvBuffer	= lpPad; */
		sb[3].BufferType = SECBUFFER_EMPTY;

		sbd.cBuffers = 4;
		sbd.pBuffers = sb;
		sbd.ulVersion = SECBUFFER_VERSION;

		EncryptMessage(&ssd->hCtxt, 0, &sbd, 0);

mylog("EMPTY=%p %d %d\n", sb[3].pvBuffer, sb[3].cbBuffer, sb[3].BufferType);
		if (wrtlen = sendall(self->socket, lpHead, ttllen), wrtlen < 0)
		{
			int	gerrno = SOCK_ERRNO;

			free(lpHead);
			SOCK_ERRNO_SET(gerrno);
			return -1;
		}

		free(lpHead);
		return slen;
	}
	else
		return send(self->socket, (char *) buffer, len, 0);
}