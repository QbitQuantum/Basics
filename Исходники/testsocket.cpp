void sendFileChunk(const char * filename, offset_t offset, ISocket * socket) 
{
    FILE *in = fopen(filename, "rb");
    unsigned size = 0;
    void * buff = NULL;

    if (in)
    {
        fseek(in, 0, SEEK_END);
        offset_t endOffset = ftell(in);
        fseek(in, offset, SEEK_SET);
        if (endOffset < offset)
            size = 0;
        else
            size = (unsigned)(endOffset - offset);
        if (size > CHUNK_SIZE)
            size = CHUNK_SIZE;
        buff = malloc(size);
        size_t numRead = fread(buff, 1, size, in);
        fclose(in);
        if (numRead != size)
		{
            printf("read from file %s failed (%u/%u)\n", filename, (unsigned)numRead, size);
            size = 0;
		}
    }
	else
		printf("read from file %s failed\n", filename);


    if (size > 0)
    {
        MemoryBuffer sendBuffer;
        unsigned rev = size + strlen(filename) + 10;
        rev |= 0x80000000;
        _WINREV(rev);
        sendBuffer.append(rev);
        sendBuffer.append('R');
        rev = 0; // should put the sequence number here
        _WINREV(rev);
        sendBuffer.append(rev);
        rev = 0; // should put the # of recs in msg here
        _WINREV(rev);
        sendBuffer.append(rev);
        sendBuffer.append(strlen(filename)+1, filename);
        sendBuffer.append(size, buff);

        socket->write(sendBuffer.toByteArray(), sendBuffer.length());
    }
    else
    {
        unsigned zeroLen = 0;
        socket->write(&zeroLen, sizeof(zeroLen));
    }

    free(buff);
}