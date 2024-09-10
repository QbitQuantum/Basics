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
void TaxaBlock::Read( NexusToken& token )
{
   isEmpty = false;
	token.GetNextToken(); // this should be the semicolon after the block name
	if( !token.Equals(";") ) {
		errormsg = "Expecting ';' after TAXA block name, but found ";
      errormsg += token.GetToken();
      errormsg += " instead";
		throw XNexus( errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn() );
	}

	for(;;)
	{
		token.GetNextToken();
		
		if( token.Equals("DIMENSIONS") ) {
			token.GetNextToken(); // this should be the NTAX keyword
			if( !token.Equals("NTAX") ) {
				errormsg = "Expecting NTAX keyword, but found ";
            errormsg += token.GetToken();
            errormsg += " instead";
				throw XNexus( errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn() );
			}

			token.GetNextToken(); // this should be the equals sign
         if( !token.Equals("=") ) {
				errormsg = "Expecting '=', but found ";
            errormsg += token.GetToken();
            errormsg += " instead";
				throw XNexus( errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn() );
         }

			token.GetNextToken(); // this should be the number of taxa
         ntax = atoi( token.GetToken().c_str() );
         if( ntax <= 0 ) {
				errormsg = "NTAX should be greater than zero (";
            errormsg += token.GetToken();
            errormsg += " was specified)";
				throw XNexus( errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn() );
         }

			token.GetNextToken(); // this should be the terminating semicolon
         if( !token.Equals(";") ) {
				errormsg = "Expecting ';' to terminate DIMENSIONS command, but found ";
            errormsg += token.GetToken();
            errormsg += " instead";
				throw XNexus( errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn() );
         }
		}
		else if( token.Equals("TAXLABELS") ) {
      	if( ntax <= 0 ) {
				errormsg = "NTAX must be specified before TAXLABELS command";
				throw XNexus( errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn() );
         }

         for( int i = 0; i < ntax; i++ ) {
				token.GetNextToken();
            taxonLabels.push_back( token.GetToken() );
         }

			token.GetNextToken(); // this should be terminating semicolon
         if( !token.Equals(";") ) {
				errormsg = "Expecting ';' to terminate TAXLABELS command, but found ";
            errormsg += token.GetToken();
            errormsg += " instead";
				throw XNexus( errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn() );
         }
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