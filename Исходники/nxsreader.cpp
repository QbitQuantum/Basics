bool NxsReader::ReadUntilEndblock(NxsToken &token, const std::string & )
	{
	for (;;)
		{
		token.GetNextToken();
		if (token.Equals("END") || token.Equals("ENDBLOCK")) 
			{
			token.GetNextToken();
			if (!token.Equals(";")) 
				{
				std::string errormsg = "Expecting ';' after END or ENDBLOCK command, but found ";
				errormsg += token.GetToken();
				errormsg += " instead";
				NexusError(NxsString(errormsg.c_str()), token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn());
				return false;
				}
			return true;
			}
		}
	}