///----------------------------------------------------------
/// 
///----------------------------------------------------------
XMLNode CreateXMLDocumentFromResourceStream( const ResourceStream& resourceStream, const std::string& optionalExpectedRootNodeName )
{
	XMLResults results;
	const char* resourceStreamAsciiFileBuffer = (const char*)resourceStream.GetDirectBufferAccess();
	XMLNode xmlDocumentRootNode = XMLNode::parseString( resourceStreamAsciiFileBuffer, NULL, &results );

	// Report errors here if "results" indicates any problems
	if( results.error != eXMLErrorNone )
	{
		ReportXMLError( resourceStream, xmlDocumentRootNode, results );
	}

	// Advance past the "xml declaration" node, if present; e.g.: <?xml version="1.0" encoding="us-ascii"?>
	// ...OR, if the root node is nameless, then it must be an implicit document-root (usually in an XML without a declaration), skip that
	while( (xmlDocumentRootNode.isDeclaration() || !xmlDocumentRootNode.getName()) && xmlDocumentRootNode.nChildNode() > 0 )
	{
		xmlDocumentRootNode = xmlDocumentRootNode.getChildNode( 0 );
	}

	if( !optionalExpectedRootNodeName.empty() )
	{
		const std::string rootNodeName = xmlDocumentRootNode.getName();
		if( Stricmp( optionalExpectedRootNodeName, rootNodeName ) )
		{
			//JAZZ_ERROR( "XML Data File Error", Stringf( "In XML data file %s, was expecting a root node\n type of <%s>, but found <%s> instead!", resourceStream.GetJazzPath()..c_str(), optionalExpectedRootNodeName.c_str(), rootNodeName.c_str() ) );
		}
	}

	return xmlDocumentRootNode;
}