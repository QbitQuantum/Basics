void InDesign_MetaHandler::CacheFileData()
{
	XMP_IO* fileRef = this->parent->ioRef;
	XMP_PacketInfo & packetInfo = this->packetInfo;

	XMP_Assert ( kINDD_PageSize == sizeof(InDesignMasterPage) );
	static const size_t kBufferSize = (2 * kINDD_PageSize);
	XMP_Uns8 buffer [kBufferSize];

	size_t	 dbPages;
	XMP_Uns8 cobjEndian;

	XMP_AbortProc abortProc  = this->parent->abortProc;
	void *        abortArg   = this->parent->abortArg;
	const bool    checkAbort = (abortProc != 0);

	this->containsXMP = false;

	// ---------------------------------------------------------------------------------
	// Figure out which master page is active and seek to the contiguous object portion.

	{
		fileRef->Rewind();
		fileRef->ReadAll ( buffer, (2 * kINDD_PageSize) );

		InDesignMasterPage * masters = (InDesignMasterPage *) &buffer[0];
		XMP_Uns64 seq0 = GetUns64LE ( (XMP_Uns8 *) &masters[0].fSequenceNumber );
		XMP_Uns64 seq1 = GetUns64LE ( (XMP_Uns8 *) &masters[1].fSequenceNumber );

		dbPages = GetUns32LE ( (XMP_Uns8 *) &masters[0].fFilePages );
		cobjEndian = masters[0].fObjectStreamEndian;
		if ( seq1 > seq0 ) {
			dbPages = GetUns32LE ( (XMP_Uns8 *)  &masters[1].fFilePages );
			cobjEndian = masters[1].fObjectStreamEndian;
		}
	}

	XMP_Assert ( ! this->streamBigEndian );
	if ( cobjEndian == kINDD_BigEndian ) this->streamBigEndian = true;

	// ---------------------------------------------------------------------------------------------
	// Look for the XMP contiguous object. Each contiguous object has a header and trailer, both of
	// the InDesignContigObjMarker structure. The stream size in the header/trailer is the number of
	// data bytes between the header and trailer. The XMP stream begins with a 4 byte size of the
	// XMP packet. Yes, this is the contiguous object data size minus 4 - silly but true. The XMP
	// must have a packet wrapper, the leading xpacket PI is used as the marker of XMP.

	XMP_Int64 cobjPos = (XMP_Int64)dbPages * kINDD_PageSize;	// ! Use a 64 bit multiply!
	cobjPos -= (2 * sizeof(InDesignContigObjMarker));			// ! For the first pass in the loop.
	XMP_Uns32 streamLength = 0;									// ! For the first pass in the loop.

	while ( true ) {

		if ( checkAbort && abortProc(abortArg) ) {
			XMP_Throw ( "InDesign_MetaHandler::LocateXMP - User abort", kXMPErr_UserAbort );
		}

		// Fetch the start of the next stream and check the contiguous object header.
		// ! The writeable bit of fObjectClassID is ignored, we use the packet trailer flag.

		cobjPos += streamLength + (2 * sizeof(InDesignContigObjMarker));
		fileRef->Seek ( cobjPos, kXMP_SeekFromStart );
		fileRef->ReadAll ( buffer, sizeof(InDesignContigObjMarker) );

		const InDesignContigObjMarker * cobjHeader = (const InDesignContigObjMarker *) &buffer[0];
		if ( ! CheckBytes ( Uns8Ptr(&cobjHeader->fGUID), kINDDContigObjHeaderGUID, kInDesignGUIDSize ) ) break;	// Not a contiguous object header.
		this->xmpObjID = cobjHeader->fObjectUID;	// Save these now while the buffer is good.
		this->xmpClassID = cobjHeader->fObjectClassID;
		streamLength = GetUns32LE ( (XMP_Uns8 *) &cobjHeader->fStreamLength );

		// See if this is the XMP stream.

		if ( streamLength < (4 + kUTF8_PacketHeaderLen + kUTF8_PacketTrailerLen) ) continue;	// Too small, can't possibly be XMP.

		fileRef->ReadAll ( buffer, (4 + kUTF8_PacketHeaderLen) );
		XMP_Uns32 innerLength = GetUns32LE ( &buffer[0] );
		if ( this->streamBigEndian ) innerLength = GetUns32BE ( &buffer[0] );
		if ( innerLength != (streamLength - 4) ) {
			// Be tolerant of a mistake with the endian flag.
			innerLength = Flip4 ( innerLength );
			if ( innerLength != (streamLength - 4) ) continue;	// Not legit XMP.
		}

		XMP_Uns8 * chPtr = &buffer[4];
		size_t startLen = strlen((char*)kUTF8_PacketStart);
		size_t idLen = strlen((char*)kUTF8_PacketID);
		
		if ( ! CheckBytes ( chPtr, kUTF8_PacketStart, startLen ) ) continue;
		chPtr += startLen;

		XMP_Uns8 quote = *chPtr;
		if ( (quote != '\'') && (quote != '"') ) continue;
		chPtr += 1;
		if ( *chPtr != quote ) {
			if ( ! CheckBytes ( chPtr, Uns8Ptr("\xEF\xBB\xBF"), 3 ) ) continue;
			chPtr += 3;
		}
		if ( *chPtr != quote ) continue;
		chPtr += 1;

		if ( ! CheckBytes ( chPtr, Uns8Ptr(" id="), 4 ) ) continue;
		chPtr += 4;
		quote = *chPtr;
		if ( (quote != '\'') && (quote != '"') ) continue;
		chPtr += 1;
		if ( ! CheckBytes ( chPtr, kUTF8_PacketID, idLen ) ) continue;
		chPtr += idLen;
		if ( *chPtr != quote ) continue;
		chPtr += 1;

		// We've seen enough, it is the XMP. To fit the Basic_Handler model we need to compute the
		// total size of remaining contiguous objects, the trailingContentSize. We don't use the
		// size to EOF, that would wrongly include the final zero padding for 4KB alignment.

		this->xmpPrefixSize = sizeof(InDesignContigObjMarker) + 4;
		this->xmpSuffixSize = sizeof(InDesignContigObjMarker);
		packetInfo.offset = cobjPos + this->xmpPrefixSize;
		packetInfo.length = innerLength;

		XMP_Int64 tcStart = cobjPos + streamLength + (2 * sizeof(InDesignContigObjMarker));
		while ( true ) {
			if ( checkAbort && abortProc(abortArg) ) {
				XMP_Throw ( "InDesign_MetaHandler::LocateXMP - User abort", kXMPErr_UserAbort );
			}
			cobjPos += streamLength + (2 * sizeof(InDesignContigObjMarker));
			XMP_Uns32 len = fileRef->Read ( buffer, sizeof(InDesignContigObjMarker) );
			if ( len < sizeof(InDesignContigObjMarker) ) break;	// Too small, must be end of file.
			cobjHeader = (const InDesignContigObjMarker *) &buffer[0];
			if ( ! CheckBytes ( Uns8Ptr(&cobjHeader->fGUID), kINDDContigObjHeaderGUID, kInDesignGUIDSize ) ) break;	// Not a contiguous object header.
			streamLength = GetUns32LE ( (XMP_Uns8 *) &cobjHeader->fStreamLength );
		}
		this->trailingContentSize = cobjPos - tcStart;

		#if TraceInDesignHandler
			XMP_Uns32 pktOffset = (XMP_Uns32)this->packetInfo.offset;
			printf ( "Found XMP in InDesign file, offsets:\n" );
			printf ( "  CObj head %X, XMP %X, CObj tail %X, file tail %X, padding %X\n",
					 (pktOffset - this->xmpPrefixSize), pktOffset, (pktOffset + this->packetInfo.length),
					 (pktOffset + this->packetInfo.length + this->xmpSuffixSize),
					 (pktOffset + this->packetInfo.length + this->xmpSuffixSize + (XMP_Uns32)this->trailingContentSize) );
		#endif

		this->containsXMP = true;
		break;

	}

	if ( this->containsXMP ) {
		this->xmpFileOffset = packetInfo.offset;
		this->xmpFileSize = packetInfo.length;
		ReadXMPPacket ( this );
	}

}	// InDesign_MetaHandler::CacheFileData