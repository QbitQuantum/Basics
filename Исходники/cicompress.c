int segment_compress(int *source, int size, char *compress_source, long int *compress_size)
{	
	int err;
	
	uLong sourceLen = (uLongf)size;
	uLongf destLen = (uLongf)(*compress_size);
	Bytef *byte_source;
	Bytef *byte_dest;
	
	byte_source = (Bytef *)source;
	byte_dest = (Bytef *)compress_source;
	
	err = compress2(byte_dest, &destLen, byte_source, sourceLen, COMPRESS_LEVEL);
	
	if(err != Z_OK) {
		printf("ERROR: Error compress!\n");
		if(err == Z_BUF_ERROR)
			printf("ERROR: The buffer was not large enough to hold the uncompressed data.\n");
		if(err == Z_MEM_ERROR)
			printf("ERROR: Insufficient memory.\n");
		if(err == Z_STREAM_ERROR)
			printf("ERROR: The compressed data (referenced by source) was corrupted.\n");
	}

	*compress_size = (long int)destLen;
	
	return 0;
}