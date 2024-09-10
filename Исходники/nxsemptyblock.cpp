/*----------------------------------------------------------------------------------------------------------------------
|	This function provides the ability to read everything following the block name (which is read by the NxsReader 
|	object) to the END or ENDBLOCK statement. Characters are read from the input stream `in'. Overrides the pure 
|	virtual function in the base class.
*/
void NxsEmptyBlock::Read(
  NxsToken &token)	/* the token used to read from `in'*/
	{
	isEmpty = false;

	// This should be the semicolon after the block name
	//
	token.GetNextToken();

	if (!token.Equals(";"))
		{
		errormsg = "Expecting ';' after ";
		errormsg += id;
		errormsg += " block name, but found ";
		errormsg += token.GetToken();
		errormsg += " instead";
		throw NxsException(errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn());
		}

	for(;;)
		{
		token.GetNextToken();

		if (token.Equals("END"))
			{
			HandleEndblock(token);
			break;
			}

		else if(token.Equals("ENDBLOCK"))
			{
			HandleEndblock(token);
			break;
			}

		else
			{
			SkippingCommand(token.GetToken());

			do
				{
				token.GetNextToken();
				}
			while (!token.AtEOF() && !token.Equals(";"));

			if (token.AtEOF())
				{
				errormsg = "Unexpected end of file encountered";
				throw NxsException(errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn());
				}
			}
		}
	}