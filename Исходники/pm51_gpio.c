static int encodeCMD( unsigned char* inBuffer, int inLength, unsigned char* outputBuffer, int* outputLength )
{
	unsigned char* ptr = outputBuffer;
	char checkSum = 0;
	int length = 2 * inLength + 4;  // total length of output buffer if all goes well
	unsigned char val;
	int i;

	if ( inLength <= 0 )
		return -1;

	if ( inBuffer == NULL || outputBuffer == NULL || outputLength == NULL )
		return -1;

	// now convert data to ASCII and assemble output buffer
	*outputLength = length;

	*ptr++ = SYNC;			  // sync byte
	*ptr++ = 2 * inLength;	  // length of message characters in buffer (excludes checksum chars)
	for( i = 0; i < inLength; i++ )
	{
		val = *(inBuffer + i);
		checkSum = checkSum + val;
		*ptr = byteToChar((val >> 4) & 0x0F);
		ptr++;
		*ptr = byteToChar(val & 0x0F);
		ptr++;
	}

	// put checksum into buffer
	//checkSum = -checkSum & 0xFF;  // don't bother inverting checksum -- just use it as is
	_DBG(1, "output checksum %x\n", checkSum );

	*ptr = byteToChar((checkSum >> 4) & 0x0F);
	ptr++;
	*ptr = byteToChar(checkSum & 0x0F);
	//sprintf( (char*)ptr++, "%0X", (checkSum >> 4) & 0x0F );
	//sprintf( (char*)ptr, "%0X", checkSum & 0x0F );

	_DBG(1, "encodeOutputBuffer: " );
	for( i = 0; i < length; i++ )
		_DBG(1, "%0x ", outputBuffer[i] );
	_DBG(1, "\n\n" );

	return 0;
}