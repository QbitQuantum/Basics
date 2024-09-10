/*----------------------------------------------------------------------------------------------------------------------
	This function provides the ability to read everything following the block name (which is read by the NxsReader
	object) to the END or ENDBLOCK statement. Characters are read from the input stream `in'. Overrides the virtual
	function in the base class.
*/
void BASICCMDLINE::Read(
  NxsToken & token)	/* is the token used to read from `in' */
	{
	isEmpty = false;

	// This should be the semicolon after the block name
	token.GetNextToken();

	if (!token.Equals(";"))
		{
		errormsg = "Expecting ';' after ";
		errormsg += NCL_BLOCKTYPE_ATTR_NAME;
		errormsg += " block name, but found ";
		errormsg += token.GetToken();
		errormsg += " instead";
		throw NxsException(errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn());
		}

	for (;;)
		{
		token.GetNextToken();

		if (token.Abbreviation("ENdblock"))
			{
			HandleEndblock(token);
			break;
			}
		else if (token.Abbreviation("Help"))
			{
			HandleHelp(token);
			}
		else if (token.Abbreviation("Log"))
			{
			HandleLog(token);
			}
		else if (token.Abbreviation("EXecute"))
			{
			HandleExecute(token);
			}
		else if (token.Abbreviation("Show"))
			{
			HandleShow(token);
			}
		else if (token.Abbreviation("Quit"))
			{
			quit_now = true;

			message = "\nBASICCMDLINE says goodbye\n";
			PrintMessage();

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