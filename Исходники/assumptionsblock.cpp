/**
 * @method HandleEndblock [void:protected]
 * @param token [NexusToken&] the token used to read from in
 * @throws XNexus
 *
 * Called when the END or ENDBLOCK command needs to be parsed
 * from within the ASSUMPTIONS block.  Basically just checks to make
 * sure the next token in  the data file is a semicolon.
 */
void AssumptionsBlock::HandleEndblock( NexusToken& token )
{
	// get the semicolon following END or ENDBLOCK token
   //
	token.GetNextToken();

	if( !token.Equals(";") ) {
   	errormsg = "Expecting ';' to terminate the END or ENDBLOCK command, but found ";
      errormsg += token.GetToken();
      errormsg += " instead";
		throw XNexus( errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn() );
	}
}