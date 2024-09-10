int WorkTodo::read_file( const char *fileName )
{
	int retVal = -1;
	
	TwsXml file;
	if( ! file.openFile(fileName) ) {
		return retVal;
	}
	retVal = 0;
	xmlNodePtr xn;
	while( (xn = file.nextXmlNode()) != NULL ) {
		assert( xn->type == XML_ELEMENT_NODE  );
		if( strcmp((char*)xn->name, "request") == 0 ) {
			retVal += read_req( xn );
		} else {
			fprintf(stderr, "Warning, unknown request tag '%s' ignored.\n",
				xn->name );
		}
	}
	
	return retVal;
}