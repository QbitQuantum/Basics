char *A2Pserialize(ATerm term, A2PType topType, int *length){
	A2PWriter writer = createWriter();
	ByteBuffer buffer = writer->buffer;
	char *result;
	int bufferSize;
	
	doSerialize(writer, topType, term);
	
	bufferSize = getCurrentByteBufferSize(buffer);
	result = (char*) malloc(bufferSize);
	memcpy(result, buffer->buffer, bufferSize);
	*length = bufferSize;
	
	destroyWriter(writer);
	
	return result;
}