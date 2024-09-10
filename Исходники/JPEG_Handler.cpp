void JPEG_MetaHandler::WriteTempFile ( XMP_IO* tempRef )
{
	XMP_IO* origRef = this->parent->ioRef;

	XMP_AbortProc abortProc  = this->parent->abortProc;
	void *        abortArg   = this->parent->abortArg;
	const bool    checkAbort = (abortProc != 0);

	XMP_Uns16 marker, contentLen;

	static const size_t kBufferSize = 64*1024;	// Enough for a segment with maximum contents.
	XMP_Uns8 buffer [kBufferSize];
	
	XMP_Int64 origLength = origRef->Length();
	if ( origLength == 0 ) return;	// Tolerate empty files.
	if ( origLength < 4 ) {
		XMP_Throw ( "JPEG must have at least SOI and EOI markers", kXMPErr_BadJPEG );
	}

	if ( ! skipReconcile ) {
		// Update the IPTC-IIM and native TIFF/Exif metadata, and reserialize the now final XMP packet.
		ExportPhotoData ( kXMP_JPEGFile, &this->xmpObj, this->exifMgr, this->iptcMgr, this->psirMgr );
		this->xmpObj.SerializeToBuffer ( &this->xmpPacket, kXMP_UseCompactFormat );
	}

	origRef->Rewind();
	tempRef->Truncate ( 0 );

	marker = XIO::ReadUns16_BE ( origRef );	// Just read the SOI marker.
	if ( marker != 0xFFD8 ) XMP_Throw ( "Missing SOI marker", kXMPErr_BadJPEG );
	XIO::WriteUns16_BE ( tempRef, marker );

	// Copy any leading APP0 marker segments.

	while ( true ) {

		if ( checkAbort && abortProc(abortArg) ) {
			XMP_Throw ( "JPEG_MetaHandler::WriteFile - User abort", kXMPErr_UserAbort );
		}
		
		if ( ! XIO::CheckFileSpace ( origRef, 2 ) ) break;	// Tolerate a file that ends abruptly.
		
		marker = XIO::ReadUns16_BE ( origRef );	// Read the next marker.
		if ( marker == 0xFFFF ) {
			// Have a pad byte, skip it. These are almost unheard of, so efficiency isn't critical.
			origRef->Seek ( -1, kXMP_SeekFromCurrent );	// Skip the first 0xFF, read the second again.
			continue;
		}

		if ( marker != 0xFFE0 ) break;	// Have a non-APP0 marker.
		XIO::WriteUns16_BE ( tempRef, marker );	// Write the APP0 marker.
		
		contentLen = XIO::ReadUns16_BE ( origRef );	// Copy the APP0 segment's length.
		XIO::WriteUns16_BE ( tempRef, contentLen );

		if ( contentLen < 2 ) XMP_Throw ( "Invalid JPEG segment length", kXMPErr_BadJPEG );
		contentLen -= 2;	// Reduce to just the content length.
		origRef->ReadAll ( buffer, contentLen );	// Copy the APP0 segment's content.
		tempRef->Write ( buffer, contentLen );

	}

	// Write the new Exif APP1 marker segment.

	XMP_Uns32 first4;

	if ( this->exifMgr != 0 ) {

		void* exifPtr;
		XMP_Uns32 exifLen = this->exifMgr->UpdateMemoryStream ( &exifPtr );
		if ( exifLen > kExifMaxDataLength ) exifLen = this->exifMgr->UpdateMemoryStream ( &exifPtr, true /* compact */ );

		while ( exifLen > 0 ) {
			XMP_Uns32 count = std::min ( exifLen, (XMP_Uns32) kExifMaxDataLength );
			first4 = MakeUns32BE ( 0xFFE10000 + 2 + kExifSignatureLength + count );
			tempRef->Write ( &first4, 4 );
			tempRef->Write ( kExifSignatureString, kExifSignatureLength );
			tempRef->Write ( exifPtr, count );
			exifPtr = (XMP_Uns8 *) exifPtr + count;
			exifLen -= count;
		}
	}

	// Write the new XMP APP1 marker segment, with possible extension marker segments.

	std::string mainXMP, extXMP, extDigest;
	SXMPUtils::PackageForJPEG ( this->xmpObj, &mainXMP, &extXMP, &extDigest );
	XMP_Assert ( (extXMP.size() == 0) || (extDigest.size() == 32) );

	first4 = MakeUns32BE ( 0xFFE10000 + 2 + kMainXMPSignatureLength + (XMP_Uns32)mainXMP.size() );
	tempRef->Write ( &first4, 4 );
	tempRef->Write ( kMainXMPSignatureString, kMainXMPSignatureLength );
	tempRef->Write ( mainXMP.c_str(), (XMP_Int32)mainXMP.size() );

	size_t extPos = 0;
	size_t extLen = extXMP.size();

	while ( extLen > 0 ) {

		size_t partLen = extLen;
		if ( partLen > 65000 ) partLen = 65000;

		first4 = MakeUns32BE ( 0xFFE10000 + 2 + kExtXMPPrefixLength + (XMP_Uns32)partLen );
		tempRef->Write ( &first4, 4 );

		tempRef->Write ( kExtXMPSignatureString, kExtXMPSignatureLength );
		tempRef->Write ( extDigest.c_str(), (XMP_Int32)extDigest.size() );

		first4 = MakeUns32BE ( (XMP_Int32)extXMP.size() );
		tempRef->Write ( &first4, 4 );
		first4 = MakeUns32BE ( (XMP_Int32)extPos );
		tempRef->Write ( &first4, 4 );

		tempRef->Write ( &extXMP[extPos], (XMP_Int32)partLen );

		extPos += partLen;
		extLen -= partLen;

	}

	// Write the new PSIR APP13 marker segments.
	if ( this->psirMgr != 0 ) {

		void* psirPtr;
		XMP_Uns32 psirLen = this->psirMgr->UpdateMemoryResources ( &psirPtr );
		while ( psirLen > 0 ) {
			XMP_Uns32 count = std::min ( psirLen, (XMP_Uns32) kPSIRMaxDataLength );
			first4 = MakeUns32BE ( 0xFFED0000 + 2 + kPSIRSignatureLength + count );
			tempRef->Write ( &first4, 4 );
			tempRef->Write ( kPSIRSignatureString, kPSIRSignatureLength );
			tempRef->Write ( psirPtr, count );
			psirPtr = (XMP_Uns8 *) psirPtr + count;
			psirLen -= count;
		}
	}

	// Copy remaining marker segments, skipping old metadata, to the first SOS marker or to EOI.
	origRef->Seek ( -2, kXMP_SeekFromCurrent );	// Back up to the marker from the end of the APP0 copy loop.
	
	while ( true ) {

		if ( checkAbort && abortProc(abortArg) ) {
			XMP_Throw ( "JPEG_MetaHandler::WriteFile - User abort", kXMPErr_UserAbort );
		}

		if ( ! XIO::CheckFileSpace ( origRef, 2 ) ) break;	// Tolerate a file that ends abruptly.
		
		marker = XIO::ReadUns16_BE ( origRef );	// Read the next marker.
		if ( marker == 0xFFFF ) {
			// Have a pad byte, skip it. These are almost unheard of, so efficiency isn't critical.
			origRef->Seek ( -1, kXMP_SeekFromCurrent );	// Skip the first 0xFF, read the second again.
			continue;
		}

		if ( (marker == 0xFFDA) || (marker == 0xFFD9) ) {	// Quit at the first SOS marker or at EOI.
			origRef->Seek ( -2, kXMP_SeekFromCurrent );	// The tail copy must include this marker.
			break;
		}

		if ( (marker == 0xFF01) ||	// Ill-formed file if we encounter a TEM or RSTn marker.
			 ((0xFFD0 <= marker) && (marker <= 0xFFD7)) ) {
			XMP_Throw ( "Unexpected TEM or RSTn marker", kXMPErr_BadJPEG );
		}

		contentLen = XIO::ReadUns16_BE ( origRef );	// Read this segment's length.
		if ( contentLen < 2 ) XMP_Throw ( "Invalid JPEG segment length", kXMPErr_BadJPEG );
		contentLen -= 2;	// Reduce to just the content length.
		
		XMP_Int64 contentOrigin = origRef->Offset();
		bool copySegment = true;
		size_t signatureLen;

		if ( (marker == 0xFFED) && (contentLen >= kPSIRSignatureLength) ) {

			// This is an APP13 segment, skip if it is the old PSIR.
			signatureLen = origRef->Read ( buffer, kPSIRSignatureLength );
			if ( (signatureLen == kPSIRSignatureLength) &&
				 CheckBytes ( &buffer[0], kPSIRSignatureString, kPSIRSignatureLength ) ) {
				copySegment = false;
			}

		} else if ( (marker == 0xFFE1) && (contentLen >= kExifSignatureLength) ) {	// Check for the shortest signature.

			// This is an APP1 segment, skip if it is the old Exif or XMP.
			
			XMP_Assert ( (kExifSignatureLength < kMainXMPSignatureLength) &&
						 (kMainXMPSignatureLength < kExtXMPSignatureLength) );
			signatureLen = origRef->Read ( buffer, kExtXMPSignatureLength );	// Read for the longest signature.

			if ( (signatureLen >= kExifSignatureLength) &&
				 (CheckBytes ( &buffer[0], kExifSignatureString, kExifSignatureLength ) ||
				  CheckBytes ( &buffer[0], kExifSignatureAltStr, kExifSignatureLength )) ) {
				copySegment = false;
			}
			
			if ( copySegment && (signatureLen >= kMainXMPSignatureLength) &&
				 CheckBytes ( &buffer[0], kMainXMPSignatureString, kMainXMPSignatureLength ) ) {
				copySegment = false;
			}
			
			if ( copySegment && (signatureLen == kExtXMPSignatureLength) &&
				 CheckBytes ( &buffer[0], kExtXMPSignatureString, kExtXMPPrefixLength ) ) {
				copySegment = false;
			}
			
		}
		
		if ( ! copySegment ) {
			origRef->Seek ( (contentOrigin + contentLen), kXMP_SeekFromStart );
		} else {
			XIO::WriteUns16_BE ( tempRef, marker );
			XIO::WriteUns16_BE ( tempRef, (contentLen + 2) );
			origRef->Seek ( contentOrigin, kXMP_SeekFromStart );
			origRef->ReadAll ( buffer, contentLen );
			tempRef->Write ( buffer, contentLen );
		}

	}

	// Copy the remainder of the source file.

	XIO::Copy ( origRef, tempRef, (origLength - origRef->Offset()) );
	this->needsUpdate = false;

}	// JPEG_MetaHandler::WriteTempFile