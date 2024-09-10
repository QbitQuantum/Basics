MDBXMLNode* MDBXMLNode::Identify( const char* p, MDBXMLEncoding encoding )
{
	MDBXMLNode* returnNode = 0;

	p = SkipWhiteSpace( p, encoding );
	if( !p || !*p || *p != '<' )
	{
		return 0;
	}

	MDBXMLDocument* doc = GetDocument();
	p = SkipWhiteSpace( p, encoding );

	if ( !p || !*p )
	{
		return 0;
	}

	// What is this thing? 
	// - Elements start with a letter or underscore, but xml is reserved.
	// - Comments: <!--
	// - Decleration: <?xml
	// - Everthing else is unknown to tinyxml.
	//

	const char* xmlHeader = { "<?xml" };
	const char* commentHeader = { "<!--" };
	const char* dtdHeader = { "<!" };
	const char* cdataHeader = { "<![CDATA[" };

	if ( StringEqual( p, xmlHeader, true, encoding ) )
	{
		#ifdef DEBUG_PARSER
			MDBXML_LOG( "XML parsing Declaration\n" );
		#endif
		returnNode = new MDBXMLDeclaration();
	}
	else if ( StringEqual( p, commentHeader, false, encoding ) )
	{
		#ifdef DEBUG_PARSER
			MDBXML_LOG( "XML parsing Comment\n" );
		#endif
		returnNode = new MDBXMLComment();
	}
	else if ( StringEqual( p, cdataHeader, false, encoding ) )
	{
		#ifdef DEBUG_PARSER
			MDBXML_LOG( "XML parsing CDATA\n" );
		#endif
		MDBXMLText* text = new MDBXMLText( "" );
		text->SetCDATA( true );
		returnNode = text;
	}
	else if ( StringEqual( p, dtdHeader, false, encoding ) )
	{
		#ifdef DEBUG_PARSER
			MDBXML_LOG( "XML parsing Unknown(1)\n" );
		#endif
		returnNode = new MDBXMLUnknown();
	}
	else if (    IsAlpha( *(p+1), encoding )
			  || *(p+1) == '_' )
	{
		#ifdef DEBUG_PARSER
			MDBXML_LOG( "XML parsing Element\n" );
		#endif
		returnNode = new MDBXMLElement( "" );
	}
	else
	{
		#ifdef DEBUG_PARSER
			MDBXML_LOG( "XML parsing Unknown(2)\n" );
		#endif
		returnNode = new MDBXMLUnknown();
	}

	if ( returnNode )
	{
		// Set the parent, so it can report errors
		returnNode->parent = this;
	}
	else
	{
		if ( doc )
			doc->SetError( MDBXML_ERROR_OUT_OF_MEMORY, 0, 0, MDBXML_ENCODING_UNKNOWN );
	}
	return returnNode;
}