void
BUrlProtocolHttp::_CopyChunkInBuffer(char** buffer, ssize_t* bytesReceived)
{
	static ssize_t chunkSize = -1;
	BString chunkHeader;
	
	if (chunkSize >= 0) {
		if ((ssize_t)fInputBuffer.Size() >= chunkSize + 2)  {
			// 2 more bytes to handle the closing CR+LF
			*bytesReceived = chunkSize;
			*buffer = new char[chunkSize+2];
			fInputBuffer.RemoveData(*buffer, chunkSize+2);
			chunkSize = -1;
		} else {
			*bytesReceived = -1;
			*buffer = NULL;
		}
	} else {
		if (_GetLine(chunkHeader) == B_ERROR) {
			chunkSize = -1;
			*buffer = NULL;
			*bytesReceived = -1;
			return;
		}
		
		// Format of a chunk header:
		// <chunk size in hex>[; optional data]
		int32 semiColonIndex = chunkHeader.FindFirst(";", 0);
	
		// Cut-off optional data if present
		if (semiColonIndex != -1)
			chunkHeader.Remove(semiColonIndex, 
				chunkHeader.Length() - semiColonIndex);
			
		chunkSize = strtol(chunkHeader.String(), NULL, 16);		
		PRINT(("BHP[%p] Chunk %s=%d\n", this, chunkHeader.String(), chunkSize));
		if (chunkSize == 0) {
			fContentReceived = true;
		}
		
		*bytesReceived = -1;
		*buffer = NULL;
	}
}