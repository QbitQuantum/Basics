//--------------------------------------------------------------
//
// Name:			paraseFormula
// Class:			GameplayFormula
//
// Description:		Parses the formula
//
// Parameters:		Script &formulaFile -- The file to parse
//					const str& name -- The token
//
// Returns:			
//
//--------------------------------------------------------------
bool GameplayFormula::parseFormula(Script &formulaFile, const str& name)
{
	const char *token;
	GameplayFormulaOperand *gpfo;
	
	if ( name != "FORMULA" )
		return false;

	if ( !formulaFile.TokenAvailable(false) )
		return false;
	
	token = formulaFile.GetToken(false);
	setName(token);

	// Get the open brace
	token = formulaFile.GetToken(true);
	if ( token[0] != '{' )
		assert(0);

	while (formulaFile.TokenAvailable(true))
	{
		token = formulaFile.GetToken(true);

		// If we have a close brace, we're done.
		if ( token[0] == '}' )
			return true;

		gpfo = new GameplayFormulaOperand();
		if ( gpfo->parseOperand(formulaFile, token) )
			_operandList.AddObject(gpfo);
		else
		{
			delete gpfo;
			return false;
		}
	}

	// Premature end of file, missing close brace.
	return false;
}