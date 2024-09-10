/*----------------------------------------------------------------------------------------------------------------------
|	This function provides the ability to read everything following the block name (which is read by the NxsReader 
|	object) to the end or endblock statement. Characters are read from the input stream in. Overrides the abstract 
|	virtual function in the base class. 
*/
void NxsTaxaBlock::Read(
  NxsToken &token)	/* the token used to read from in */
	{
	ntax				= 0;
	unsigned nominal_ntax	= 0;
	isEmpty				= false;
	isUserSupplied		= true;

	DemandEndSemicolon(token, "BEGIN TAXA");

	for (;;)
		{
		token.GetNextToken();

		if (token.Equals("DIMENSIONS"))
			{
			// This should be the NTAX keyword
			//
			token.GetNextToken(); 

			if (!token.Equals("NTAX"))
				{
				errormsg = "Expecting NTAX keyword, but found ";
				errormsg += token.GetToken();
				errormsg += " instead";
				throw NxsException(errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn());
				}

			DemandEquals(token, "after NTAX");
			nominal_ntax = DemandPositiveInt(token, "NTAX");
			DemandEndSemicolon(token, "DIMENSIONS");
			}	// if (token.Equals("DIMENSIONS"))

		else if (token.Equals("TAXLABELS")) 
			{
			if (nominal_ntax <= 0) 
				{
				errormsg = "NTAX must be specified before TAXLABELS command";
				throw NxsException(errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn());
				}

			for (unsigned i = 0; i < nominal_ntax; i++)
				{
				token.GetNextToken();
				//@pol should check to make sure this is not punctuation
				AddTaxonLabel(token.GetToken());
				}
			DemandEndSemicolon(token, "TAXLABELS");
			}	// if (token.Equals("TAXLABELS")) 

		else if (token.Equals("END") || token.Equals("ENDBLOCK"))
			{
			DemandEndSemicolon(token, "ENDBLOCK");
			break;
			}	// if (token.Equals("END") || token.Equals("ENDBLOCK"))

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
			}	// token not END, ENDBLOCK, TAXLABELS, or DIMENSIONS
		}	// GetNextToken loop
	}