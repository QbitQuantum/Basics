void Scanner_MetaHandler::CacheFileData()
{
	LFA_FileRef fileRef   = this->parent->fileRef;
	bool        beLenient = XMP_OptionIsClear ( this->parent->openFlags, kXMPFiles_OpenStrictly );

	int			pkt;
	XMP_Int64	bufPos;
	size_t		bufLen;
	SXMPMeta *	newMeta;
	
	XMP_AbortProc abortProc  = this->parent->abortProc;
	void *            abortArg   = this->parent->abortArg;
	const bool        checkAbort = (abortProc != 0);

	std::vector<CandidateInfo> candidates;	// ! These have SXMPMeta* fields, don't leak on exceptions.
	
	this->containsXMP = false;
	
	try {
		
		// ------------------------------------------------------
		// Scan the entire file to find all of the valid packets.
		
		XMP_Int64  fileLen = LFA_Measure ( fileRef );
		XMPScanner scanner ( fileLen );

		enum { kBufferSize = 64*1024 };
		XMP_Uns8	buffer [kBufferSize];

		LFA_Seek ( fileRef, 0, SEEK_SET );
		
		for ( bufPos = 0; bufPos < fileLen; bufPos += bufLen ) {
			if ( checkAbort && abortProc(abortArg) ) {
				XMP_Throw ( "Scanner_MetaHandler::LocateXMP - User abort", kXMPErr_UserAbort );
			}
			bufLen = LFA_Read ( fileRef, buffer, kBufferSize );
			if ( bufLen == 0 ) XMP_Throw ( "Scanner_MetaHandler::LocateXMP: Read failure", kXMPErr_ExternalFailure );
			scanner.Scan ( buffer, bufPos, bufLen );
		}
		
		// --------------------------------------------------------------
		// Parse the valid packet snips, building a vector of candidates.
		
		long snipCount = scanner.GetSnipCount();
		
		XMPScanner::SnipInfoVector snips ( snipCount );
		scanner.Report ( snips );
		
		for ( pkt = 0; pkt < snipCount; ++pkt ) {

			if ( checkAbort && abortProc(abortArg) ) {
				XMP_Throw ( "Scanner_MetaHandler::LocateXMP - User abort", kXMPErr_UserAbort );
			}
				
			// Seek to the packet then try to parse it.
			
			if ( snips[pkt].fState != XMPScanner::eValidPacketSnip ) continue;
			LFA_Seek ( fileRef, snips[pkt].fOffset, SEEK_SET );
			newMeta = new SXMPMeta();
			std::string xmpPacket;
			xmpPacket.reserve ( (size_t)snips[pkt].fLength );

			try {
				for ( bufPos = 0; bufPos < snips[pkt].fLength; bufPos += bufLen ) {
					bufLen = kBufferSize;
					if ( (bufPos + bufLen) > (size_t)snips[pkt].fLength ) bufLen = size_t ( snips[pkt].fLength - bufPos );
					(void) LFA_Read ( fileRef, buffer, (XMP_Int32)bufLen, kLFA_RequireAll );
					xmpPacket.append ( (const char *)buffer, bufLen );
					newMeta->ParseFromBuffer ( (char *)buffer, (XMP_StringLen)bufLen, kXMP_ParseMoreBuffers );
				}
				newMeta->ParseFromBuffer ( 0, 0, kXMP_NoOptions );
			} catch ( ... ) {
				delete newMeta;
				if ( beLenient ) continue;	// Skip if we're being lenient, else rethrow.
				throw;
			}

			// It parsed OK, add it to the array of candidates.
			
			candidates.push_back ( CandidateInfo() );
			CandidateInfo & newInfo = candidates.back();
			newInfo.xmpObj = newMeta;
			newInfo.xmpPacket.swap ( xmpPacket );
			newInfo.packetInfo.offset = snips[pkt].fOffset;
			newInfo.packetInfo.length = (XMP_Int32)snips[pkt].fLength;
			newInfo.packetInfo.charForm  = snips[pkt].fCharForm;
			newInfo.packetInfo.writeable = (snips[pkt].fAccess == 'w');

		}
		
		// ----------------------------------------
		// Figure out which packet is the main one.
		
		int main = PickMainPacket ( candidates, beLenient );
		
		if ( main != -1 ) {
			this->packetInfo = candidates[main].packetInfo;
			this->xmpPacket.swap ( candidates[main].xmpPacket );
			this->xmpObj = *candidates[main].xmpObj;
			this->containsXMP = true;
			this->processedXMP = true;
		}
		
		for ( pkt = 0; pkt < (int)candidates.size(); ++pkt ) {
			if ( candidates[pkt].xmpObj != 0 ) delete candidates[pkt].xmpObj;
		}
	
	} catch ( ... ) {
	
		// Clean up the SXMPMeta* fields from the vector of candidates.
		for ( pkt = 0; pkt < (int)candidates.size(); ++pkt ) {
			if ( candidates[pkt].xmpObj != 0 ) delete candidates[pkt].xmpObj;
		}
		throw;
	
	}

}	// Scanner_MetaHandler::CacheFileData