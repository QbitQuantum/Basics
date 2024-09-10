void Parser::VarListTail(ExprRec& var, ExprRec& index) {
	switch (NextToken()) {
	case COMMA:
		Match(COMMA);
		Variable(var, index);
		code.ProcessVar(var, index); /*** CODE ***/
		code.Listen(var, index); /*** CODE ***/
		/* Recursion for other variables */
		VarListTail(var, index);
		break;
	case SEMICOLON:
		break;
	default:
		SyntaxError(NextToken(), "VarListTail");
	}
}