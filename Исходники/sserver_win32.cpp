int sserver_write_data(const struct protocol_interface *protocol, const void *data, int length)
{
	if(!length)
		return 0;

	BYTE *buffer = (BYTE*)malloc(length+secSizes.cbHeader+secSizes.cbTrailer);
	memcpy(buffer+secSizes.cbHeader,data,length);

	SecBuffer rgsb[] =
	{
		{ secSizes.cbHeader, SECBUFFER_STREAM_HEADER, buffer },
        {length, SECBUFFER_DATA, buffer+secSizes.cbHeader},
		{ secSizes.cbTrailer, SECBUFFER_STREAM_TRAILER, buffer+secSizes.cbHeader+length },
		{ 0, SECBUFFER_EMPTY, NULL }
    };
    SecBufferDesc sbd = {SECBUFFER_VERSION, sizeof rgsb / sizeof *rgsb, rgsb};
	int rc;

	rc = EncryptMessage(&contextHandle,0,&sbd,0);

	if(rc)
	{
		free(buffer);
		return -1;
	}

	// In practice only the trailer length changes, otherwise this wouldn't work..
	rc = tcp_write(buffer,rgsb[0].cbBuffer+rgsb[1].cbBuffer+rgsb[2].cbBuffer);
	
	free(buffer);
	return length;
}