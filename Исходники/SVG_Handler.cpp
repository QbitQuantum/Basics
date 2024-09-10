void SVG_MetaHandler::CacheFileData() 
{
	XMP_Assert( !this->containsXMP );

	XMP_IO * fileRef = this->parent->ioRef;
	
	XMP_Uns8 marker[ 4 ];
	fileRef->Rewind();
	fileRef->Read( marker, 4 );

	// Checking for UTF-16 BOM and UTF-32 BOM
	if ( ( marker[ 0 ] == 0xFF && marker[ 1 ] == 0xFE ) || ( marker[ 0 ] == 0xFE && marker[ 1 ] == 0xFF ) || ( marker[ 0 ] == marker[ 1 ] == 0x00 && marker[ 2 ] == 0xFE && marker[ 3 ] == 0xFF ) )
	{
		XMP_Error error( kXMPErr_BadXML, "Invalid SVG file" );
		this->NotifyClient( &this->parent->errorCallback, kXMPErrSev_OperationFatal, error );
	}
		
	// Creating a new SVG Parser
	svgAdapter = new SVG_Adapter();
	if ( svgAdapter == 0 )
		XMP_Throw( "SVG_MetaHandler: Can't create SVG adapter", kXMPErr_NoMemory );
	svgAdapter->SetErrorCallback( &this->parent->errorCallback );

	// Registering all the required tags to SVG Parser
	svgAdapter->RegisterPI( "xpacket" );
	svgAdapter->RegisterElement( "metadata", "svg" );
	svgAdapter->RegisterElement( "xmpmeta", "metadata" );
	svgAdapter->RegisterElement( "RDF", "metadata" );
	svgAdapter->RegisterElement( "title", "svg" );
	svgAdapter->RegisterElement( "desc", "svg" );

	// Parsing the whole buffer
	fileRef->Rewind();
	XMP_Uns8 buffer[ 64 * 1024 ];
	while ( true ) {
		XMP_Int32 ioCount = fileRef->Read( buffer, sizeof( buffer ) );
		if ( ioCount == 0 || !svgAdapter->IsParsingRequire() ) break;
		svgAdapter->ParseBuffer( buffer, ioCount, false /* not the end */ );
	}
	svgAdapter->ParseBuffer( 0, 0, true );	// End the parse.

	XML_Node & xmlTree = this->svgAdapter->tree;
	XML_NodePtr rootElem = 0;

	for ( size_t i = 0, limit = xmlTree.content.size(); i < limit; ++i )
	{
		if ( xmlTree.content[ i ]->kind == kElemNode ) {
			rootElem = xmlTree.content[ i ];
		}
	}
	if ( rootElem == 0 )
		XMP_Throw( "Not a valid SVG File", kXMPErr_BadFileFormat );

	XMP_StringPtr rootLocalName = rootElem->name.c_str() + rootElem->nsPrefixLen;

	if ( ! XMP_LitMatch( rootLocalName, "svg" ) )
		XMP_Throw( "Not able to parse such SVG File", kXMPErr_BadFileFormat );
	
	// Making SVG node as Root Node
	svgNode = rootElem;

	bool FoundPI = false;
	bool FoundWrapper = false;
	XML_NodePtr metadataNode = svgNode->GetNamedElement( rootElem->ns.c_str(), "metadata" );

	// We are intersted only in the Metadata tag of outer SVG element
	// XMP should be present only in metadata Node of SVG
	if ( metadataNode != NULL )
	{
		XMP_Int64 packetLength = -1;
		XMP_Int64 packetOffset = -1;
		XMP_Int64 PIOffset = svgAdapter->GetPIOffset( "xpacket", 1 );
		OffsetStruct wrapperOffset = svgAdapter->GetElementOffsets( "xmpmeta" );
		OffsetStruct rdfOffset = svgAdapter->GetElementOffsets( "RDF" );
		
		// Checking XMP PI's position
		if ( PIOffset != -1 )
		{
			if ( wrapperOffset.startOffset != -1 && wrapperOffset.startOffset < PIOffset )
				packetOffset = wrapperOffset.startOffset;
			else
			{
				XMP_Int64 trailerOffset = svgAdapter->GetPIOffset( "xpacket", 2 );
				XML_NodePtr trailerNode = metadataNode->GetNamedElement( "", "xpacket", 1 );
				if ( trailerOffset != -1 || trailerNode != 0 )
				{
					packetLength = 2;								// "<?" = 2
					packetLength += trailerNode->name.length();		// Node's name
					packetLength += 1;								// Empty Space after Node's name
					packetLength += trailerNode->value.length();	// Value
					packetLength += 2;								// "?>" = 2
					packetLength += ( trailerOffset - PIOffset );
					packetOffset = PIOffset;
				}
			}
		}
		else if ( wrapperOffset.startOffset != -1 )		// XMP Wrapper is present without PI
		{
			XML_NodePtr wrapperNode = metadataNode->GetNamedElement( "adobe:ns:meta/", "xmpmeta" );
			if ( wrapperNode != 0 )
			{
				std::string trailerWrapper = "</x:xmpmeta>";
				packetLength = trailerWrapper.length();
				packetLength += ( wrapperOffset.endOffset - wrapperOffset.startOffset );
				packetOffset = wrapperOffset.startOffset;
			}
		}
		else		// RDF packet is present without PI and wrapper
		{
			XML_NodePtr rdfNode = metadataNode->GetNamedElement( "http://www.w3.org/1999/02/22-rdf-syntax-ns#", "RDF" );
			if ( rdfNode != 0 )
			{
				std::string rdfTrailer = "</rdf:RDF>";
				packetLength = rdfTrailer.length();
				packetLength += ( rdfOffset.endOffset - rdfOffset.startOffset );
				packetOffset = rdfOffset.startOffset;
			}
		}

		// Fill the necesarry information and packet with XMP data
		if ( packetOffset != -1 )
		{
			this->packetInfo.offset = packetOffset;
			this->packetInfo.length = ( XMP_Int32 ) packetLength;
			this->xmpPacket.assign( this->packetInfo.length, ' ' );
			fileRef->Seek( packetOffset, kXMP_SeekFromStart );
			fileRef->ReadAll( ( void* )this->xmpPacket.data(), this->packetInfo.length );
			FillPacketInfo( this->xmpPacket, &this->packetInfo );
			this->containsXMP = true;
			return;
		}
	}
	this->containsXMP = false;	

}	// SVG_MetaHandler::CacheFileData