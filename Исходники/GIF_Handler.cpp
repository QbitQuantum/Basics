void GIF_MetaHandler::WriteTempFile ( XMP_IO* tempRef )
{
	XMP_Assert( this->needsUpdate );

	XMP_IO* originalRef = this->parent->ioRef;
	originalRef->Rewind();

	tempRef->Truncate ( 0 );
	
	if ( XMPPacketOffset != 0 )
	{
		// Copying blocks before XMP Application Block
		XIO::Copy( originalRef, tempRef, XMPPacketOffset );

		// Writing XMP Packet
		tempRef->Write( this->xmpPacket.c_str(), (XMP_Uns32)this->xmpPacket.size() );

		// Copying Rest of the file
		originalRef->Seek( XMPPacketLength, kXMP_SeekFromCurrent );
		XIO::Copy( originalRef, tempRef, originalRef->Length() - originalRef->Offset() );

	}
	else
	{
		if ( trailerOffset == 0 )
			XMP_Throw( "Not able to write XMP packet in GIF file", kXMPErr_BadFileFormat );

		// Copying blocks before XMP Application Block
		XIO::Copy( originalRef, tempRef, trailerOffset );

		// Writing Extension Introducer 
		XIO::WriteUns8( tempRef, kXMP_block_Extension );

		// Writing Application Extension label
		XIO::WriteUns8( tempRef, 0xFF );

		// Writing Application Extension label
		XIO::WriteUns8( tempRef, APP_ID_LEN );

		// Writing Application Extension label
		tempRef->Write( XMP_APP_ID_DATA, APP_ID_LEN );

		// Writing XMP Packet
		tempRef->Write( this->xmpPacket.c_str(), (XMP_Uns32)this->xmpPacket.size() );

		// Writing Magic trailer
		XMP_Uns8 magicByte = 0x01;
		tempRef->Write( &magicByte, 1 );
		for ( magicByte = 0xFF; magicByte != 0x00; --magicByte )
			tempRef->Write( &magicByte, 1 );
		tempRef->Write( &magicByte, 1 );
		tempRef->Write( &magicByte, 1 );

		// Copying Rest of the file
		XIO::Copy( originalRef, tempRef, originalRef->Length() - originalRef->Offset() );

	}

}	// GIF_MetaHandler::WriteTempFile