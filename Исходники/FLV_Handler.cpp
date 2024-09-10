void FLV_MetaHandler::WriteTempFile ( XMP_IO* tempRef )
{
	if ( ! this->needsUpdate ) return;

	XMP_AbortProc abortProc  = this->parent->abortProc;
	void *        abortArg   = this->parent->abortArg;
	const bool    checkAbort = (abortProc != 0);

	XMP_IO* originalRef = this->parent->ioRef;

	XMP_Uns64 sourceLen = originalRef->Length();
	XMP_Uns64 sourcePos = 0;

	originalRef->Rewind();
	tempRef->Rewind();
	tempRef->Truncate ( 0 );
	XMP_ProgressTracker* progressTracker = this->parent->progressTracker;
	if ( progressTracker != 0 ) {
		float fileSize=(float)(this->xmpPacket.size()+48);
		if ( this->omdTagPos == 0 ) {
			sourcePos=(this->flvHeaderLen+4);
			fileSize+=sourcePos;
		} else {
			if ( this->xmpTagPos < this->omdTagPos ) {
				fileSize+=this->xmpTagPos;
			}
			fileSize+=(this->omdTagPos + this->omdTagLen-
				((this->xmpTagPos!=0 && this->xmpTagPos < this->omdTagPos)?
				(this->xmpTagPos + this->xmpTagLen):0));
			sourcePos =this->omdTagPos + this->omdTagLen;
		}
		if ( (this->xmpTagPos != 0) && (this->xmpTagPos >= sourcePos) ) {
			fileSize+=(this->xmpTagPos - sourcePos);
			sourcePos=this->xmpTagPos + this->xmpTagLen;
		}
		fileSize+=(sourceLen - sourcePos);
		sourcePos=0;
		progressTracker->BeginWork ( fileSize );
	}
	// First do whatever is needed to put the new XMP after any existing onMetaData tag, or as the
	// first time 0 tag.

	if ( this->omdTagPos == 0 ) {

		// There is no onMetaData tag. Copy the file header, then write the new XMP as the first tag.
		// Allow the degenerate case of a file with just a header, no initial back pointer or tags.

		originalRef->Seek ( sourcePos, kXMP_SeekFromStart );
		XIO::Copy ( originalRef, tempRef, this->flvHeaderLen, abortProc, abortArg );

		XMP_Uns32 zero = 0;	// Ensure that the initial back offset really is zero.
		tempRef->Write ( &zero, 4 );
		sourcePos = this->flvHeaderLen + 4;

		WriteOnXMP ( tempRef, this->xmpPacket );

	} else {

		// There is an onMetaData tag. Copy the front of the file through the onMetaData tag,
		// skipping any XMP that happens to be in the way. The XMP should not be before onMetaData,
		// but let's be robust. Write the new XMP immediately after onMetaData, at the same time.

		XMP_Uns64 omdEnd = this->omdTagPos + this->omdTagLen;

		if ( (this->xmpTagPos != 0) && (this->xmpTagPos < this->omdTagPos) ) {
			// The XMP tag was in front of the onMetaData tag. Copy up to it, then skip it.
			originalRef->Seek ( sourcePos, kXMP_SeekFromStart );
			XIO::Copy ( originalRef, tempRef, this->xmpTagPos, abortProc, abortArg );
			sourcePos = this->xmpTagPos + this->xmpTagLen;	// The tag length includes the trailing size field.
		}

		// Copy through the onMetaData tag, then write the XMP.
		originalRef->Seek ( sourcePos, kXMP_SeekFromStart );
		XIO::Copy ( originalRef, tempRef, (omdEnd - sourcePos), abortProc, abortArg );
		sourcePos = omdEnd;

		WriteOnXMP ( tempRef, this->xmpPacket );

	}

	// Copy the rest of the file, skipping any XMP that is in the way.

	if ( (this->xmpTagPos != 0) && (this->xmpTagPos >= sourcePos) ) {
		originalRef->Seek ( sourcePos, kXMP_SeekFromStart );
		XIO::Copy ( originalRef, tempRef, (this->xmpTagPos - sourcePos), abortProc, abortArg );
		sourcePos = this->xmpTagPos + this->xmpTagLen;
	}

	originalRef->Seek ( sourcePos, kXMP_SeekFromStart );
	XIO::Copy ( originalRef, tempRef, (sourceLen - sourcePos), abortProc, abortArg );

	this->needsUpdate = false;
	
	if (  progressTracker != 0  ) progressTracker->WorkComplete();

}	// FLV_MetaHandler::WriteTempFile