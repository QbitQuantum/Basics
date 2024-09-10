	////////////////////////////////////////////////////////////////////////////////
	// LexOther:  Lex the token types known to subclass (must be defined by subclass)
	// Return value:
	//	RegularExprToken::Type		The type of the matched token.
	//
	// Note: May throw an integer to indicate error.
	////////////////////////////////////////////////////////////////////////////////
	RegularExprToken::Type RegularExprLexerSymbol::LexOther()
	{
		//the symbol strings are separated by spaces
		if (!ISALNUM(current)) {
			throw 1;
		}
		while (ISALNUM(current) || current == '_') {
			Consume();
		}

		return RegularExprToken::Literal;
	}