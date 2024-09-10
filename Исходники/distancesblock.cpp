/**
 * @method Read [void:protected]
 * @param token [NexusToken&] the token used to read from in
 * @throws XNexus
 *
 * This function provides the ability to read everything following the block name
 * (which is read by the Nexus object) to the end or endblock statement.
 * Characters are read from the input stream in. Overrides the
 * abstract virtual function in the base class.
 */
void DistancesBlock::Read( NexusToken& token )
{
   isEmpty = false;
	token.GetNextToken(); // this should be the semicolon after the block name
	if( !token.Equals(";") ) {
		errormsg = "Expecting ';' after ";
      errormsg += id;
      errormsg += " block name, but found ";
      errormsg += token.GetToken();
      errormsg += " instead";
		throw XNexus( errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn() );
	}

	for(;;)
	{
		token.GetNextToken();

		if( token.Equals("DIMENSIONS") ) {
         HandleDimensionsCommand( token );
		}
		else if( token.Equals("FORMAT") ) {
         HandleFormatCommand( token );
		}
		else if( token.Equals("TAXLABELS") ) {
         HandleTaxlabelsCommand( token );
		}
		else if( token.Equals("MATRIX") ) {
         HandleMatrixCommand( token );
		}
		else if( token.Equals("END") ) {
			// get the semicolon following END
			token.GetNextToken();
         if( !token.Equals(";") ) {
				errormsg = "Expecting ';' to terminate the END command, but found ";
            errormsg += token.GetToken();
            errormsg += " instead";
				throw XNexus( errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn() );
         }
			break;
		}
		else if( token.Equals("ENDBLOCK") ) {
			// get the semicolon following ENDBLOCK
			token.GetNextToken();
         if( !token.Equals(";") ) {
				errormsg = "Expecting ';' to terminate the ENDBLOCK command, but found ";
            errormsg += token.GetToken();
            errormsg += " instead";
				throw XNexus( errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn() );
         }
			break;
		}
		else {
      	SkippingCommand( token.GetToken() );
         do {
            token.GetNextToken();
         } while( !token.AtEOF() && !token.Equals(";") );
         if( token.AtEOF() ) {
				errormsg = "Unexpected end of file encountered";
				throw XNexus( errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn() );
         }
		}
	}
}